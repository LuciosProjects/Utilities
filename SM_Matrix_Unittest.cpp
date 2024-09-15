#include "Utilities.h"

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

	double Multiplication_ref3[4][4] = {	{ 2.0, 3.0,  4.0,  5.0 },
											{ 3.0, 5.0,  7.0,  9.0 },
											{ 4.0, 7.0, 10.0, 13.0 },
											{ 5.0, 9.0, 13.0, 17.0 } };

	double Multiplication_ref_4[4][4] = {	{ 2.0,  4.0,  6.0,  8.0 },
											{ 4.0,  8.0, 12.0, 16.0 },
											{ 6.0, 12.0, 18.0, 24.0 },
											{ 8.0, 16.0, 24.0, 32.0 } };

	double Multiple_Multiplication_ref = { 0.0 };

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

	double Invertible_ref[4][4] = {	{ 1.0, 0.0, 0.0, 0.0 },
									{ 2.0, 4.0, 0.0, 0.0 },
									{ 0.0, 2.0, 4.0, 0.0 },
									{ 0.0, 0.0, 2.0, 1.0 } };

	double Inverse_ref[4][4] = {{ 1.0, -0.50,  1.0, -0.50 }, 
								{ 0.0,  0.25, -0.5,  0.25 },
								{ 0.0,  0.00,  1.0, -0.50 },
								{ 0.0,  0.00,  0.0,  0.25 } };
}

void PresentTestResult(const char* str, SM_Matrix<>& Res)
{
	std::cout << str << "\n" << Res << std::endl;
}

bool SM_Matrix_UT()
{
	bool SM_Matrix_UT_Success;
	bool Contruction_UT_Success = false, Assignment_UT_success = false;
	bool Addition_UT_Success = false, Subtraction_UT_Success = false;
	bool Multiplication_UT_Success = false, Division_UT_Success = false;
	bool Inversion_UT_Success = false;

	Contruction_UT_Success = SM_Matrix_Unittests::ConstructionTest();
	Assignment_UT_success = SM_Matrix_Unittests::AssignmentTest();
	Addition_UT_Success = SM_Matrix_Unittests::AdditionTest();
	Subtraction_UT_Success = SM_Matrix_Unittests::SubtractionTest();
	Multiplication_UT_Success = SM_Matrix_Unittests::MultiplicationTest();
	Inversion_UT_Success = SM_Matrix_Unittests::InversionTest();
	Division_UT_Success = SM_Matrix_Unittests::DivisionTest();

	SM_Matrix_UT_Success = Contruction_UT_Success && Assignment_UT_success && 
							Addition_UT_Success && Subtraction_UT_Success && 
							Multiplication_UT_Success && Inversion_UT_Success && Division_UT_Success;

	if (SM_Matrix_UT_Success)
	{
		std::cout << "\nSM_Matrix_UT Succeeded!" << std::endl;
	}
	else
	{
		std::cout << "\nSM_Matrix_UT Failed!" << std::endl;
	}

	return SM_Matrix_UT_Success;
}

bool SM_Matrix_Unittests::ConstructionTest()
{
	Math::SM_Matrix Mat1_1D(3, 3, SM_Matrix_UT_variables::ID_ref_1D);
	Math::SM_Matrix Mat1(3, 3, SM_Matrix_UT_variables::ID_ref);
	Math::SM_Matrix Mat1_copy(3, 3, SM_Matrix_UT_variables::ID_ref);
	Math::SM_Matrix ZeroMat(3, 3, SM_Matrix_UT_variables::ZERO_ref);

	int i, j;

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
	//std::cout << "1D pointer construction operator succeeded" << std::endl;

	for (i = 0; i < Mat1.Nrows; i++)
	{
		for (j = 0; j < Mat1.Ncolumns; j++)
		{
			if (Mat1.Mat[i*Mat1.Ncolumns + j] != SM_Matrix_UT_variables::ID_ref[i][j])
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
	Math::SM_Matrix Mat(3, 3, SM_Matrix_UT_variables::MutableMat);
	Math::SM_Matrix ID_Mat(3, 3, SM_Matrix_UT_variables::ID_ref);

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
		//std::cout << "2D assignment succeeded" << std::endl;
	}

	if (Mat[0][0] != temp)
	{
		std::cout << "Mat[0][0] getter operation failed" << std::endl;
		return false;
	}
	else
	{
		std::cout << "Mat[0][0] getter operation succeeded" << std::endl;
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
		//std::cout << "Matrix copy succeeded" << std::endl;
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
	//std::cout << "Matrix 2D copy succeeded" << std::endl;

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
	//std::cout << "Matrix zeroize method succeeded" << std::endl;

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
	//std::cout << "Matrix identity method succeeded" << std::endl;

	Mat.Zeroize();

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::AdditionTest()
{
	double res_arr[3][3] = { 0.0 };
	SM_Matrix ResMat(3, 3, res_arr);

	SM_Matrix Addition_A(3, 3, SM_Matrix_UT_variables::Addition_A);
	SM_Matrix Addition_B(3, 3, SM_Matrix_UT_variables::Addition_B);
	SM_Matrix Addition_C(3, 3, SM_Matrix_UT_variables::Addition_C);
	SM_Matrix Addition_D(3, 3, SM_Matrix_UT_variables::Addition_D);
	SM_Matrix OnesMat(3, 3, SM_Matrix_UT_variables::OnesMat);

	int i, j;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Addition Unittest ------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// A + B Test
	std::cout << "Performing: Res1 = A + B" << std::endl;
	std::cout << "A = \n" << Addition_A << std::endl;
	std::cout << "B = \n" << Addition_B << std::endl;

	ResMat = Addition_A + Addition_B;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 10.0)
			{
				std::cout << "A + B addition failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_ApB_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_ApB_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A + B addition succeeded", ResMat);
	//std::cout << "A + B addition succeeded" << std::endl;

	ResMat.Zeroize();

	// A + B + C Test
	std::cout << "Performing: Res2 = A + B + C" << std::endl;
	std::cout << "C = \n" << Addition_C << std::endl;
	ResMat = Addition_A + Addition_B + Addition_C;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 11.0)
			{
				std::cout << "A + B + C addition failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_ApBpC_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_ApBpC_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A + B + C addition succeeded", ResMat);
	//std::cout << "A + B + C addition succeeded" << std::endl;

	ResMat.Zeroize();

	// A + B + C + D Test
	std::cout << "Performing: Res3 = A + B + C + D" << std::endl;
	std::cout << "D = \n" << Addition_D << std::endl;
	ResMat = Addition_A + Addition_B + Addition_C + Addition_D;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 13.0)
			{
				std::cout << "A + B + C + D addition failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A + B + C + D addition succeeded", ResMat);
	//std::cout << "A + B + C + D addition succeeded" << std::endl;

	// Scalar addition
	std::cout << "Performing: Res4 = Res3 + 1 (Scalar addition test)" << std::endl;
	std::cout << "Res3 = \n" << ResMat << std::endl;

	ResMat = ResMat + 1;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 14.0)
			{
				std::cout << "Scalar addition failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_MatpK_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_MatpK_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Scalar addition succeeded", ResMat);
	//std::cout << "Scalar addition succeeded" << std::endl;

	// Addition assignment 
	std::cout << "Performing: Res5 = Res4 + OnesMat (Addition assignment test with SM_Matrix object)" << std::endl;
	std::cout << "Res4 = \n" << ResMat << std::endl;

	ResMat += OnesMat;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 15.0)
			{
				std::cout << "Addition assignment failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_MatpOnes_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_MatpOnes_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Addition assignment succeeded", ResMat);
	//std::cout << "Addition assignment succeeded" << std::endl;

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::SubtractionTest()
{
	double res_arr[3][3] = { 0.0 };
	SM_Matrix ResMat(3, 3, res_arr);
	ResMat = 15.0; // Assigning 15 to every cell in the matrix

	SM_Matrix OnesMat(3, 3, SM_Matrix_UT_variables::OnesMat);
	SM_Matrix Another_OnesMat(3, 3, SM_Matrix_UT_variables::MutableMat);
	Another_OnesMat = 1.0;

	int i, j;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "----------------------------- Subtraction Unittest -----------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// A - B
	std::cout << "Performing: Res1 = A - B" << std::endl;
	std::cout << "A = \n" << ResMat << std::endl;
	std::cout << "B = \n" << OnesMat << std::endl;

	ResMat = ResMat - OnesMat;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 14.0)
			{
				std::cout << "A - B subtraction failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_MatpK_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_MatpK_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A - B subtraction succeeded", ResMat);
	//std::cout << "A - B subtraction succeeded" << std::endl;

	ResMat = 15.0;

	// A - B - C
	std::cout << "Performing: Res1 = A - B - C" << std::endl;
	std::cout << "C = \n" << Another_OnesMat << std::endl;

	ResMat = ResMat - OnesMat - Another_OnesMat;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 13.0)
			{
				std::cout << "A - B - C subtraction failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A - B - C subtraction succeeded", ResMat);
	//std::cout << "A - B - C subtraction succeeded" << std::endl;

	ResMat = 14.0;

	// Scalar subtraction
	std::cout << "Performing: Res2 = Mat14 - 1 (Scalar subtraction test)" << std::endl;
	std::cout << "Mat14 = \n" << ResMat << std::endl;

	ResMat = ResMat - 1;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 13.0)
			{
				std::cout << "Scalar subtraction failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Scalar subtraction succeeded", ResMat);

	ResMat = 14.0;

	// Subtraction assignment
	std::cout << "Performing: Res3 = Mat14 - OnesMat (Subtraction assignment test with SM_Matrix object)" << std::endl;
	std::cout << "Mat14 = \n" << ResMat << std::endl;

	ResMat -= OnesMat;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 13.0)
			{
				std::cout << "Subtraction assignment failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Addition_ApBpCpD_Result[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Subtraction assignment succeeded", ResMat);

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	Another_OnesMat.Zeroize();

	return true;
}

bool SM_Matrix_Unittests::MultiplicationTest()
{
	double res_arr[4][4] = { 0.0 };
	double ones_arr[4][4] = { 0.0 };
	double Eye_x2_arr[4][4] = { 0.0 };
	SM_Matrix ResMat(4, 4, res_arr);
	SM_Matrix OnesMat(4, 4, ones_arr);
	SM_Matrix Eye_x2_Mat(4, 4, Eye_x2_arr);

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

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != SM_Matrix_UT_variables::Multiplication_ref_2[i][j])
			{
				std::cout << "A * B Multiplication failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Multiplication_ref_2[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Multiplication_ref_2[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A * B Multiplication succeeded", ResMat);

	// A * B * C
	std::cout << "Performing: ResMat = A * B * C" << std::endl;
	std::cout << "C = \n" << Eye_x2_Mat << std::endl;

	ResMat = Multiplication_right * Multiplication_left * Eye_x2_Mat;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != SM_Matrix_UT_variables::Multiplication_ref_4[i][j])
			{
				std::cout << "A * B * C Multiplication failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Multiplication_ref_4[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Multiplication_ref_4[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A * B * C Multiplication succeeded", ResMat);

	ResMat.Zeroize();

	// A * B + C
	std::cout << "Performing: ResMat = A * B + C" << std::endl;
	std::cout << "C = \n" << OnesMat << std::endl;

	ResMat = Multiplication_right * Multiplication_left + OnesMat;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != SM_Matrix_UT_variables::Multiplication_ref3[i][j])
			{
				std::cout << "A * B + C Multiplication failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Multiplication_ref3[i][0];
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Multiplication_ref3[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("A * B + C Multiplication succeeded", ResMat);

	ResMat.Zeroize();
	ResMat = 1.0;

	// Matrix multiplication assignment
	std::cout << "Performing: ResMat *= Other" << std::endl;
	std::cout << "ResMat = \n" << ResMat << std::endl;
	std::cout << "Other = \n" << Eye_x2_Mat << std::endl;

	ResMat *= Eye_x2_Mat;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 2.0)
			{
				std::cout << "Matrix multiplication assignment failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << 2.0;
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << 2.0;
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Matrix multiplication assignment succeeded", ResMat);

	ResMat.Zeroize();

	// Scalar multiplication
	std::cout << "Performing: ResMat = A * B * 2 (Scalar multiplication test)" << std::endl;

	ResMat = 1.0;
	ResMat = ResMat * 2.0;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 2.0)
			{
				std::cout << "Scalar multiplication failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << 2.0;
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << 2.0;
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Scalar multiplication succeeded", ResMat);

	ResMat.Zeroize();

	// Scalar multiplication assignment
	std::cout << "Performing: ResMat *= 2 (Scalar multiplication assignment test)" << std::endl;

	ResMat = 1.0;
	ResMat *= 2.0;

	for (i = 0; i < ResMat.Nrows; i++)
	{
		for (j = 0; j < ResMat.Ncolumns; j++)
		{
			if (ResMat[i][j] != 2.0)
			{
				std::cout << "Scalar multiplication assignment failed" << std::endl;
				std::cout << "Result: \n" << ResMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < ResMat.Nrows; i++)
				{
					std::cout << "\n" << 2.0;
					for (j = 1; j < ResMat.Ncolumns; j++)
					{
						std::cout << ", " << 2.0;
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Scalar multiplication assignment succeeded", ResMat);

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return true;
}

bool SM_Matrix_Unittests::InversionTest()
{
	double ResMat_arr[4][4] = { 0.0 }, InvMat_arr[4][4] = { 0.0 }, L_arr[4][4] = { 0.0 }, U_arr[4][6] = { 0.0 };
	SM_Matrix ResMat(4, 4, ResMat_arr), InvMat(4, 4, InvMat_arr);
	SM_Matrix LU_Mat(4, 6, SM_Matrix_UT_variables::LU_ref);
	SM_Matrix L_Mat(4, 4, L_arr), U_Mat(4, 6, U_arr);

	int i, j;
	double DetVal = 0;

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Inversion Unittest -----------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	// LU decompusition
	std::cout << "Performing: LU decomposition on LU reference:\n" << LU_Mat << std::endl;

	LU_Mat.LU_Decompose(L_Mat, U_Mat);

	for (i = 0; i < L_Mat.Nrows; i++)
	{
		for (j = 0; j < L_Mat.Ncolumns; j++)
		{
			if (L_Mat[i][j] != SM_Matrix_UT_variables::L_ref[i][j])
			{
				std::cout << "LU decomposition failed (L)" << std::endl;
				std::cout << "Result: \n" << L_Mat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < L_Mat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::L_ref[i][0];
					for (j = 1; j < L_Mat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::L_ref[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	for (i = 0; i < U_Mat.Nrows; i++)
	{
		for (j = 0; j < U_Mat.Ncolumns; j++)
		{
			if (U_Mat[i][j] != SM_Matrix_UT_variables::U_ref[i][j])
			{
				std::cout << "LU decomposition failed (U)" << std::endl;
				std::cout << "Result: \n" << U_Mat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < U_Mat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::U_ref[i][0];
					for (j = 1; j < U_Mat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::U_ref[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("LU decomposition succeeded\n L:", L_Mat);
	std::cout << "U:\n" << U_Mat << std::endl;

	ResMat = &SM_Matrix_UT_variables::Invertible_ref[0][0];

	// Determinant
	std::cout << "Performing: Determinant calculation on:\n" << ResMat << std::endl;

	DetVal = ResMat.Det();

	if (DetVal != 16.0)
	{
		std::cout << "Determinant calculation failed" << std::endl;
		std::cout << "Result - " << DetVal << std::endl;
		std::cout << "Expected value - " << 16.0 << std::endl;
	}
	else
	{
		std::cout << "Determinant calculation succeeded" << "\n" << DetVal << std::endl;
	}

	// Inversion
	std::cout << "Performing: Matrix inversion on:\n" << ResMat << std::endl;

	InvMat = ResMat.Invert();

	for (i = 0; i < InvMat.Nrows; i++)
	{
		for (j = 0; j < InvMat.Ncolumns; j++)
		{
			if (InvMat[i][j] != SM_Matrix_UT_variables::Inverse_ref[i][j])
			{
				std::cout << "Matrix inversion" << std::endl;
				std::cout << "Result: \n" << InvMat << std::endl;

				std::cout << "Expected result:";

				for (i = 0; i < InvMat.Nrows; i++)
				{
					std::cout << "\n" << SM_Matrix_UT_variables::Inverse_ref[i][0];
					for (j = 1; j < InvMat.Ncolumns; j++)
					{
						std::cout << ", " << SM_Matrix_UT_variables::Inverse_ref[i][j];
					}
				}
				std::cout << "\n";

				return false;
			}
		}
	}
	PresentTestResult("Matrix inversion succeeded", InvMat);

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return false;
}

bool SM_Matrix_Unittests::DivisionTest()
{

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Division Unittest ------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	//

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "\n";

	return false;
}