#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "Matrix.h"

#define SQR(X)	X * X
#define SQRT(X) sqrt((Real64)X)

//constexpr SInt64	SqrtFloatMagicNum		= 0x427DE9F7;
constexpr SInt64	InvSqrtFloatMagicNum	= 0x5f3759df;
//constexpr SInt64x2  SqrtDoubleMagicNum	= 0x404FBD3EE730FC21;
constexpr SInt64x2	InvSqrtDoubleMagicNum	= 0x5fe6eb50c7b537a9;

namespace Math
{

	// Constants
	//const Real64 Rad2Deg    = MathConsts::RAD2DEG;
	//const Real64 Deg2Rad    = MathConsts::DEG2RAD;
	//const Real64 Euler	    = MathConsts::EULER;
	//const Real64 EPS_d	    = MathConsts::EPS_d;
	//const Real64 EPS_f	    = MathConsts::EPS_f;
    using namespace MathConsts;

	// General math utilities
	template <typename Type> /* Maximal value between 2 numbers */
	inline Type Max(Type a, Type b) { return (((a) > (b)) ? (a) : (b)); }

    template <typename Type> /* Minimal value between 2 numbers */
    inline Type Min(Type a, Type b) { return (((a) < (b)) ? (a) : (b)); }

    template <typename Type> /* Saturation function */
    inline Type Saturate(Type num, Type lower, Type upper) { return Max(Min(num, upper), lower); }

	template <typename Type> /* Division protection function */
	inline Type DivProtect(Type num, Type den) { return (abs(den) < EPS_d) ? num : (num / den); }

	template <typename Type> /* Scalar input Relu */
	inline Type Relu_s(Type num) { return Max(0,num); }
	
	template <typename Type> /* Sign function */
	inline Type Sign(Type num) { return (num >= 0) ? 1 : -1; }

	// Element sum of a vectors
	template <typename Type>
	Type VecSum(const Type Vec[], const UInt32 size)
	{
		UInt32 i;
		Type Sum = 0;
		for (i = 0; i < size; i++) {
			Sum += Vec[i];
		}
		return Sum;
	}

	// Element product of a vector
	template <typename Type>
	Type VecProd(const Type Vec[], const UInt32 size)
	{
		UInt32 i;
		Type Prod = 1;
		for (i = 0; i < size; i++) {
			Prod *= Vec[i];
		}
		return Prod;
	}

	template <typename Type>
	inline Type VecMean(const Type Vec[], const UInt32 size) { return  VecSum<Type>(Vec, size) / size; }

	// Fast inverse square root function (doesn't support complex numbers)
	//inline Real64 InvSqrt(Real64 num);
	//inline Real32 InvSqrt(Real32 num);

	// Fast square root function (doesn't support complex numbers)
	//template <typename Type>
	//inline Type Sqrt(Type num)
	//{
	//	return (Type)(1/Math::InvSqrt((Real32)num));
	//}
	
	// Norm of a vector (base 2)
	template <typename Type>
	Type VecNorm2(const Type Vec[], const UInt32 size)
	{
		UInt32 i;
		Type Norm = 0;
		for (i = 0; i < size; i++) {
			Norm += SQR(Vec[i]);
		}
		return sqrt(Norm);
	}

	// Unit vector
	template <typename Type>
	void UnitVec(const Type Vec[], const UInt32 size, Type Out[])
	{
		UInt32 i;
		Type Norm = VecNorm2(Vec, size);
		for (i = 0; i < size; i++) {
			Out[i] = Vec[i] / Norm;
		}
	}

	// softmax function
	template <typename Type>
	void softmax(const Type Vec[], const UInt32 size, Type Out[])
	{
		UInt32 i;
		Type ExpSum = 0;
		for (i = 0; i < size; i++) {
			Out[i] = (Type)EXP((Real64)Vec[i]);
			ExpSum += Out[i];
		}
		for (i = 0; i < size; i++) {
			Out[i] /= ExpSum;
		}
	}

	// Dot product
	template <typename Type>
	Type DotProd(const Type VecL[], const Type VecR[], UInt32 size)
	{
		UInt32 i;
		Type DotPr = 0;
		for (i = 0; i < size; i++) {
			DotPr += VecL[i] * VecR[i];
		}
		return DotPr;
	}

	// Cross product of R^3 entities
	template <typename Type>
	void CrossProd(const Type* VecL, const Type* VecR, Type* Prod)
	{
		*(Prod)     = *(VecL + 1)   * *(VecR + 2) - *(VecR + 1) * *(VecL + 2);
		*(Prod + 1) = *(VecL)       * *(VecR + 2) - *(VecR)     * *(VecL + 2);
		*(Prod + 2) = *(VecL)       * *(VecR + 1) - *(VecR)     * *(VecL + 1);
	}

	// Angle wrapper to [0.0 2Pi) (in radians only!)
	template <typename Type>
	Type WrapTo2Pi(const Type ang)
	{
		Type WrappedAng;

		if (ang > 0 && ang < 2 * PI) {
			return ang;
		}

		if (ang < 0 && ang > -2 * PI) {
			return -ang;
		}

		WrappedAng = ang - (2 * PI) * floor(ang / (2 * PI));
		return WrappedAng;
	}

	// Angle wrapper to [-Pi Pi] (in radians only!)
	template <typename Type>
	Type WrapToPi(const Type ang)
	{
		Type WrappedAng;

		WrappedAng = WrapTo2Pi(ang);
		if (WrappedAng > PI) {
			WrappedAng -= 2 * PI;
		}
		return WrappedAng;
	}
};

using namespace Math;

//void MathUtilsUnittest();

#endif
