#ifndef EARTH_GEOMETRY_H
#define EARTH_GEOMETRY_H

#include <math.h>

#include "TypeDefinitions.h"

// Sources -    https://en.wikipedia.org/wiki/Gravity_of_Earth
namespace EarthGeometry {
    constexpr Real64 OmegaEarth         = 0.000072921159; // [rad/sec]
    constexpr Real64 SemiAxe_a          = 6378137.0; // [m]
    constexpr Real64 SemiAxe_b          = 6356752.314245; // [m]
    constexpr Real64 EarthRadius0       = 6356766.0; // [m]
    constexpr Real64 SL_Grav            = 9.80665; // [m/s^2]
    constexpr Real64 Grav_at_Poles      = 9.8321849378; // [m/s^2]
    constexpr Real64 Grav_at_Equator    = 9.7803267715; // [m/s^2]
    constexpr Real64 Sq_eccentricity    = 1.0 - ((SemiAxe_b * SemiAxe_b) / (SemiAxe_a * SemiAxe_a));
    constexpr Real64 k_const            = (SemiAxe_b * Grav_at_Poles - SemiAxe_a * Grav_at_Equator) / (SemiAxe_a * Grav_at_Equator);
    
    Real64 CalcGravity_Simple(const Real64 Z); // [m/s^2]
    Real64 CalcGravity(const Real64& lat); // [m/s^2]
}

#endif