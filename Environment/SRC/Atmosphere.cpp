#include "Atmosphere.h"

AtmosOut AtmosCOESA(const AtmosCOESA_In In, const AtmosCOESA_Actions Action)
{
	AtmosOut Atm;
	UInt32 i;
	Real64 H, PressMultiplier;

	H = AtmosGH(In.Alt);
	//H = In.Alt;
	HandleAtmosCOESA_Action(H, Action);

	//Atm.Gravity = AtmosGravity(In.Alt);

	for (i = 0; i < ATMOS_DATALEN-1; i++) {
		if (H < AtmosConstants::ISA_GHeights[i+1]) {
			break; // Relevant index is found
		}
	}

	Atm.Temp			= AtmosConstants::ISA_Temperature[i] + AtmosConstants::ISA_LapseRate[i]*(H - AtmosConstants::ISA_GHeights[i]) + In.dTemp;
	Atm.Vsound			= sqrt(AtmosConstants::GammaRconst * Atm.Temp);

	PressMultiplier		= (abs(AtmosConstants::ISA_LapseRate[i]) > EPS_d) ?	pow((AtmosConstants::ISA_Temperature[i]/(Atm.Temp - In.dTemp)),(AtmosConstants::SL_Gravity/(AtmosConstants::R_Specific*AtmosConstants::ISA_LapseRate[i]))) :
																			pow(EULER,(-AtmosConstants::SL_Gravity*(H - AtmosConstants::ISA_GHeights[i]))/(AtmosConstants::R_Specific*AtmosConstants::ISA_Temperature[i]));
	Atm.Press			= AtmosConstants::ISA_Pressure[i]*PressMultiplier;
	Atm.Rho				= Atm.Press/(AtmosConstants::R_Specific*Atm.Temp);
	
	Atm.DynamViscosity	= AtmosConstants::Beta_Visc * pow(Atm.Temp, 1.5) / (Atm.Temp + AtmosConstants::Sutherland);
	Atm.kT				= (2.64638e-3 * pow(Atm.Temp, 1.5)) / (Atm.Temp + 245.4 * pow(10.0, -12.0 / Atm.Temp));

	return Atm;
}

void HandleAtmosCOESA_Action(const Real64 H, const AtmosCOESA_Actions Action)
{
	switch (Action)
	{
		case AtmosCOESA_Actions::AtmosCOESA_None:
		{
			// Do nothing
			break;
		}
		case AtmosCOESA_Actions::AtmosCOESA_Warning:
		{
			if (H < AtmosConstants::ISA_GHeights[0] || H > AtmosConstants::ISA_GHeights[7]) {
				LOGWARNING("AtmosCOESA Warning: Geopotential height out of model bounds.");
			}
			break;
		}
		case AtmosCOESA_Actions::AtmosCOESA_Error:
		{
			if (H < AtmosConstants::ISA_GHeights[0] || H > AtmosConstants::ISA_GHeights[7]) {
				LOGERROR("Geopotential height out of model bounds.\nSimulation is terminating");
				std::exit(1); // Temporal, termination will be handled more comprehensively rather than local execution command
			}
			break;
		}
	}
}

Real64 AtmosGH(const Real64 H)
{
	return ((H * AtmosConstants::EarthRadius0) / (H + AtmosConstants::EarthRadius0));
}

//Real64 AtmosGravity(const Real64 Z)
//{
//	return AtmosConstants::SL_Gravity * SQR(AtmosConstants::EarthRadius0/(Z + AtmosConstants::EarthRadius0));
//}

void AtmosphericModelUUT()
{
	AtmosCOESA_In AtmIn;
	AtmIn.Alt	= 0.0;
	AtmIn.dTemp = 0.0;

	AtmosOut Atm = AtmosCOESA(AtmIn);
	LogMoveLine("Geopotential Height = "	<< AtmosGH(AtmIn.Alt)	<< " [m], dTemp = " << AtmIn.dTemp << " [K]");
	//LogMoveLine("Gravity = "				<< Atm.Gravity			<< " [m/s^2]");
	LogMoveLine("Pressure = "				<< Atm.Press			<< " [Pa]");
	LogMoveLine("Rho = "					<< Atm.Rho				<< " [kg/m^3]");
	LogMoveLine("Temperature = "			<< Atm.Temp				<< " [K]");
	LogMoveLine("Vsound = "					<< Atm.Vsound			<< " [m/s]");
	LogMoveLine("Dynamic viscosity = "		<< Atm.DynamViscosity	<< " [N*s/m^2]");
	LogMoveLine("Thermal conductivity = "	<< Atm.kT				<< " [W/m*K]");
}