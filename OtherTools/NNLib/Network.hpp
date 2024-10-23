#ifndef _NETWORK_H
#define _NETWORK_H

template<size_t NLayers = 2>
class Network
{
private:
	/* Private Members */
	std::array<NN_Layer<>, NLayers> Layers;

public:
	Network() {};

	//Network(NN_Layer LayersIn[])
	//{
	//	int i;
	//	for (i = 0; i < numLayers; i++)
	//	{
	//		Layers[i] = LayersIn[i];
	//	}
	//}

	//Network(NN_Layer_Container LayersIn)
	//{
	//	int i;
	//	for (i = 0; i < numLayers; i++)
	//	{
	//		Layers[i] = LayersIn[i];
	//	}
	//}

	~Network() {};

	double Predict()
	{
		return 0;
	}

	/* Public Members */
	int numLayers = NLayers;
};

#endif
