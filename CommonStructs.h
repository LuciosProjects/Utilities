#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

struct T_XYZ {
    Real64 x;
    Real64 y;
    Real64 z;
};

struct T_NED {
    Real64 North;
    Real64 East;
    Real64 Down;
};

struct T_LLA {
    Real64 lat;
    Real64 lon;
    Real64 alt_asl;
};

struct T_Euler {
    Real64 Phi;
    Real64 Theta;
    Real64 Psi;
};

struct T_Attitude {
    Real64 roll;
    Real64 pitch;
    Real64 yaw;
};

#endif
