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
}


void SM_Matrix_UT();
namespace SM_Matrix_Unittests
{
	void ConstructionTest();
	// Constructor unittests
	// assignment unittests
}

#endif
