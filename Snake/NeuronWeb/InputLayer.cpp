#include "InputLayer.hpp"


InputLayer::InputLayer(int inputs_num)
{
	outputs.reserve(inputs_num);

	for (int i = 0; i < inputs_num; i++)
		outputs.push_back(0);

	//for (int i = 0; i < inputs_num; i++)
	//	outputs[i] = 0;
}


InputLayer::~InputLayer()
{
}


void InputLayer::set_inputs(std::vector<double> inputs)
{
	outputs = inputs;
}

std::vector<double> InputLayer::get_outputs()
{
	return outputs;
}