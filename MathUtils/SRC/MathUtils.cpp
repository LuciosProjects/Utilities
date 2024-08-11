#include "Utilities.h"

//inline Real64 Math::InvSqrt(Real64 num)
//{
//	//if (num < 0) {
//	//	std::cout << "error in Math::InvSqrt(num), negative argument, this function does not support complex numbers." << std::endl;
//	//	std::exit(1);
//	//}
//
//	Real64 InvSr = num;
//	Real64 num2 = num * 0.5;
//	SInt64x2 i = *(SInt64x2*)&InvSr;						// Converting adress of floating point variable (must be a regular number) to integer
//
//	i = InvSqrtDoubleMagicNum - (i >> 1);					// Implementation of y = = sqrt(x) in binary
//	InvSr = *(Real64*)&i;									// Converting back to floating point variable
//	InvSr = InvSr * (1.5 - (InvSr * InvSr * num2));			// Newton-Raphson iteration 1
//	InvSr = InvSr * (1.5 - (InvSr * InvSr * num2));			// Newton-Raphson iteration 2
//
//	return InvSr;
//}
//
//inline Real32 Math::InvSqrt(Real32 num)
//{
//	//if (num < 0) {
//	//	std::cout << "error in Math::InvSqrt(num), negative argument, this function does not support complex numbers." << std::endl;
//	//	std::exit(1);
//	//}
//
//	Real32 InvSr = num;
//	Real32 num2 = num * 0.5;
//	SInt64 i = *(SInt64*)&InvSr;							// Converting adress of floating point variable (must be a regular number) to integer
//
//	i = InvSqrtFloatMagicNum - (i >> 1);					// Implementation of y = = sqrt(x) in binary
//	InvSr = *(Real32*)&i;									// Converting back to floating point variable
//	InvSr = InvSr * (1.5f - (InvSr * InvSr * num2));		// Newton-Raphson iteration 1
//	InvSr = InvSr * (1.5f - (InvSr * InvSr * num2));		// Newton-Raphson iteration 2
//
//	return InvSr;
//}
//
//void MathUtilsUnittest()
//{
//	// RNG definition
//	std::random_device rd;
//	std::mt19937_64 gen(rd());
//	std::uniform_real_distribution<Real64> dis(0.0f, 1000.0f);
//
//	// Testing fast square root function
//	constexpr UInt32 VecSize = 100000000;
//	UInt32 i;
//	Real64 MaxErr = 0.0, Error = 0.0, AvgTime_FastSqrt = 0.0, AvgTime_RefSqrt = 0.0;
//
//	std::chrono::high_resolution_clock::time_point Start_FastSqrt, Start_RefSqrt;
//	UInt64x2 duration_ns_FastSqrt, duration_ns_RefSqrt;
//	Real64* X = new Real64[VecSize], * X_sr = new Real64[VecSize], * X_sr_Ref = new Real64[VecSize];
//	//Real32* X = new Real32[VecSize], * X_sr = new Real32[VecSize], * X_sr_Ref = new Real32[VecSize];
//	
//
//	for (i = 0; i < VecSize; i++) {
//		X[i] = dis(gen);
//	}
//
//	Start_FastSqrt = Utilities::Time::TStart();
//	for (i = 0; i < VecSize; i++) {
//		X_sr[i]	= Math::InvSqrt(X[i]);
//	}
//	duration_ns_FastSqrt = Utilities::Time::GetDuration(Start_FastSqrt);
//	AvgTime_FastSqrt = duration_ns_FastSqrt * TimeConversions::Nanoseconds2Milliseconds;
//
//	Start_RefSqrt = Utilities::Time::TStart();
//	for (i = 0; i < VecSize; i++) {
//		X_sr_Ref[i] = 1/sqrt(X[i]);
//	}
//	duration_ns_RefSqrt = Utilities::Time::GetDuration(Start_RefSqrt);
//	AvgTime_RefSqrt = duration_ns_RefSqrt * TimeConversions::Nanoseconds2Milliseconds;
//
//	for (i = 0; i < VecSize; i++) {
//		Error = abs(X_sr_Ref[i] - X_sr[i]);
//		if (Error > MaxErr) {
//			MaxErr = Error;
//		}
//	}
//
//	LogMoveLine("Math::Sqrt(): \n" << "Mean time: " << AvgTime_FastSqrt << " [miliseconds]\nMax error - " << MaxErr);
//	LogMoveLine("Reference Sqrt(): \n" << "Mean time: " << AvgTime_RefSqrt << " [miliseconds]");
//
//	delete[] X, X_sr, X_sr_Ref;
//}
