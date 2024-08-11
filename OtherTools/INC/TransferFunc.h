#ifndef _TRANSFER_FUNC_H
#define _TRANSFER_FUNC_H

#include "Utilities.h"

enum E_TF_TransformType
{
    DTF_Bilinear,   /* Bilinear transformation (Tustin) */
    DTF_ZOH,        /* Zero order hold */
    DTF_FOH,        /* First order hold */
    DTF_Impulse,    /* Impulse invariant discretization */
};

class CTransferFunc
{
private:
    UInt32 m_uiNumZeros, m_uiNumPoles;
    Real64 *InputMemory, *OutputMemory;
    Real64 *m_dNumerator, *m_dDenominator;  /* Discrete polinomial coefficients */
    Real64 Kd;                              /* Discrete TF gain */
public:
    //CTransferFunc(Real64 dt);
    CTransferFunc(Real64 dt, E_TF_TransformType TransformType = DTF_Bilinear, Real64 FreeGain = 1.0,
                  std::vector<Real64> ZerosVec = {}, std::vector<Real64> PolesVec = { -1.0 });

    ~CTransferFunc();

    Real64 Forward(Real64 Input);
};

#endif
