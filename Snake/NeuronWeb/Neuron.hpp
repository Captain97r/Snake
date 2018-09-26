#pragma once
#include <vector>

class Neuron
{
	int inputs_num;
	std::vector<double> inputs;

	double derivation();

public:
	std::vector<double> weights;

	Neuron(int previous_neurons_quantity, std::vector<double> input_data);
	~Neuron();

	double sigm_conversion();
	double weights_sum();

	void set_weights(std::vector<double> weights);
	std::vector<double> get_weights();

	void set_inputs(std::vector<double> input);
};

