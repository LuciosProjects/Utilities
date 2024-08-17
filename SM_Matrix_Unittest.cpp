#include <iostream>

#include "MathUtils_Unittests.h"
#include "SM_Matrix.hpp"

bool SM_Matrix_UT()
{
	bool Contruction_UT_Success;
	Contruction_UT_Success = SM_Matrix_Unittests::ConstructionTest();

	if (Contruction_UT_Success)
	{
		return true;
	}

	return false;
}

bool SM_Matrix_Unittests::ConstructionTest()
{
	bool MatCompare;
	
	Math::SM_Matrix<3, 3> Mat1;
	Math::SM_Matrix<5, 6> Mat2(SM_Matrix_UT_variables::nonSquare);
	Math::SM_Matrix<5, 6> Mat3(SM_Matrix_UT_variables::nonSquare[0]);
	Math::SM_Matrix<5, 6> Mat4(Mat2);

	//std::cout << Mat1 << std::endl;
	//std::cout << Mat2 << std::endl;
	//std::cout << Mat3 << std::endl;

	MatCompare = Mat2 == Mat4;

	if (MatCompare)
	{
		std::cout << "Construction test succeeded" << std::endl;
	}
	else
	{
		std::cout << "Construction test failed" << std::endl;
	}

	return MatCompare;
	//return false;
}