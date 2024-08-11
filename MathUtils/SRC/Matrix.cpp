#include "Matrix.h"

void MatrixUnittest()
{
	LogMoveLine("---------------------------------------------------------------------");
	LogMoveLine("-------------------------- Matrix unittest --------------------------");
	LogMoveLine("---------------------------------------------------------------------");

	Real64 Vec1[3] = { 1.0, 2.0, 3.0 }, Vec2[3] = { 4.0, 5.0, 6.0 }/*, * VecOut*/;
	Matrix<Real64> MatR(3, 4), MatL(4, 3), MatResAdd(3, 4), MatResMul(3, 3);
	Matrix<Real64> DblMat1(3, 3), DblMat2(3, 4), DblMat3(2, 3), DblMat4(4, 4), DblMat5(3, 3), DblMat6(4, 3);
	Matrix<Real64> Q, R, L, U;
    DblMat1[0][0] = DblMat1(1, 1) = DblMat1[2][2] = 1.0;
	DblMat2[0][0] = 1.0, DblMat2[0][1] = 2.0, DblMat2[0][2] = 3.0, DblMat2[0][3] = 4.0;
	DblMat3[0][0] = 1.0, DblMat3[0][1] = 2.0, DblMat3[0][2] = 3.0, DblMat3[1][0] = 4.0, DblMat3[1][1] = 5.0, DblMat3[1][2] = 6.0;
	DblMat4[0][0] = 1.0, DblMat4[0][1] = 2.0, DblMat4[0][2] = 3.0, DblMat4[0][3] = 4.0, DblMat4[1][1] = 1.0, DblMat4[2][2] = 1.0, DblMat4[3][3] = 1.0;
	DblMat5[0][0] = 1.0, DblMat5[0][1] = 2.0, DblMat5[0][2] = 3.0;
	DblMat5[1][0] = 2.0, DblMat5[1][1] = 1.0, DblMat5[1][2] = 2.0;
	DblMat5[2][0] = 3.0, DblMat5[2][1] = 2.0, DblMat5[2][2] = 1.0;

	DblMat6[0][0] = 1.0, DblMat6[0][1] = 2.0, DblMat6[0][2] = 1.0;
	DblMat6[1][0] = 2.0, DblMat6[1][1] = 4.0, DblMat6[1][2] = 2.0;
	DblMat6[2][0] = 4.0, DblMat6[2][1] = 5.0, DblMat6[2][2] = 6.0;
	DblMat6[3][0] = 7.0, DblMat6[3][1] = 8.0, DblMat6[3][2] = 9.0;

	LogMoveLine("DblMat1 = \n" << DblMat1);
	LogMoveLine("DblMat2 = \n" << DblMat2);
	LogMoveLine("DblMat3 = \n" << DblMat3);

	DblMat1 *= 2;
	LogMoveLine("DblMat1 *= 2: \n" << DblMat1);
	//LogMoveLine("DblMat1[0] = " << DblMat1[0] << ", DblMat1[1] = " << DblMat1[1] << ", DblMat1[4] = " << DblMat1[4]);
	LogMoveLine("DblMat1(0,0) = " << DblMat1(0, 0) << ", DblMat1(0,1) = " << DblMat1(0, 1) << ", DblMat1(1,1)	= " << DblMat1(1, 1) << "\n");

	LogMoveLine("DblMat1*DblMat2 = \n" << (DblMat1 * DblMat2));
	LogMoveLine("Element-wise multiplication DblMat1.*DblMat1 = DblMat1.EMultiply(DblMat1) = \n" << (DblMat1.EMultiply(DblMat1)));
	LogMoveLine("Element-wise dibision DblMat2./DblMat2 = DblMat2.EDivide(DblMat2) = \n" << (DblMat2.EDivide(DblMat2)));
	LogMoveLine("DblMat1: \n" << DblMat1);
	DblMat2 = DblMat1;
	LogMoveLine("DblMat2 = DblMat1 -> \n" << DblMat2);

	LogMoveLine(DblMat3);

	LogMoveLine("Swap (0,0) with (0,1): \n" << DblMat3.Swap(0, 0, 0, 1));
	LogMoveLine("And back: \n" << DblMat3.Swap(0, 0, 0, 1));

	LogMoveLine("Swap rows 0 & 1: \n" << (DblMat3.SwapRows(0, 1)));
	DblMat3.SwapRows(1, 0); // swap back
	LogMoveLine("Swap columns 0 & 2: \n" << (DblMat3.SwapColumns(0, 2)));
	DblMat3.SwapColumns(2, 0); // swap back

	LogMoveLine("DblMat3.Transpose() = \n" << (DblMat3.Transpose()));
	LogMoveLine("Double tarnspose DblMat3.Transpose().Transpose(): \n" << DblMat3.Transpose().Transpose());

	LogMoveLine("DblMat4: \n" << DblMat4);
	LogMoveLine("DblMat4 minor matrix at (1,2): \n" << DblMat4.Minor(1, 2));
	LogMoveLine("DblMat4.Det() = " << DblMat4.Det());
	LogMoveLine("DblMat2.Det() = " << DblMat2.Det());

	LogMoveLine("DblMat5 = \n" << DblMat5);
	LogMoveLine("DblMat5 + DblMat1 = \n" << DblMat5 + DblMat1);
	LogMoveLine("DblMat5 - DblMat1 = \n" << DblMat5 - DblMat1);

	// Comparing execution time for regular multiplication vs assignment multiplicaiton
	//std::chrono::high_resolution_clock::time_point Start1 = Utilities::Time::TStart();

	//DblMat1* DblMat5;
	//Utilities::Time::TStop(Start1);

	//std::chrono::high_resolution_clock::time_point Start2 = Utilities::Time::TStart();
	//DblMat1 *= DblMat5;
	//Utilities::Time::TStop(Start2);

	//VecOut = DblMat5 * Vec1;
	//LogMoveLine("Multiplying DblMat5 by vector: \n" << VecOut[0] << ",\n " << VecOut[1] << ",\n " << VecOut[2]);
	LogMoveLine("DblMat5.Det() = " << DblMat5.Det());
	LogMoveLine("DblMat5.Adjugate(): \n" << DblMat5.Adjugate());
	LogMoveLine("DblMat5.Invert(): \n" << DblMat5.Invert());

	LogMoveLine("DblMat5: \n"	<<	DblMat5);
	LogMoveLine("DblMat5^0: \n" << (DblMat5^0));
	LogMoveLine("DblMat5^2: \n" << (DblMat5^2));
	LogMoveLine("DblMat5^1: \n" << (DblMat5^1));
	LogMoveLine("DblMat5^-1: \n" << (DblMat5^-1));
	LogMoveLine("DblMat5^-2: \n" << (DblMat5 ^ -2));
	DblMat5.QR_Decompose(Q, R);
	LogMoveLine("QR decomposition of DblMat5: \nQ:\n" << Q << "R:\n" << R);
	DblMat5.LU_Decompose(L, U);
	LogMoveLine("LU decomposition of DblMat5: \nL:\n" << L << "U:\n" << U);

	LogMoveLine("DblMat5.Rank() = " << DblMat5.Rank());
	
	LogMoveLine("----------------------------------------------------------------");
	LogMoveLine("DblMat6: \n" << DblMat6);
	DblMat6.QR_Decompose(Q, R);
	LogMoveLine("QR decomposition of DblMat6: \nQ:\n" << Q << "R:\n" << R);
	LogMoveLine("DblMat6.Rank() = " << DblMat6.Rank());
	LogMoveLine("QR = DblMat6: \n" << Q*R);
	LogMoveLine("----------------------------------------------------------------");
	LogMoveLine("Same process for DblMat6.Transpose: \n");
	LogMoveLine("DblMat6.Transpose(): \n" << DblMat6.Transpose());
	DblMat6.Transpose().QR_Decompose(Q, R);
	LogMoveLine("QR decomposition of DblMat6.Transpose(): \nQ:\n" << Q << "R:\n" << R);
	LogMoveLine("DblMat6.Transpose().Rank() = " << DblMat6.Transpose().Rank());
	LogMoveLine("QR = DblMat6 (does not give back the transposed matrix): \n" << Q*R);

	LogMoveLine("----------------------------------------------------------------");
	Real64 Mat[4*3] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
	Matrix<Real64> DblMat7(4, 3, Mat);
	LogMoveLine("DblMat7 init [Matrix<Real64> DblMat7(" << DblMat7.Nrows << ", " << DblMat7.Ncolumns << " , MatRef)]: \n" << DblMat7);
	DblMat7.LU_Decompose(L, U);
	LogMoveLine("LU decomposition of DblMat7: \nL:\n" << L << "U:\n" << U);
	LogMoveLine("DblMat7 = L*U: \n" << L*U);
	LogMoveLine("----------------------------------------------------------------");

}