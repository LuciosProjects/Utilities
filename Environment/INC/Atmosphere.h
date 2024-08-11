#ifndef _ATMOSPHERE_H
#define _ATMOSPHERE_H

#include "Utilities.h"

#define ATMOS_DATALEN 9

/* Action enum for AtmosCOESA */
enum class AtmosCOESA_Actions
{
	AtmosCOESA_None,
	AtmosCOESA_Warning,
	AtmosCOESA_Error
};

/* Atmospheric model output struct */
struct AtmosOut
{
	Real64 Rho;				// [kg/m^3]			Air density
	Real64 Temp;			// [K]				Air ambient temperature
	Real64 Press;			// [Pa]				Air ambient pressure
	Real64 Vsound;			// [m/s]			Ambient speed of sound
	//Real64 Gravity;			// [m/s^2]			Gravitational acceleration
	Real64 DynamViscosity;	// [kg/s*m*K^0.5]	Dynamic viscosity
	Real64 kT;				// [W/m*K]			Thermal conductivity
};

///* AtmosLapse input struct */
//typedef struct AtmosLapseIn
//{
//	Real64 H;
//	Real64 g0;
//	Real64 SpecificHeatRatio;
//	Real64 Rgas;
//	Real64 LapseRate;
//	Real64 H_Troposphere;
//	Real64 H_Tropopause;
//	Real64 Rho0;
//	Real64 P0;
//	Real64 T0;
//}AtmosLapseIn;

/* AtmosCOESA input struct */
struct AtmosCOESA_In
{
	Real64 Alt		= 0.0;
	Real64 dTemp	= 0.0;
};

/* Atmospheric constant definitions */
namespace AtmosConstants
{
	constexpr Real64 k_bolzmann		= 1.380622e-23;	// [J/K] Bolzmann's constant
	constexpr Real64 Sutherland		= 110.4;		// [K] Sutherland's constant
	constexpr Real64 Beta_Visc		= 1.458e-6;		// [kg/s*m*K^0.5] Constant expression for dynamic viscosity
	constexpr Real64 SL_Pressure	= 101325.0;		// [pa]
	constexpr Real64 SL_Density		= 1.225;		// [kg/m^3]
	constexpr Real64 SL_Temp		= 288.15;		// [K]
	constexpr Real64 SL_Gravity		= 9.80665;		// [m/s^2]
	constexpr Real64 R_Specific		= 287.052874;	// [J/kg*K] for dry air only
	constexpr Real64 SpecificHeat_r	= 1.4;			// Specific hear ratio for air at constant pressure & volume
	constexpr Real64 AirMolarMass	= 28.9644;		// [kg/kmol] Molar mass of air
	constexpr Real64 SL_LapseRate	= -0.0065;		// [K/m] Sea level lapse rate
	constexpr Real64 EarthRadius0	= 6356766.0;	// [m] Effective radius of the earth
	constexpr Real64 GammaRconst	= SpecificHeat_r * R_Specific; // Precalculating Gamma * R to save calculations

	constexpr Real64 ISA_GHeights[ATMOS_DATALEN]	= {  -5000.0,		0.0000, 11000.00,				  20000.000,			  32000.0000,				47000.00,				51000.0000,				71000.000,				84852.000 };
	constexpr Real64 ISA_LapseRate[ATMOS_DATALEN]	= {  -0.0065, SL_LapseRate,	    0.00,					  0.001,				  0.0028,					0.00,				   -0.0028,				   -0.002,					0.000 };
	constexpr Real64 ISA_Temperature[ATMOS_DATALEN] = {	  320.65,	   SL_Temp,   216.65,					216.650,				228.6500,				  270.65,				  270.6500,				  214.650,				  186.946 };
	constexpr Real64 ISA_Pressure[ATMOS_DATALEN]	= { 177687.0,  SL_Pressure,	    2.26320639734629E+4,	  5.47488866967777E+3,    8.68018684755228E+2,		1.10906305554966E+2,	6.69388731186873E+1,	3.95642042804073E+0,	3.73383589976215E-1 };
}

/********************************************************************************/
/***************************** Atmosphere functions *****************************/
/********************************************************************************/

/* All calculations in this function will be w.r.t SI units */
/* This model uses a rather basic & simpllified gravitational model */
AtmosOut AtmosCOESA(const AtmosCOESA_In In,const AtmosCOESA_Actions Action = AtmosCOESA_Actions::AtmosCOESA_None);

//////////////////////// Helper functions ////////////////////////
/* Geopotential Height */
Real64 AtmosGH(const Real64 Z);
/* Gravitational field strength */
Real64 AtmosGravity(const Real64 Z);
/* AtmosCOESA action handler */
void HandleAtmosCOESA_Action(const Real64 Z,const AtmosCOESA_Actions Action);

/* Unittest function */
void AtmosphericModelUUT();

#endif
