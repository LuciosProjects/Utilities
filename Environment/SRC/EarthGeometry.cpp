#include "EarthGeometry.h"

Real64 EarthGeometry::CalcGravity_Simple(const Real64 Z)
{
    Real64 ratio = EarthGeometry::EarthRadius0 / (Z + EarthGeometry::EarthRadius0);
    return EarthGeometry::SL_Grav * ratio * ratio;
}

Real64 EarthGeometry::CalcGravity(const Real64& lat)
{
    // latitude is given in radians
    Real64 sinlat   = sin(lat);

    return (EarthGeometry::Grav_at_Equator * ((1.0 + EarthGeometry::k_const * sinlat * sinlat) /
                                                sqrt(1.0 - EarthGeometry::Sq_eccentricity * sinlat * sinlat)));
}