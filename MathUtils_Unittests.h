#ifndef _MATH_UTILS_UNITTESTS_
#define _MATH_UTILS_UNITTESTS_

#include <iostream>

/****************************************************************/
/********************** Unittest variables **********************/
/****************************************************************/
namespace SM_Matrix_UT_variables
{
	double ID_ref[3][3] = { {1.0, 0.0, 0.0},
							{0.0, 1.0, 0.0},
							{0.0, 0.0, 1.0} };
	double ZERO_ref[3][3] = {	{0.0, 0.0, 0.0},
								{0.0, 0.0, 0.0},
								{0.0, 0.0, 0.0} };

	double nonSquare[5][6] = {	{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
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
	double Addition_ref[3][3] = {	{10.0, 10.0, 10.0},
									{10.0, 10.0, 10.0},
									{10.0, 10.0, 10.0} };
	double Multiple_Additions_ref[3][3] = {	{11.0, 11.0, 11.0},
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
	double Multiple_Multiplication_ref = { 0.0 };
}


bool SM_Matrix_UT();
namespace SM_Matrix_Unittests
{
	bool ConstructionTest();
	
	// assignment unittests
}

#endif
