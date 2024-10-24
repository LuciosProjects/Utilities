#ifndef UTILITIES_H
#define UTILITIES_H

// General libraries
#include <functional>
#include <map>
#include <variant>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <regex>
#include <chrono>
#include <ctime>
#include <random>
#include <cstdarg>
#include <typeinfo>

//#include "direct.h"
//#include "stdio.h"
//#include "math.h"

/**************************************/
/***** Project specific libraries *****/
/**************************************/
// Type definitions & common definitions
#include "UtilitiesVer.h"
#include "TypeDefinitions.h"
#include "CommonGlobals.h"
#include "CommonStructs.h"

// Local math libraries
#include "MathUtils.h"
//#include "SM_Matrix.hpp"
#include "Matrix.h"
#include "Quaternion.h"

#include "MathUtils_Unittests.h"

// Environment libraries
#include "EnvironmentIncludes.h" // Includes of all Earth folder utilities

// Other libraries
//#include "TransferFunc.h"

// AI libraries
// TBD

/**************************************/
/*************** Macros ***************/
/**************************************/
#define LogMoveLine(str)		(std::cout << str << std::endl)
#define LogDontMoveLine(str)	(std::cout << str)
#define LOGWARNING(msg)			(std::cout << "Warning in " << __FUNCTION__ << ", " << msg << std::endl)
#define LOGERROR(msg)			(std::cout << "Error in " << __FUNCTION__ << ", " << msg << std::endl)
#define LENGTH(Vec)				(UInt32)(sizeof(Vec)/sizeof(Vec[0]))


#define _UTILITIES_CHAR_BUFFER_LEN 100

enum InterpType
{
	IT_Inbounds,
	IT_Extrapolate
};

namespace Utilities
{	
	namespace Time 
	{	
		using namespace TimeConversions;
		using time_point = std::chrono::high_resolution_clock::time_point;

		static std::chrono::high_resolution_clock::time_point Stop;

		//Char* GetDateTime();
		std::string GetDateTime();
		std::chrono::high_resolution_clock::time_point TStart();
		UInt64x2 GetDuration(std::chrono::high_resolution_clock::time_point Start);
		//void TStop(const std::chrono::high_resolution_clock::time_point Start);
		std::string TStop(const std::chrono::high_resolution_clock::time_point Start);
	}

	namespace MsgLogger
	{
		// This section will handle log messages for the solution
		// Log message function (taking std::ostream& as input)
		// Message logging by print level (Normal/Warning/Error)
	}

	namespace InterpTools
	{
		/* Xvec must be monotonic */
		BOOLEAN GetInterpParams(Real64 x, Real64 Xvec[], UInt32 size, SInt32* Start_idx, Real64* dX, InterpType IT = IT_Inbounds);
		Real64 Interp1D(Real64 x, Real64 Xvec[], Real64 Yvec[], UInt32 Start_idx, Real64 dX);

		//Type Interp1D(...);
	}
};

void InterpolationUnitest();

#endif
