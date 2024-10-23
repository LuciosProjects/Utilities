#ifndef _NNACTIVATIONFUNCTIONS_H
#define _NNACTIVATIONFUNCTIONS_H

namespace NNActivations
{
	inline double Linear(double& x) { return x; }
	inline double Sigmoid(double& x) { return 1 / (1 + exp(-x)); }
	inline double ReLU(double& x) { return fmax(0,x); };
	//inline double* Softmax(double* In, size_t size)
	//{

	//}

}

#endif
