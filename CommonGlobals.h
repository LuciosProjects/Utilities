#ifndef COMMONGLOBALS_H
#define COMMONGLOBALS_H


namespace MathConsts
{
    constexpr Real64 PI			= 3.14159265358979323846264338;
    constexpr Real64 PI_x2      = 2 * PI;
    constexpr Real64 EULER		= 2.71828182845904523536028747;

    constexpr Real64 RAD2DEG	= 180.0 / PI;
    constexpr Real64 DEG2RAD	= PI / 180.0;

    constexpr Real64 EPS_d		= 1.0e-12; //
    constexpr Real64 EPS_f		= 1.0e-6;
}

// Time conversions
namespace TimeConversions {
	// From hour scale
	constexpr UInt64x2 Hours2Minutes		= 60;
	constexpr UInt64x2 Hours2Seconds		= 3600;
	constexpr UInt64x2 Hours2Milliseconds	= 3600000;
	constexpr UInt64x2 Hours2Microseconds	= 3600000000;
	constexpr UInt64x2 Hours2Nanoseconds	= 3600000000000;

	// From Minute scale
	constexpr LReal64  Minutes2Hours		= 1.0 / 60.0;
	constexpr UInt64x2 Minutes2Seconds	    = 60;
	constexpr UInt64x2 Minutes2Milliseconds = 60000;
	constexpr UInt64x2 Minutes2Microseconds = 60000000;
	constexpr UInt64x2 Minutes2Nanoseconds  = 60000000000;

	// From Seconds scale
	constexpr LReal64  Seconds2Hours		= 1.0 / 3600.0;
	constexpr LReal64  Seconds2Minutes		= 1.0 / 60.0;
	constexpr UInt64x2 Seconds2Milliseconds = 1000;
	constexpr UInt64x2 Seconds2Microseconds = 1000000;
	constexpr UInt64x2 Seconds2Nanoseconds  = 1000000000;

	// From Milliseconds scale
	constexpr LReal64  Milliseconds2Hours			= 1.0 / 3600000.0;
	constexpr LReal64  Milliseconds2Minutes			= 1.0 / 60000.0;
	constexpr LReal64  Milliseconds2Seconds			= 1.0 / 1000.0;
	constexpr UInt64x2 Milliseconds2Microseconds	= 1000;
	constexpr UInt64x2 Milliseconds2Nanoseconds		= 1000000;

	// From Microseconds scale
	constexpr LReal64  Microseconds2Hours			= 1.0 / 3600000000.0;
	constexpr LReal64  Microseconds2Minutes			= 1.0 / 60000000.0;
	constexpr LReal64  Microseconds2Seconds			= 1.0 / 1000000.0;
	constexpr LReal64  Microseconds2Milliseconds	= 1.0 / 1000.0;
	constexpr UInt64x2 Microseconds2Nanoseconds		= 1000;

	// From Nanoseconds scale
	constexpr LReal64 Nanoseconds2Hours			= 1.0 / 3600000000000.0;
	constexpr LReal64 Nanoseconds2Minutes		= 1.0 / 60000000000.0;
	constexpr LReal64 Nanoseconds2Seconds		= 1.0 / 1000000000.0;
	constexpr LReal64 Nanoseconds2Milliseconds	= 1.0 / 1000000.0;
	constexpr LReal64 Nanoseconds2Microseconds	= 1.0 / 1000.0;
}

/* Random conversions */
namespace RandomConversions
{
    constexpr Real64 RPM2Rad_per_Sec = MathConsts::PI / 30.0; /* Effectively 2xPI/60 */
}

// Other

#endif