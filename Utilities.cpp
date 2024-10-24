#include "Utilities.h"

/******************************************************************************/
/***************************** General Functions ******************************/
/******************************************************************************/
std::string GetUtilitiesVer()
{
	return UtilitiesVer;
}

/******************************************************************************/
/******************************* Time Utilities *******************************/
/******************************************************************************/
std::string Utilities::Time::GetDateTime()
{
	std::tm timeStruct;
	Char buffer[_UTILITIES_CHAR_BUFFER_LEN];

	std::chrono::system_clock::time_point CurrentTime = std::chrono::system_clock::now();
	std::time_t DateTime = std::chrono::system_clock::to_time_t(CurrentTime);

	// Convert to a tm structure for formatting
	localtime_s(&timeStruct, &DateTime);  // Thread-safe version of localtime

	std::strftime(buffer, sizeof(buffer), "%Y\\%m\\%d %H:%M:%S", &timeStruct);

	return std::string(buffer);
}

std::chrono::high_resolution_clock::time_point Utilities::Time::TStart()
{
	return std::chrono::high_resolution_clock::now();
}

UInt64x2 Utilities::Time::GetDuration(std::chrono::high_resolution_clock::time_point Start)
{
	Stop								= std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds duration	= std::chrono::duration_cast<std::chrono::nanoseconds>(Stop - Start);
	return duration.count();
}

std::string Utilities::Time::TStop(const std::chrono::high_resolution_clock::time_point Start)
{
	UInt16 i, i_start = 0;
	UInt64x2 TimeUnits[6] = { 0 }, Res;
	UInt64x2 TimeMultipliers[5] = { Utilities::Time::Hours2Minutes ,
									Utilities::Time::Minutes2Seconds  ,
									Utilities::Time::Seconds2Milliseconds ,
									Utilities::Time::Milliseconds2Microseconds ,
									Utilities::Time::Microseconds2Nanoseconds };
	Stop = std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Stop - Start); // duration in nanoseconds
	std::string durStr;

	// Fill TimeUnits vector
	Res = duration.count();
	for (i = 5; i > 0; i--) {
		TimeUnits[i] = Res % TimeMultipliers[i-1];
		Res -= TimeUnits[i];
		Res /= TimeMultipliers[i-1];
	}
	TimeUnits[0] = Res; // Last iteration for the hours scale

	for (i = 0; i < 6; i++) {
		if (TimeUnits[i] > 0) {
			i_start = i;
		}
	}

	// Determine timescale & print
	switch (i_start)
	{
		case 0:
		{
			//std::cout << "Execution time: " << TimeUnits[0] << ":" << TimeUnits[1] << ":" << TimeUnits[2] << "." << TimeUnits[3] << " hours." << std::endl;
			durStr = "Execution time: " + std::to_string(TimeUnits[0]) + ":" + std::to_string(TimeUnits[1]) + ":" + std::to_string(TimeUnits[2]) + "." + std::to_string(TimeUnits[3]) + " hours.";
			break;
		}
		case 1:
		{
			//std::cout << "Execution time: " << TimeUnits[1] << ":" << TimeUnits[2] << "." << TimeUnits[3] << " minutes." << std::endl;
			durStr = "Execution time: " + std::to_string(TimeUnits[1]) + ":" + std::to_string(TimeUnits[2]) + "." + std::to_string(TimeUnits[3]) + " minutes.";
			break;
		}
		case 2:
		{
			//std::cout << "Execution time: " << TimeUnits[2] << "." << TimeUnits[3] << " seconds." << std::endl;
			durStr = "Execution time: " + std::to_string(TimeUnits[2]) + "." + std::to_string(TimeUnits[3]) + " seconds.";
			break;
		}
		case 3:
		{
			//std::cout << "Execution time: " << TimeUnits[3] << "." << TimeUnits[4] << " milliseconds." << std::endl;
			durStr = "Execution time: " + std::to_string(TimeUnits[3]) + "." + std::to_string(TimeUnits[4]) + " milliseconds.";
			break;
		}
		case 4:
		{
			//std::cout << "Execution time: " << TimeUnits[4] << "." << TimeUnits[5] << " microseconds." << std::endl;
			durStr = "Execution time: " + std::to_string(TimeUnits[4]) + "." + std::to_string(TimeUnits[5]) + " microseconds.";
			break;
		}
		case 5:
		{
			//std::cout << "Execution time: "  << TimeUnits[5] << " nanoseconds." << std::endl;
			durStr = "Execution time: "  + std::to_string(TimeUnits[5]) + " nanoseconds.";
			break;
		}
	}

	return durStr;
}

/*******************************************************************************/
/***************************** MsgLogger Utilities *****************************/
/*******************************************************************************/
// TBD

/*******************************************************************************/
/***************************** Interpolation Tools *****************************/
/*******************************************************************************/
BOOLEAN Utilities::InterpTools::GetInterpParams(Real64 x, Real64 Xvec[], UInt32 size, SInt32* Start_idx, Real64* dX, InterpType IT)
{
	UInt32 i;
	BOOLEAN InterpSuccess = FALSE;

	for (i = 1; i < size; i++)
	{
		if (x < Xvec[i]) {
			*Start_idx		= i-1;
			*dX				= Xvec[i] - Xvec[i-1];
			InterpSuccess	= TRUE;
			break;
		}
	}

	if (!InterpSuccess) {
		*Start_idx	= -1;
		*dX			= 0.0;
	}

	// There will be an extension that enables extrapolation
	return InterpSuccess;
}

Real64 Utilities::InterpTools::Interp1D(Real64 x, Real64 Xvec[], Real64 Yvec[], UInt32 Start_idx, Real64 dX)
{
	// For now it doesn't support extrapolation
	return Yvec[Start_idx] + ((Yvec[Start_idx + 1] - Yvec[Start_idx]) / dX) * (x - Xvec[Start_idx]);
}

void InterpolationUnitest()
{
	constexpr UInt32 VecSize = 100;

	Real64 X[VecSize], Y[VecSize], x = 0.0, dX, InterpResult;
	SInt32 n;
	BOOLEAN InterpSuccess;

	// Preparing interpolation vectors
	for (n = 0; n < VecSize; n++) {
		X[n] = x;
		Y[n] = sin(x);

		x += 0.1;
	}
	x = 0.15; // Xquery

	InterpSuccess = Utilities::InterpTools::GetInterpParams(x, X, VecSize, &n, &dX);
	InterpResult = Utilities::InterpTools::Interp1D(x, X, Y, n, dX);
	LogMoveLine("Interp result - " << InterpResult << ", Reference - " << sin(x));
}

/*******************************************************************************/
/********************************* Other Tools *********************************/
/*******************************************************************************/
