#include "pch.h"
#include "NNLib_UT.h"

// 1 - input
// 2 - hidden1
// 3 - hidden2
// 4 - output

double W31_arr[3][3] = { { 1.0, 0.0, 0.0},
						{ 0.0, 1.0, 0.0 },
						{ 0.0, 0.0, 1.0 } };
double b31_arr[3] = { 0.0, 0.0, 0.0 };
double b32_arr[3] = { 0.0, 0.0, 0.0 };
double W32_arr[3][2] = { { 1.0, 0.0 },
						{ 0.0, 1.0 },
						{ 0.0, 0.0 } };

// Variables
SM_Matrix W1(2, 2), W2(3, 2), W31(3, 3, W31_arr), W32(3, 2, W32_arr), W4(1, 3);
SM_Matrix b1(2, 1), b2(3, 1), b31(3, 1, b31_arr), b32(3, 1, b32_arr), b4(1, 1);

NNLayers::DenseLayer<2> L1(3, NNActivations::Linear, W31, b31, W32, b32);

void NNLib_UT()
{
	
}