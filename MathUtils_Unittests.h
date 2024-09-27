#ifndef _MATH_UTILS_UNITTESTS_
#define _MATH_UTILS_UNITTESTS_

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

void PresentTestResult(const char* str, SM_Matrix<>& Res);

bool CompareResult(SM_Matrix<>& result, double ref, const char* expression);
bool CompareResult(double* result, double* ref, int size, const char* expression);

template<size_t N>
bool CompareResult(SM_Matrix<>& result, double (*ref)[N], const char* expression)
{
	int i, j;

	for (i = 0; i < result.Nrows; i++)
	{
		for (j = 0; j < result.Ncolumns; j++)
		{
			if (abs(result[i][j] - ref[i][j]) > Math::EPS_f)
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
