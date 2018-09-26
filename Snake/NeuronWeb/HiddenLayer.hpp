#pragma once
#include "Neuron.hpp"
#include <vector>

class HiddenLayer
{
	int inputs_quantity;
	int neurons_quantity;

	void set_weights();

public:
	Neuron **neurons;

	HiddenLayer(int inputs_quantity, int neurons_quantity, std::vector<double> inputs);
	~HiddenLayer();
	double* back_propagation(double *targets, int targets_length);
	std::vector<double> get_outputs();
	//Neuron** get_neurons();
};

