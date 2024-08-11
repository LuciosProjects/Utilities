#include "TransferFunc.h"

//CTransferFunc::CTransferFunc(Real64 dt)
//{
//    /* This default constructor constructs a transfer function of the form:
//        
//                            1
//                        ---------
//                        S   +   1
//       
//       using the bilinear transformation (Tustin)
//    */
//
//    InputMemory     = new Real64[1];
//    OutputMemory    = new Real64[1];
//    m_dNumerator    = new Real64[2];
//    m_dDenominator  = new Real64[2];
//
//    m_uiNumZeros = 0;
//    m_uiNumPoles = 1;
//
//    *InputMemory = 0.0;
//    *OutputMemory = 0.0;
//
//    Kd = (dt * 0.25); /* dt * 0.5 * 0.5 */
//
//    m_dNumerator[0] = m_dNumerator[1] = 1.0;
//    m_dDenominator[0] = 1.0;
//    m_dDenominator[1] = 0.0;
//}

CTransferFunc::CTransferFunc(Real64 dt, E_TF_TransformType TransformType, Real64 FreeGain,
                             std::vector<Real64> ZerosVec, std::vector<Real64> PolesVec)
{
    if (PolesVec.size() < ZerosVec.size())
    {
        LogMoveLine("ERROR: Invalid transfer function initialization,\n number of poles must be equal or larger than number of zeros.");
        LogMoveLine("Program is terminating");
        std::exit(1);
    }
    else
    {
        m_uiNumZeros = ZerosVec.size();
        m_uiNumPoles = PolesVec.size();
    }

    switch (TransformType)
    {
        case DTF_Bilinear:
        {
            break;
        }
        case DTF_ZOH:
        {
            break;
        }
        case DTF_FOH:
        {
            break;
        }
        case DTF_Impulse:
        {
            break;
        }
    }
}

CTransferFunc::~CTransferFunc()
{
    delete[] InputMemory;
    delete[] OutputMemory;
    delete[] m_dNumerator;
    delete[] m_dDenominator;
}

Real64 CTransferFunc::Forward(Real64 Input)
{
    return 0.0;
}