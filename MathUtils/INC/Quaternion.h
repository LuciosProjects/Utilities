#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion
{
private:
    BOOLEAN isUnitQuat();
    
public:
    Quaternion();
    Quaternion(Real64 in_Real_1, Real64 in_Imag_i, Real64 in_Imag_j, Real64 in_Imag_k);

    ~Quaternion();

    void setRotation(Real64& Ax_1, Real64& Ax_2, Real64& Ax_3);
    Real64 sqrNorm();
    Real64 norm();
    Quaternion Conjugate();
    Quaternion Invert();
    Quaternion unitQuat();
    Quaternion derivative(Quaternion& Q_angRate);

    //Matrix<Real64> getRotMat();


    Quaternion operator=(Quaternion other);
    Quaternion operator+(Quaternion& other);
    Quaternion operator+=(Quaternion& other);
    Quaternion operator-(Quaternion& other);
    Quaternion operator-=(Quaternion& other);
    Quaternion operator/(Real64 k);
    Quaternion operator/=(Real64 k);
    Quaternion operator*(Real64 k);
    Quaternion operator*=(Real64 k);
    Quaternion operator*(Quaternion& other);
    Quaternion operator*=(Quaternion& other);

    Real64 Real_1, Imag_i, Imag_j, Imag_k;
};

#endif
