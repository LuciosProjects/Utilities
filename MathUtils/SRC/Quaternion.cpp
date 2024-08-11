#include "Utilities.h"

Quaternion::Quaternion()
{
    Real_1 = 0.0;
    Imag_i = 0.0;
    Imag_j = 0.0;
    Imag_k = 0.0;
}

Quaternion::Quaternion(Real64 in_Real_1, Real64 in_Imag_i, Real64 in_Imag_j, Real64 in_Imag_k)
                        : Real_1(in_Real_1), Imag_i(in_Imag_i), Imag_j(in_Imag_j), Imag_k(in_Imag_k) {}

Quaternion::~Quaternion()
{

}

void Quaternion::setRotation(Real64& Ax_1, Real64& Ax_2, Real64& Ax_3)
{
    //Quaternion Q_rotation_Ax_1(cos(Ax_1 * 0.5), sin(Ax_1 * 0.5),    0.0,                0.0);
    //Quaternion Q_rotation_Ax_2(cos(Ax_2 * 0.5), 0.0,                sin(Ax_2 * 0.5),    0.0);
    //Quaternion Q_rotation_Ax_3(cos(Ax_3 * 0.5), 0.0,                0.0,                sin(Ax_3 * 0.5));
    //Quaternion Q_rotation_tot = (Q_rotation_Ax_1 * Q_rotation_Ax_2) * Q_rotation_Ax_3;

    Real64 C_half_1 = cos(Ax_1 * 0.5); // 1 indicactes first rotation
    Real64 S_half_1 = sin(Ax_1 * 0.5);
    Real64 S_half_2 = sin(Ax_2 * 0.5); // 2 indicates second rotation
    Real64 C_half_2 = cos(Ax_2 * 0.5);
    Real64 S_half_3 = sin(Ax_3 * 0.5); // 3 indicates third rotation
    Real64 C_half_3 = cos(Ax_3 * 0.5);

    Real_1 = C_half_1 * C_half_2 * C_half_3 + S_half_1 * S_half_2 * S_half_3;
    //Imag_i = C_half_1 * C_half_2 * S_half_3 - S_half_1 * S_half_2 * C_half_3;
    Imag_i = S_half_1 * C_half_2 * C_half_3 - C_half_1 * S_half_2 * S_half_3;
    Imag_j = C_half_1 * S_half_2 * C_half_3 + S_half_1 * C_half_2 * S_half_3;
    //Imag_k = S_half_1 * C_half_2 * C_half_3 - C_half_1 * S_half_2 * S_half_3;
    Imag_k = C_half_1 * C_half_2 * S_half_3 - S_half_1 * S_half_2 * C_half_3;
}

BOOLEAN Quaternion::isUnitQuat()
{
    Real64 QNorm = norm();
    return (QNorm >= (1.0 - Math::EPS_d) && QNorm <= (1.0 + Math::EPS_d));
}

/****************************************************************/
/********************* Operator overloading *********************/
/****************************************************************/
Quaternion Quaternion::operator=(Quaternion other)
{
    Real_1 = other.Real_1;
    Imag_i = other.Imag_i;
    Imag_j = other.Imag_j;
    Imag_k = other.Imag_k;

    return *this;
}

Quaternion Quaternion::operator+(Quaternion& other)
{
    Quaternion res;
    
    res.Real_1 = Real_1 + other.Real_1;
    res.Imag_i = Imag_i + other.Imag_i;
    res.Imag_j = Imag_j + other.Imag_j;
    res.Imag_k = Imag_k + other.Imag_k;

    return res;
}

Quaternion Quaternion::operator+=(Quaternion& other)
{
    Real_1 += other.Real_1;
    Imag_i += other.Imag_i;
    Imag_j += other.Imag_j;
    Imag_k += other.Imag_k;

    return *this;
}

Quaternion Quaternion::operator-(Quaternion& other)
{
    Quaternion res;

    res.Real_1 = Real_1 - other.Real_1;
    res.Imag_i = Imag_i - other.Imag_i;
    res.Imag_j = Imag_j - other.Imag_j;
    res.Imag_k = Imag_k - other.Imag_k;

    return res;
}

Quaternion Quaternion::operator-=(Quaternion& other)
{
    Real_1 -= other.Real_1;
    Imag_i -= other.Imag_i;
    Imag_j -= other.Imag_j;
    Imag_k -= other.Imag_k;

    return *this;
}

Quaternion Quaternion::operator/(Real64 k)
{
    Quaternion res;

    res.Real_1 = Real_1 / k;
    res.Imag_i = Imag_i / k;
    res.Imag_j = Imag_j / k;
    res.Imag_k = Imag_k / k;

    return res;
}

Quaternion Quaternion::operator/=(Real64 k)
{
    Real_1 /= k;
    Imag_i /= k;
    Imag_j /= k;
    Imag_k /= k;

    return *this;
}

Quaternion Quaternion::operator*(Real64 k)
{
    Quaternion res;

    res.Real_1 = Real_1 * k;
    res.Imag_i = Imag_i * k;
    res.Imag_j = Imag_j * k;
    res.Imag_k = Imag_k * k;

    return res;
}

Quaternion Quaternion::operator*=(Real64 k)
{
    Real_1 *= k;
    Imag_i *= k;
    Imag_j *= k;
    Imag_k *= k;

    return *this;
}

Quaternion Quaternion::operator*(Quaternion& other)
{
    Quaternion res;

    res.Real_1 = Real_1 * other.Real_1 - Imag_i * other.Imag_i - Imag_j * other.Imag_j - Imag_k * other.Imag_k;
    res.Imag_i = Real_1 * other.Imag_i + Imag_i * other.Real_1 + Imag_j * other.Imag_k - Imag_k * other.Imag_j;
    res.Imag_j = Real_1 * other.Imag_j - Imag_i * other.Imag_k + Imag_j * other.Real_1 + Imag_k * other.Imag_i;
    res.Imag_k = Real_1 * other.Imag_k + Imag_i * other.Imag_j - Imag_j * other.Imag_i + Imag_k * other.Real_1;

    return res;
}

Quaternion Quaternion::operator*=(Quaternion& other)
{
    Real64 t_Real_1(Real_1), t_Imag_i(Imag_i), t_Imag_j(Imag_j), t_Imag_k(Imag_k);

    Real_1 = t_Real_1 * other.Real_1 - t_Imag_i * other.Imag_i - t_Imag_j * other.Imag_j - t_Imag_k * other.Imag_k;
    Imag_i = t_Real_1 * other.Imag_i + t_Imag_i * other.Real_1 + t_Imag_j * other.Imag_k - t_Imag_k * other.Imag_j;
    Imag_j = t_Real_1 * other.Imag_j - t_Imag_i * other.Imag_k + t_Imag_j * other.Real_1 + t_Imag_k * other.Imag_i;
    Imag_k = t_Real_1 * other.Imag_k + t_Imag_i * other.Imag_j - t_Imag_j * other.Imag_i + t_Imag_k * other.Real_1;

    return *this;
}

/*********************************************************/
/********************* Utility functions *****************/
/*********************************************************/
Real64 Quaternion::sqrNorm()
{
    return (SQR(Real_1) + SQR(Imag_i) + SQR(Imag_j) + SQR(Imag_k));
}

Real64 Quaternion::norm()
{
    return SQRT(this->sqrNorm());
}

Quaternion Quaternion::Conjugate()
{
    return Quaternion(Real_1, -Imag_i, -Imag_j, -Imag_k);
}

Quaternion Quaternion::Invert()
{
    Real64 sqrNorm = this->sqrNorm();

    // sqrNorm is always positive so no ABS() needed
    return ((sqrNorm > Math::EPS_d) ? this->Conjugate()/sqrNorm : this->Conjugate());
}

Quaternion Quaternion::unitQuat()
{
    *this /= this->norm();
    return *this;
}

//Matrix<Real64> Quaternion::getRotMat()
//{
//    Matrix<Real64> res(3,3);
//
//    if (isUnitQuat())
//    {
//        // Calculate rotation matrix
//        res[0][0] = 1.0 - 2.0 * (SQR(Imag_j) + SQR(Imag_k)); // SQR(Real_1) + SQR(Imag_i) - SQR(Imag_j) - SQR(Imag_k)
//        res[0][1] = 2.0 * (Imag_i * Imag_j - Real_1 * Imag_k);
//        res[0][2] = 2.0 * (Real_1 * Imag_j + Imag_i * Imag_k);
//        res[1][0] = 2.0 * (Imag_k * Real_1 + Imag_i * Imag_j);
//        res[1][1] = 1.0 - 2.0 * (SQR(Imag_i) + SQR(Imag_k)); // SQR(Real_1) - SQR(Imag_i) + SQR(Imag_j) - SQR(Imag_k)
//        res[1][2] = 2.0 * (Imag_j * Imag_k - Real_1 * Imag_i);
//        res[2][0] = 2.0 * (Imag_i * Imag_k - Real_1 * Imag_j);
//        res[2][1] = 2.0 * (Real_1 * Imag_i + Imag_j * Imag_k);
//        res[2][2] = 1.0 - 2.0 * (SQR(Imag_i) + SQR(Imag_j)); // SQR(Real_1) - SQR(Imag_i) - SQR(Imag_j) + SQR(Imag_k)
//
//        return res;
//    }
//    else
//    {
//        std::cout << "ERROR: not a unit quaternion!" << std::endl;
//    }
//}

Quaternion Quaternion::derivative(Quaternion& Q_angRate)
{
    return (Q_angRate * (*this)) * 0.5;
}