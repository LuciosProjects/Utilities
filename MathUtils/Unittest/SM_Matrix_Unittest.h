#ifndef _SM_MATRIX_UNITTEST
#define _SM_MATRIX_UNITTEST

#include "SM_Matrix.hpp"

using SM_Matrix = Math::SM_Matrix<>;

/****************************************************************/
/************************ Unittest macros ***********************/
/****************************************************************/
#define _SM_Matrix_PI 3.14159265358979323846264338

/****************************************************************/
/********************* Unittest declarations ********************/
/****************************************************************/

bool SM_Matrix_UT();
namespace SM_Matrix_Unittests
{
	bool ConstructionTest();
	bool AssignmentTest();
	bool AdditionTest();
	bool SubtractionTest();
	bool MultiplicationTest();
	bool InversionTest();
	bool DivisionTest();
	bool ExponentTest();
	bool MiscTest();

	// assignment unittests
}

void PresentTestResult(const char* str, SM_Matrix& Res);

bool CompareResult(SM_Matrix& result, double ref, const char* expression);
bool CompareResult(double* result, double* ref, int size, const char* expression);

template<size_t N>
bool CompareResult(SM_Matrix& result, double (*ref)[N], const char* expression)
{
	int i, j;

	for (i = 0; i < result.Nrows; i++)
	{
		for (j = 0; j < result.Ncolumns; j++)
		{
			if (abs(result[i][j] - ref[i][j]) > 1e-6)
			{
				std::cout << expression << " failed" << std::endl;
				std::cout << "Result: \n" << result << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < result.Nrows; i++)
				{
					std::cout << "\n" << ref[i][0];
					for (j = 1; j < result.Ncolumns; j++)
					{
						std::cout << ", " << ref[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	std::cout << expression << " succeeded" << "\n" << result << std::endl;
	return true;
}

#endif
