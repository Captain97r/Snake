#include "Neuron.hpp"
#include <cmath>


Neuron::Neuron(int previous_neurons_quantity, std::vector<double> input_data)
{
	inputs_num = previous_neurons_quantity;

	weights.reserve(previous_neurons_quantity);
	for (int i = 0; i < previous_neurons_quantity; i++)
		weights.push_back(0);

	inputs = input_data;
}


Neuron::~Neuron()
{
}


double Neuron::derivation()
{
	double result = 0;
	for (int i = 0; i < inputs_num; i++)
	{
		result += inputs[i] * weights[i];
	}
	return result;
}


double Neuron::sigm_conversion()
{
	return pow(1 + exp(-derivation()), -1);
}

double Neuron::weights_sum()
{
	double result = 0;

	for (int i = 0; i < inputs_num; i++)
		result += weights[i];

	return result;
}


void Neuron::set_weights(std::vector<double> weights)
{
	for (int i = 0; i < inputs_num; i++)
		this->weights[i] = weights[i];
}


std::vector<double> Neuron::get_weights()
{
	return weights;
}


void Neuron::set_inputs(std::vector<double> inputs)
{
	this->inputs = inputs;
}