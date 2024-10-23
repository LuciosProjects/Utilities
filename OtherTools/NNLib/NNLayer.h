#ifndef _NN_LAYER_H
#define _NN_LAYER_H

enum class ELayerTypes
{
	Null,
	Dense
};

typedef double (*ScalarActivationFcnPtr)(double&);

template<size_t NChildren = 1>
class NN_Layer
{
private:

public:

	NN_Layer() {};
	~NN_Layer() {};

	NN_Layer* parent = nullptr;
	std::array<NN_Layer*, NChildren> children;

	ScalarActivationFcnPtr ActivationFcn = nullptr;
	ELayerTypes LayerType = ELayerTypes::Null;
};

namespace NNLayers
{
	template<size_t NChildren = 1>
	class DenseLayer : NN_Layer<NChildren>
	{
	private:

	public:
		template<typename... Args>
		DenseLayer(size_t size, ScalarActivationFcnPtr Activation, const Args&... args) : Size(size), Weights{}, Biases{}
		{
			constexpr size_t arr_size = sizeof...(args);

			static_assert(arr_size % 2 == 0, "Incomplete weight-bias pair");

			std::array<SM_Matrix<>,arr_size> arr = { args... }; // Pack the matrices into an array

			int jumper_idx;

			for (jumper_idx = 0; jumper_idx < arr_size; jumper_idx += 2)
			{
				if (arr[jumper_idx].Nrows == size && arr[jumper_idx + 1].Nrows == size) // Verifying valid dimensions
				{
					Weights[jumper_idx/2].ReInit(arr[jumper_idx]);
					Biases[jumper_idx/2].ReInit(arr[jumper_idx + 1]);
				}
				else
				{
					continue;
				}
			}

			NN_Layer<NChildren>::ActivationFcn	= Activation;
			NN_Layer<NChildren>::LayerType		= ELayerTypes::Dense;
		};

		~DenseLayer() {};

		std::array<SM_Matrix<>, NChildren> Weights;
		std::array<SM_Matrix<>, NChildren> Biases;
		size_t Size;
	};
}

#endif