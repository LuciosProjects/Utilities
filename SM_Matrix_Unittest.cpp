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
	double ZERO_ref[3][3] = { {0.0, 0.0, 0.0},
								{0.0, 0.0, 0.0},
								{0.0, 0.0, 0.0} };

	double nonSquare[5][6] = { { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
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
	double Addition_C[3][3] = { { 1.0, 1.0, 1.0 },
								{ 1.0, 1.0, 1.0 } ,
								{ 1.0, 1.0, 1.0 } };
	double Addition_ref[3][3] = { {10.0, 10.0, 10.0},
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
	double Multiplication_ref_2[4][4] = { { 1.0, 2.0,  3.0,  4.0 },
											{ 2.0, 4.0,  6.0,  8.0 },
											{ 3.0, 6.0,  9.0, 12.0 },
											{ 4.0, 8.0, 12.0, 16.0 } };
	double Multiple_Multiplication_ref = { 0.0 };
}

bool SM_Matrix_UT()
{
	bool Contruction_UT_Success = false, Assignment_UT_success = false;
	bool Addition_UT_Success = false;

	Contruction_UT_Success = SM_Matrix_Unittests::ConstructionTest();
	Assignment_UT_success = SM_Matrix_Unittests::AssignmentTest();
	Addition_UT_Success = SM_Matrix_Unittests::AdditionTest();

	return (Contruction_UT_Success && Assignment_UT_success && Addition_UT_Success);
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
	std::cout << "1D pointer construction operator succeeded" << std::endl;

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
	std::cout << "2D pointer construction operator succeeded" << std::endl;

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
	std::cout << "--------------------------------------------------------------------------------\n" << std::endl;
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
		std::cout << "2D assignment succeeded" << std::endl;
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
		std::cout << "Matrix copy succeeded" << std::endl;
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
	std::cout << "Matrix 1D copy succeeded" << std::endl;

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
	std::cout << "Matrix 2D copy succeeded" << std::endl;

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
	std::cout << "Matrix zeroize method succeeded" << std::endl;

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
	std::cout << "Matrix identity method succeeded" << std::endl;

	Mat.Zeroize();

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	return true;
}

bool SM_Matrix_Unittests::AdditionTest()
{
	double res_arr[3][3] = { 0.0 };
	SM_Matrix ResMat(3, 3, res_arr);

	SM_Matrix Addition_A(3, 3, SM_Matrix_UT_variables::Addition_A);
	SM_Matrix Addition_B(3, 3, SM_Matrix_UT_variables::Addition_B);
	SM_Matrix Addition_C(3, 3, SM_Matrix_UT_variables::Addition_C);

	// Header
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------- Addition Unittest ------------------------------" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	std::cout << "Performing: Addition_A + Addition_B" << std::endl;
	std::cout << "Addition_A = \n" << Addition_A << std::endl;
	std::cout << "Addition_B = \n" << Addition_B << std::endl;

	ResMat = Addition_A + Addition_B;

	return false;
}