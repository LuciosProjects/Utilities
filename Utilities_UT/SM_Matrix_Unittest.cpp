#include "pch.h"
#include "SM_Matrix_Unittest.h"

/****************************************************************/
/********************** Unittest references *********************/
/****************************************************************/
namespace SM_Matrix_UT_variables
{
	double MutableMat[3][3] = { 0.0 };

	double ID_ref[3][3] = { {1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{0.0, 0.0, 1.0} };

	double ID_ref_1D[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

	double ZERO_ref[3][3] = {	{0.0, 0.0, 0.0},
								{0.0, 0.0, 0.0},
								{0.0, 0.0, 0.0} };

	double OnesMat[3][3] = {	{1.0, 1.0, 1.0},
								{1.0, 1.0, 1.0},
								{1.0, 1.0, 1.0} };

	double nonSquare[5][6] = {  { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
								{ 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 },
								{ 1.0, 0.0, 1.0, 0.0, 1.0, 0.0 },
								{ 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 },
								{ 1.0, 0.0, 1.0, 0.0, 1.0, 0.0} };

	// Addition
	double Addition_A[3][3] = { { 1.0, 2.0, 3.0 },
								{ 4.0, 5.0, 6.0 } ,
								{ 7.0, 8.0, 9.0 } };

	double Addition_B[3][3] = { { 9.0, 8.0, 7.0 },
								{ 6.0, 5.0, 4.0 } ,
								{ 3.0, 2.0, 1.0 } };

	double Addition_ApB_Result[3][3] = {{ 10.0, 10.0, 10.0 },
										{ 10.0, 10.0, 10.0 } ,
										{ 10.0, 10.0, 10.0 } };

	double Addition_C[3][3] = { { 1.0, 1.0, 1.0 },
								{ 1.0, 1.0, 1.0 } ,
								{ 1.0, 1.0, 1.0 } };

	double Addition_ApBpC_Result[3][3] = {	{ 11.0, 11.0, 11.0 },
											{ 11.0, 11.0, 11.0 } ,
											{ 11.0, 11.0, 11.0 } };

	double Addition_D[3][3] = { { 2.0, 2.0, 2.0 },
								{ 2.0, 2.0, 2.0 } ,
								{ 2.0, 2.0, 2.0 } };

	double Addition_ApBpCpD_Result[3][3] = {{ 13.0, 13.0, 13.0 },
											{ 13.0, 13.0, 13.0 } ,
											{ 13.0, 13.0, 13.0 } };

	double Addition_MatpK_Result[3][3] = {	{ 14.0, 14.0, 14.0 },
											{ 14.0, 14.0, 14.0 } ,
											{ 14.0, 14.0, 14.0 } };

	double Addition_MatpOnes_Result[3][3] = {	{ 15.0, 15.0, 15.0 },
												{ 15.0, 15.0, 15.0 } ,
												{ 15.0, 15.0, 15.0 } };

	double Addition_ref[3][3] = {	{10.0, 10.0, 10.0},
									{10.0, 10.0, 10.0},
									{10.0, 10.0, 10.0} };

	double Multiple_Additions_ref[3][3] = { {11.0, 11.0, 11.0},
											{11.0, 11.0, 11.0},
											{11.0, 11.0, 11.0} };

	// Multiplication
	double Multiplication_right[4][1] = {	{ 1.0 },
											{ 2.0 },
											{ 3.0 },
											{ 4.0 } };

	double Multiplication_left[1][4] = { { 1.0, 2.0, 3.0, 4.0 } };

	double Multiplication_ref_1[3][3] = { 0.0 };

	double Multiplication_ref_2[4][4] = {	{ 1.0, 2.0,  3.0,  4.0 },
											{ 2.0, 4.0,  6.0,  8.0 },
											{ 3.0, 6.0,  9.0, 12.0 },
											{ 4.0, 8.0, 12.0, 16.0 } };

	double Multiplication_ref_3[4][4] = {	{ 2.0, 3.0,  4.0,  5.0 },
											{ 3.0, 5.0,  7.0,  9.0 },
											{ 4.0, 7.0, 10.0, 13.0 },
											{ 5.0, 9.0, 13.0, 17.0 } };

	double Multiplication_ref_4[4][4] = {	{ 2.0,  4.0,  6.0,  8.0 },
											{ 4.0,  8.0, 12.0, 16.0 },
											{ 6.0, 12.0, 18.0, 24.0 },
											{ 8.0, 16.0, 24.0, 32.0 } };

	double Multiple_Multiplication_ref = { 0.0 };

	double MatxVec_ref[3] = { 6.0, 6.0, 6.0 };

	// LU decomposition
	double LU_ref[4][6] = { { 1.0, 2.0,  3.0,  4.0,  5.0,  6.0 },
							{ 2.0, 4.0,  6.0,  8.0, 10.0, 12.0 },
							{ 3.0, 6.0,  9.0, 12.0, 15.0, 18.0 },
							{ 4.0, 8.0, 12.0, 16.0, 20.0, 24.0 } };

	double L_ref[4][4] = {	{ 1.0, 0.0, 0.0, 0.0 },
							{ 2.0, 1.0, 0.0, 0.0 },
							{ 3.0, 0.0, 1.0, 0.0 }, 
							{ 4.0, 0.0, 0.0, 1.0 }};

	double U_ref[4][6] = {	{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
							{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
							{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }, 
							{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } };

	// Inversion
	double Invertible_ref[4][4] = {	{ 1.0, 0.0, 0.0, 0.0 },
									{ 2.0, 4.0, 0.0, 0.0 },
									{ 0.0, 2.0, 4.0, 0.0 },
									{ 0.0, 0.0, 2.0, 1.0 } };

	double Inverse_ref[4][4] = {{  1.000,  0.000,  0.000,  0.000 }, 
								{ -0.500,  0.250,  0.000,  0.000 },
								{  0.250, -0.125,  0.250,  0.000 },
								{ -0.500,  0.250, -0.500,  1.000 } };

	double EYE4_ref[4][4] = {	{ 1.0, 0.0, 0.0, 0.0 },
								{ 0.0, 1.0, 0.0, 0.0 }, 
								{ 0.0, 0.0, 1.0, 0.0 }, 
								{ 0.0, 0.0, 0.0, 1.0 } };

	double EYE3x2[3][3] = { { 2.0, 0.0, 0.0 },
							{ 0.0, 2.0, 0.0 },
							{ 0.0, 0.0, 2.0 } };
	double EYE3x16[3][3] = {{ 16.0,  0.0,  0.0 },
							{  0.0, 16.0,  0.0 },
							{  0.0,  0.0, 16.0 } };
	double NegExp3[3][3] = {{ 0.0625, 0.0,   0.0		},
							{ 0.0,	  0.0625, 0.0		},
							{ 0.0,    0.0,	  0.0625	} };
	
	// Misc
	double EMult_operand[3][3] = {	{ 1.0, 2.0, 3.0 },
									{ 4.0, 5.0, 6.0 }, 
									{ 7.0, 8.0, 9.0 } };
	double EMult_ref[3][3] = {	{  1.0,  4.0,  9.0 },
								{ 16.0, 25.0, 36.0 },
								{ 49.0, 64.0, 81.0 } };

	// ApplyEach
	double ApplyEach_Input[3][3] = {{ _SM_Matrix_PI / 6.0,	0.0,			0.0 },
									{ 0.0,				_SM_Matrix_PI / 2.0,	0.0 },
									{ 0.0,				0.0,			_SM_Matrix_PI } };

	double ApplyEach_ref[3][3] = {	{	0.5,	0.0,	0.0 },
									{	0.0,	1.0,	0.0 },
									{	0.0,	0.0,	0.0 } };

	double ApplyEach_2ndarg_ref[3][3] = {	{ 1.0,	1.0,			1.0 },
											{ 1.0,	_SM_Matrix_PI / 2.0,	1.0 },
											{ 1.0,	1.0,			_SM_Matrix_PI } };

}

void PresentTestResult(const char* str, SM_Matrix<>& Res)
{
	std::cout << str << "\n" << Res << std::endl;
}

bool CompareResult(SM_Matrix<>& result, double ref, const char* expression)
{
	int i, j;

	for (i = 0; i < result.Nrows; i++)
	{
		for (j = 0; j < result.Ncolumns; j++)
		{
			if (abs(result[i][j] - ref) > 1e-6)
			{
				std::cout << expression << " failed" << std::endl;
				std::cout << "Result: \n" << result << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < result.Nrows; i++)
				{
					std::cout << "\n" << ref;
					for (j = 1; j < result.Ncolumns; j++)
					{
						std::cout << ", " << ref;
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

bool CompareResult(double* result, double* ref, int size, const char* expression)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (abs(result[i] - ref[i]) > 1e-6)
		{
			std::cout << expression << " failed" << std::endl;
			std::cout << "Result: " << result[0];
		
			for (i = 1; i < size; i++)
			{
				std::cout << ", " << result[i];
			}
			std::cout << "\n";

			std::cout << "Expected result: " << ref[0];
		
			for (i = 1; i < size; i++)
			{
				std::cout << ", " << ref[i];
			}
			std::cout << "\n";
		
			return false;
		}
	}
	std::cout << expression << " succeeded"  << std::endl;

	std::cout << result[0];
	for (i = 1; i < size; i++)
	{
		std::cout << ", " << result[i];
	}
	std::cout << "\n";

	return true;
}

bool SM_Matrix_UT()
{
	if (SM_Matrix_Unittests::ConstructionTest())
	{
		if (SM_Matrix_Unittests::AssignmentTest())
		{
			if (SM_Matrix_Unittests::AdditionTest())
			{
				if (SM_Matrix_Unittests::SubtractionTest())
				{
					if (SM_Matrix_Unittests::MultiplicationTest())
					{
						if (SM_Matrix_Unittests::InversionTest())
						{
							if (SM_Matrix_Unittests::DivisionTest())
							{
								if (SM_Matrix_Unittests::ExponentTest())
								{
									if (SM_Matrix_Unittests::MiscTest())
									{
										std::cout << "\nSM_Matrix_UT Succeeded!" << std::endl;
										return true;
									}
									else
										std::cout << "SM_Matrix UT failed on Misc test" << std::endl;
									return false;
								}
								else
									std::cout << "SM_Matrix UT failed on Exponent test" << std::endl;
									return false;
							}
							else
								std::cout << "SM_Matrix UT failed on Division test" << std::endl;
								return false;
						}
						else
							std::cout << "SM_Matrix UT failed on Inversion test" << std::endl;
							return false;
					}
					else
						std::cout << "SM_Matrix UT failed on Multiplication test" << std::endl;
						return false;
				}
				else
					std::cout << "SM_Matrix UT failed on Subtraction test" << std::endl;
					return false;
			}
			else
				std::cout << "SM_Matrix UT failed on Addition test" << std::endl;
				return false;
		}
		else
			std::cout << "SM_Matrix UT failed on Assignment test" << std::endl;
			return false;
	}
	else
		std::cout << "SM_Matrix UT failed on Construction test" << std::endl;
		return false;
}

bool SM_Matrix_Unittests::ConstructionTest()
{
	SM_Matrix Mat1_1D(3, 3);
	SM_Matrix Mat1(3, 3);
	SM_Matrix Mat1_copy(3, 3);
	SM_Matrix ZeroMat(3, 3);

	int i, j;

	Mat1_1D = &SM_Matrix_UT_variables::ID_ref_1D[0];
	Mat1 = &SM_Matrix_UT_variables::ID_ref[0][0];
	Mat1_copy = &SM_Matrix_UT_variables::ID_ref[0][0];
	ZeroMat = &SM_Matrix_UT_variables::ZERO_ref[0][0];

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "---------------------------- Construction Unittest -----------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// Construction tests
	for (i = 0; i < Mat1_1D.NumEl; i++)
	{
		if (Mat1_1D.Mat[i] != SM_Matrix_UT_variables::ID_ref_1D[i])
		{
			std::cout << "1D pointer constructor failed" << std::endl;
			std::cout << Mat1_1D << std::endl;
			return false;
		}
	}
	PresentTestResult("1D pointer construction operator succeeded", Mat1_1D);

	for (i = 0; i < Mat1.Nrows; i++)
	{
		for (j = 0; j < Mat1.Ncolumns; j++)
		{
			if (Mat1[i][j] != SM_Matrix_UT_variables::ID_ref[i][j])
			{
				std::cout << "2D pointer constructor failed" << std::endl;
				std::cout << Mat1 << std::endl;
				return false;
			}
		}
		
	}
	PresentTestResult("2D pointer construction operator succeeded", Mat1);
	//std::cout << "2D pointer construction operator succeeded" << std::endl;

	// Comparison test
	if (Mat1 == Mat1_copy)
	{
		std::cout << "Equaity operator succeeded" << std::endl;
	}
	else
	{
		std::cout << "Equaity operator failed" << std::endl;
		return false;
	}

	if (Mat1 != ZeroMat)
	{
		std::cout << "Inequaity operator succeeded" << std::endl;
	}
	else
	{
		std::cout << "Inequaity operator failed" << std::endl;
		return false;
	}

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::AssignmentTest()
{
	SM_Matrix Mat(3, 3);
	SM_Matrix ID_Mat(3, 3, SM_Matrix_UT_variables::ID_ref);

	double temp = 5.0;
	int i, j;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "----------------------------- Assignment Unittest ------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	std::cout << "performing: Mat[0][0] = " << temp << ";" << std::endl;
	Mat[0][0] = temp;

	if (Mat.Mat[0] != temp)
	{
		std::cout << "Mat[0][0] != " << temp << std::endl;
		std::cout << "Mat[0][0] == " << Mat.Mat[0] << std::endl;
		std::cout << "2D assignment failed" << std::endl;
		return false;
	}
	else
	{
		PresentTestResult("2D assignment succeeded", Mat);
	}

	if (Mat[0][0] != temp)
	{
		std::cout << "Mat[0][0] getter operation failed" << std::endl;
		return false;
	}
	else
	{
		std::cout << "Mat[0][0] getter operation succeeded" << std::endl;
		std::cout << "Mat[0][0] == ref == " << temp << std::endl;
	}

	// Matrix assignments
	Mat = ID_Mat;

	if (Mat != ID_Mat)
	{
		std::cout << "Matrix copy failed" << std::endl;
		std::cout << "ref:" << std::endl;
		std::cout << ID_Mat << std::endl;
		std::cout << "Matrix:" << std::endl;
		std::cout << Mat << std::endl;
		return false;
	}
	else
	{
		PresentTestResult("Matrix copy succeeded", Mat);
	}

	Mat[0][0] = 6.0;
	Mat[1][1] = 7.0;
	Mat[2][2] = 8.0;
	Mat = SM_Matrix_UT_variables::ID_ref_1D;

	for (i = 0; i < Mat.Nrows; i++)
	{
		for (j = 0; j < Mat.Ncolumns; j++)
		{
			if (Mat[i][j] != SM_Matrix_UT_variables::ID_ref_1D[i * Mat.Ncolumns + j])
			{
				std::cout << "Matrix 1D copy failed" << std::endl;
				std::cout << "ref:" << std::endl;
				std::cout << ID_Mat << std::endl;
				std::cout << "Matrix:" << std::endl;
				std::cout << Mat << std::endl;
				return false;
			}
		}
	}
	PresentTestResult("Matrix 1D copy succeeded", Mat);
	//std::cout << "Matrix 1D copy succeeded" << std::endl;

	Mat = &SM_Matrix_UT_variables::Addition_A[0][0];
	for (i = 0; i < Mat.Nrows; i++)
	{
		for (j = 0; j < Mat.Ncolumns; j++)
		{
			if (Mat[i][j] != SM_Matrix_UT_variables::Addition_A[i][j])
			{
				std::cout << "Matrix 2D copy failed" << std::endl;
				std::cout << "ref:";

				for (i = 0; i < Mat.Nrows; i++)
				{
					std::cout << "\n";
					for (j = 0; j < Mat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_A[i][j];
					}
				}
				std::cout << "\n";

				std::cout << "Matrix:" << std::endl;
				std::cout << Mat << std::endl;
				return false;
			}
		}
	}
	PresentTestResult("Matrix 2D copy succeeded", Mat);

	Mat.Zeroize();
	for (i = 0; i < Mat.Nrows; i++)
	{
		for (j = 0; j < Mat.Ncolumns; j++)
		{
			if (Mat[i][j] != 0.0)
			{
				std::cout << "Matrix zeroize method failed" << std::endl;
				std::cout << "Matrix:" << std::endl;
				std::cout << Mat << std::endl;
				return false;
			}
		}
	}
	PresentTestResult("Matrix zeroize method succeeded", Mat);

	Mat.Identity();
	for (i = 0; i < Mat.Nrows; i++)
	{
		for (j = 0; j < Mat.Ncolumns; j++)
		{
			if (Mat[i][j] != (double)(i == j))
			{
				std::cout << "Matrix identity method failed" << std::endl;
				std::cout << "Matrix:" << std::endl;
				std::cout << Mat << std::endl;

				return false;
			}
		}
	}
	PresentTestResult("Matrix identity method succeeded", Mat);

	Mat.Zeroize();

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::AdditionTest()
{
	bool testSuccess = false;
	//double res_arr[3][3] = { 0.0 };
	SM_Matrix ResMat(3, 3);

	SM_Matrix Addition_A(3, 3, SM_Matrix_UT_variables::Addition_A);
	SM_Matrix Addition_B(3, 3, SM_Matrix_UT_variables::Addition_B);
	SM_Matrix Addition_C(3, 3, SM_Matrix_UT_variables::Addition_C);
	SM_Matrix Addition_D(3, 3, SM_Matrix_UT_variables::Addition_D);
	SM_Matrix OnesMat(3, 3);

	OnesMat = 1.0;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Addition Unittest ------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// A + B Test
	std::cout << "Performing: Res1 = A + B" << std::endl;
	std::cout << "A = \n" << Addition_A << std::endl;
	std::cout << "B = \n" << Addition_B << std::endl;

	ResMat = Addition_A + Addition_B;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::Addition_ApB_Result, "A + B addition");

	if (!testSuccess)
		return false;

	ResMat.Zeroize();

	// A + B + C Test
	std::cout << "Performing: Res2 = A + B + C" << std::endl;
	std::cout << "C = \n" << Addition_C << std::endl;
	ResMat = Addition_A + Addition_B + Addition_C;

	testSuccess = CompareResult(ResMat, 11.0, "A + B + C addition");
	
	if (!testSuccess)
		return false;

	ResMat.Zeroize();

	// A + B + C + D Test
	std::cout << "Performing: Res3 = A + B + C + D" << std::endl;
	std::cout << "D = \n" << Addition_D << std::endl;
	ResMat = Addition_A + Addition_B + Addition_C + Addition_D;

	testSuccess = CompareResult(ResMat, 13.0, "A + B + C + D addition");

	if (!testSuccess)
		return false;

	// Scalar addition
	std::cout << "Performing: Res4 = Res3 + 1 (Scalar addition test)" << std::endl;
	std::cout << "Res3 = \n" << ResMat << std::endl;

	ResMat = ResMat + 1;

	testSuccess = CompareResult(ResMat, 14.0, "Scalar addition");

	if (!testSuccess)
		return false;

	// Addition assignment 
	std::cout << "Performing: Res5 = Res4 + OnesMat (Addition assignment test with SM_Matrix object)" << std::endl;
	std::cout << "Res4 = \n" << ResMat << std::endl;

	ResMat += OnesMat;

	testSuccess = CompareResult(ResMat, 15.0, "Addition assignment");

	if (!testSuccess)
		return false;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::SubtractionTest()
{
	bool testSuccess = false;

	//double res_arr[3][3] = { 0.0 };
	SM_Matrix ResMat(3, 3);

	ResMat = 15.0; // Assigning 15 to every cell in the matrix

	SM_Matrix OnesMat(3, 3), Another_OnesMat(3, 3);

	OnesMat = 1.0;
	Another_OnesMat = 1.0;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "----------------------------- Subtraction Unittest -----------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// A - B
	std::cout << "Performing: Res1 = A - B" << std::endl;
	std::cout << "A = \n" << ResMat << std::endl;
	std::cout << "B = \n" << OnesMat << std::endl;

	ResMat = ResMat - OnesMat;

	testSuccess = CompareResult(ResMat, 14.0, "A - B subtraction");

	if (!testSuccess)
		return false;

	ResMat = 15.0;

	// A - B - C
	std::cout << "Performing: Res1 = A - B - C" << std::endl;
	std::cout << "C = \n" << Another_OnesMat << std::endl;

	ResMat = ResMat - OnesMat - Another_OnesMat;

	testSuccess = CompareResult(ResMat, 13.0, "A - B - C subtraction");

	if (!testSuccess)
		return false;

	ResMat = 14.0;

	// Scalar subtraction
	std::cout << "Performing: Res2 = Mat14 - 1 (Scalar subtraction test)" << std::endl;
	std::cout << "Mat14 = \n" << ResMat << std::endl;

	ResMat = ResMat - 1;

	testSuccess = CompareResult(ResMat, 13.0, "Scalar subtraction");

	if (!testSuccess)
		return false;

	ResMat = 14.0;

	// Subtraction assignment
	std::cout << "Performing: Res3 = Mat14 - OnesMat (Subtraction assignment test with SM_Matrix object)" << std::endl;
	std::cout << "Mat14 = \n" << ResMat << std::endl;

	ResMat -= OnesMat;

	testSuccess = CompareResult(ResMat, 13.0, "Subtraction assignment");

	if (!testSuccess)
		return false;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	Another_OnesMat.Zeroize();

	return true;
}

bool SM_Matrix_Unittests::MultiplicationTest()
{
	bool testSuccess = false;

	//double res_arr[4][4] = { 0.0 }, res_arr2[3][3] = { 0.0 };
	//double ones_arr[4][4] = { 0.0 };
	//double Eye_x2_arr[4][4] = { 0.0 };
	double VecIn[3] = { 1.0, 2.0, 3.0 }, VecOut[3] = { 4.0, 5.0, 6.0 };
	SM_Matrix ResMat(4, 4), ResMat2(3, 3), OnesMat(4, 4), Eye_x2_Mat(4, 4);

	OnesMat = 1.0; // Initializing OnesMat with ones
	Eye_x2_Mat.Identity();
	Eye_x2_Mat *= 2.0;

	SM_Matrix Multiplication_right(4, 1, SM_Matrix_UT_variables::Multiplication_right);
	SM_Matrix Multiplication_left(1, 4, SM_Matrix_UT_variables::Multiplication_left);

	int i, j;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "---------------------------- Multiplication Unittest ---------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// A * B 
	std::cout << "Performing: ResMat = A * B" << std::endl;
	std::cout << "A = \n" << Multiplication_right << std::endl;
	std::cout << "B = \n" << Multiplication_left << std::endl;

	ResMat = Multiplication_right * Multiplication_left;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::Multiplication_ref_2, "A * B Multiplication");

	if (!testSuccess)
		return false;

	// A * B * C
	std::cout << "Performing: ResMat = A * B * C" << std::endl;
	std::cout << "C = \n" << Eye_x2_Mat << std::endl;

	ResMat = Multiplication_right * Multiplication_left * Eye_x2_Mat;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::Multiplication_ref_4, "A * B * C Multiplication");

	if (!testSuccess)
		return false;

	ResMat.Zeroize();

	// A * B + C
	std::cout << "Performing: ResMat = A * B + C" << std::endl;
	std::cout << "C = \n" << OnesMat << std::endl;

	ResMat = Multiplication_right * Multiplication_left + OnesMat;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::Multiplication_ref_3, "A * B + C Multiplication");

	if (!testSuccess)
		return false;

	ResMat.Zeroize();
	ResMat = 1.0;

	// Matrix multiplication assignment
	std::cout << "Performing: ResMat *= Other" << std::endl;
	std::cout << "ResMat = \n" << ResMat << std::endl;
	std::cout << "Other = \n" << Eye_x2_Mat << std::endl;

	ResMat *= Eye_x2_Mat;

	testSuccess = CompareResult(ResMat, 2.0, "Matrix multiplication assignment");

	if (!testSuccess)
		return false;

	ResMat.Zeroize();

	// Scalar multiplication
	std::cout << "Performing: ResMat = A * B * 2 (Scalar multiplication test)" << std::endl;

	ResMat = 1.0;
	ResMat = ResMat * 2.0;

	testSuccess = CompareResult(ResMat, 2.0, "Scalar multiplication");

	if (!testSuccess)
		return false;

	ResMat.Zeroize();

	// Scalar multiplication assignment
	std::cout << "Performing: ResMat *= 2 (Scalar multiplication assignment test)" << std::endl;

	ResMat = 1.0;
	ResMat *= 2.0;

	testSuccess = CompareResult(ResMat, 2.0, "Scalar multiplication assignment");

	if (!testSuccess)
		return false;

	// Scalar multiplication assignment
	ResMat2 = 1;
	std::cout << "Performing: Matrix multiplication by vector:\n" << ResMat2 << std::endl;
	std::cout << "with:\n" << VecIn[0] << ", " << VecIn[1] << ", " << VecIn[2] << std::endl;

	ResMat2.MatxVec(VecIn, VecOut);

	testSuccess = CompareResult(VecOut, SM_Matrix_UT_variables::MatxVec_ref, 3, "Matrix multiplication by vector");

	if (!testSuccess)
		return false;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::InversionTest()
{
	bool testSuccess = false;

	//double ResMat_arr[4][4] = { 0.0 }, InvMat_arr[4][4] = { 0.0 }, T_arr[6][4] = { 0.0 }, L_arr[4][4] = { 0.0 }, U_arr[4][6] = { 0.0 };
	SM_Matrix ResMat(4, 4), InvMat(4, 4);
	SM_Matrix LU_Mat(4, 6, SM_Matrix_UT_variables::LU_ref);
	SM_Matrix T_Mat(6, 4), L_Mat(4, 4), U_Mat(4, 6);

	int i, j;
	double DetVal = 0;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Inversion Unittest -----------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// Transpose
	std::cout << "Performing: matrix transpose on:\n" << LU_Mat << std::endl;
	
	T_Mat = LU_Mat.Transpose();

	for (i = 0; i < T_Mat.Nrows; i++)
	{
		for (j = 0; j < T_Mat.Ncolumns; j++)
		{
			if (T_Mat[i][j] != SM_Matrix_UT_variables::LU_ref[j][i])
			{
				std::cout << "Matrix transpose failed" << std::endl;
				std::cout << "Result: \n" << T_Mat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < T_Mat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::U_ref[j][0];
					for (j = 1; j < T_Mat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::U_ref[j][i];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Matrix transpose succeeded", T_Mat);

	// LU decompusition
	std::cout << "Performing: LU decomposition on LU reference:\n" << LU_Mat << std::endl;

	LU_Mat.LU_Decompose(L_Mat, U_Mat);

	testSuccess = CompareResult(L_Mat, SM_Matrix_UT_variables::L_ref, "LU decomposition (L)");

	if (!testSuccess)
		return false;

	testSuccess = CompareResult(U_Mat, SM_Matrix_UT_variables::U_ref, "LU decomposition (U)");

	if (!testSuccess)
		return false;

	ResMat = &SM_Matrix_UT_variables::Invertible_ref[0][0];

	// Determinant
	std::cout << "Performing: Determinant calculation on:\n" << ResMat << std::endl;

	DetVal = ResMat.Det();

	if (DetVal != 16.0)
	{
		std::cout << "Determinant calculation failed" << std::endl;
		std::cout << "Result - " << DetVal << std::endl;
		std::cout << "Expected value - " << 16.0 << std::endl;
		return false;
	}
	else
	{
		std::cout << "Determinant calculation succeeded" << "\n" << DetVal << std::endl;
	}

	// Inversion
	std::cout << "Performing: Matrix inversion on:\n" << ResMat << std::endl;

	InvMat = ResMat.Invert();

	testSuccess = CompareResult(InvMat, SM_Matrix_UT_variables::Inverse_ref, "Matrix inversion");

	if (!testSuccess)
		return false;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::DivisionTest()
{
	bool testSuccess = false;

	//double ResMat_arr[4][4] = { 0.0 };
	SM_Matrix ResMat(4, 4);

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Division Unittest ------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// Scalar division
	ResMat = 5.0;
	std::cout << "Performing: Scalar division on:\n" << ResMat << std::endl;

	ResMat = ResMat / 5.0;

	testSuccess = CompareResult(ResMat, 1.0, "Scalar division");

	if (!testSuccess)
		return false;

	// Scalar division assignment
	ResMat = 5.0;
	std::cout << "Performing: Scalar division assignment on:\n" << ResMat << std::endl;

	ResMat /= 5.0;

	testSuccess = CompareResult(ResMat, 1.0, "Scalar division assignment");

	if (!testSuccess)
		return false;

	// 'Division' by Matrix (Multiplication with inverse)
	ResMat = &SM_Matrix_UT_variables::Invertible_ref[0][0];
	std::cout << "Performing: Division by matrix (multiply by inverse) on:\n" << ResMat << std::endl;
	std::cout << "with:\n" << ResMat << std::endl;

	ResMat = ResMat / ResMat;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::EYE4_ref, "Division by matrix (multiply by inverse)");

	if (!testSuccess)
		return false;

	// 'Division'assignment by Matrix (Multiplication with inverse)
	ResMat = &SM_Matrix_UT_variables::Invertible_ref[0][0];
	std::cout << "Performing: Division assignment by matrix (multiply assign by inverse) on:\n" << ResMat << std::endl;
	std::cout << "with:\n" << ResMat << std::endl;

	ResMat /= ResMat;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::EYE4_ref, "Division assignment by matrix (multiply assign by inverse)");

	if (!testSuccess)
		return false;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::ExponentTest()
{
	bool testSuccess = false;

	//double ResMat_arr[3][3] = { 0.0 };
	SM_Matrix ResMat(3, 3);

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Exponent Unittest ------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// Positive exponentiation
	ResMat = &SM_Matrix_UT_variables::EYE3x2[0][0];
	std::cout << "Performing: Positive exponentiation on:\n" << ResMat << std::endl;
	std::cout << "by:\n" << 4 << std::endl;

	ResMat = ResMat ^ 4;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::EYE3x16, "Positive exponentiation");

	if (!testSuccess)
		return false;

	// Positive exponentiation assignment
	ResMat = &SM_Matrix_UT_variables::EYE3x2[0][0];
	std::cout << "Performing: Positive exponentiation assignment on:\n" << ResMat << std::endl;
	std::cout << "by:\n" << 4 << std::endl;

	ResMat ^= 4;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::EYE3x16, "Positive exponentiation assignment");

	if (!testSuccess)
		return false;

	// Negative exponentiation
	std::cout << "Performing: Negative exponentiation on:\n" << ResMat << std::endl;
	std::cout << "by:\n" << -1 << std::endl;

	ResMat = ResMat ^ -1;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::NegExp3, "Negative exponentiation");

	if (!testSuccess)
		return false;

	// Negative exponentiation assignment
	ResMat = &SM_Matrix_UT_variables::EYE3x16[0][0];
	std::cout << "Performing: Negative exponentiation assignment on:\n" << ResMat << std::endl;
	std::cout << "by:\n" << -1 << std::endl;

	ResMat ^= -1;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::NegExp3, "Negative exponentiation assignment");

	if (!testSuccess)
		return false;

	// Null Exponentiation (to the power of 0)
	std::cout << "Performing: Null Exponentiation (to the power of 0) on:\n" << ResMat << std::endl;

	ResMat = ResMat ^ 0;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::ID_ref, "Null exponentiation");

	if (!testSuccess)
		return false;

	// Null Exponentiation assignment (to the power of 0)
	ResMat = &SM_Matrix_UT_variables::NegExp3[0][0];
	std::cout << "Performing: Null exponentiation assignment (to the power of 0) on:\n" << ResMat << std::endl;

	ResMat ^= 0;

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::ID_ref, "Null exponentiation assignment");

	if (!testSuccess)
		return false;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::MiscTest()
{
	bool testSuccess = false;
	//double ResMat_arr[3][3] = { 0.0 };
	double Trace = 0;
	SM_Matrix ResMat(3, 3);
	SM_Matrix Mat_operand1(3, 3, SM_Matrix_UT_variables::EMult_operand), Mat_operand2(3, 3, SM_Matrix_UT_variables::EMult_operand);
	

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------- Misc Unittest --------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// EMultiply
	ResMat = &SM_Matrix_UT_variables::EMult_operand[0][0];
	std::cout << "Performing: element-wise multiplication on:\n" << Mat_operand1 << std::endl;
	std::cout << "With:\n" << Mat_operand2 << std::endl;

	ResMat = Mat_operand1.EMultiply(Mat_operand2);

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::EMult_ref, "element-wise multiplication");

	if (!testSuccess)
		return false;

	// EDivide
	std::cout << "Performing: element-wise division on:\n" << ResMat << std::endl;
	std::cout << "With:\n" << Mat_operand1 << std::endl;

	ResMat = ResMat.EDivide(Mat_operand1);

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::EMult_operand, "element-wise division");

	if (!testSuccess)
		return false;

	// Trace
	std::cout << "Performing: trace on:\n" << ResMat << std::endl;

	Trace = ResMat.Trace();

	if (Trace != 15.0)
	{
		std::cout << "Trace calculation failed" << std::endl;
		std::cout << "Result - " << Trace << std::endl;
		std::cout << "Expected value - " << 16.0 << std::endl;
		return false;
	}
	else
	{
		std::cout << "Trace calculation succeeded" << "\n" << Trace << std::endl;
	}

	// ApplyEach single argument (argument pass by value)
	ResMat = &SM_Matrix_UT_variables::ApplyEach_Input[0][0];
	std::cout << "Performing: element-wise function application (sin) on:\n" << ResMat << std::endl;

	ResMat = ResMat.ApplyEach(sin);

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::ApplyEach_ref, "element-wise function application (sin)");

	if (!testSuccess)
		return false;

	// ApplyEach double argument (arguments pass by value)
	ResMat = &SM_Matrix_UT_variables::ApplyEach_Input[0][0];
	std::cout << "Performing: element-wise 2-argument function application (fmax) on:\n" << ResMat << std::endl;
	std::cout << "(max(x[i][j],1.0))" << std::endl;
	
	ResMat = ResMat.ApplyEach(fmax,1.0);

	testSuccess = CompareResult(ResMat, SM_Matrix_UT_variables::ApplyEach_2ndarg_ref, "element-wise 2-argument function application (fmax)");

	if (!testSuccess)
		return false;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}