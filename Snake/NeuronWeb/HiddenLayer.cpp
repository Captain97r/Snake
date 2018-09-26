#include "HiddenLayer.hpp"
#include "Neuron.hpp"
#include <random>


HiddenLayer::HiddenLayer(int inputs_quantity, int neurons_quantity, std::vector<double> inputs)
{
	this->inputs_quantity = inputs_quantity;
	this->neurons_quantity = neurons_quantity;

	neurons = new Neuron*[neurons_quantity];
	for (int i = 0; i < neurons_quantity; i++)
		neurons[i] = new Neuron(inputs_quantity, inputs);

	set_weights();
}


HiddenLayer::~HiddenLayer()
{
	for (int i = 0; i < neurons_quantity; i++)
		delete[] neurons[i];

	delete[] neurons;
}


void HiddenLayer::set_weights()
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_real_distribution<> distribution(-pow(inputs_quantity, -0.5), pow(inputs_quantity, -0.5));

	std::vector<double> weights;

	for (int i = 0; i < neurons_quantity; i++)
	{
		for (int j = 0; j < inputs_quantity; j++)
		{
			weights.push_back(distribution(generator));
		}
		neurons[i]->set_weights(weights);
		weights.clear();
	}
}

double* HiddenLayer::back_propagation(double *targets, int targets_length)
{
	double learning_grate = 0.1;

	// ������ �������
	double *errors = new double[neurons_quantity];
	// ������ ����� ����������� ����
	double** hidden_errors = new double*[neurons_quantity];
	for (int i = 0; i < neurons_quantity; i++)
		hidden_errors[i] = new double[inputs_quantity];

	// ����������� ������ �� �������
	std::vector<double> outputs = get_outputs();

	for (int i = 0; i < targets_length; i++)
		errors[i] = targets[i] - outputs[i];

	// ����������� ������ �� ����� ����������� ���� � ��������� ������� ������������
	for (int i = 0; i < neurons_quantity; i++)
		for (int j = 0; j < inputs_quantity; j++)
		{
			hidden_errors[i][j] = errors[i] * (neurons[i]->weights[j] / neurons[i]->weights_sum());
			neurons[i]->weights[j] += hidden_errors[i][j] * learning_grate;
		}

	// ������ �� ������ ����������� ����
	double *error_of_previous_layer = new double[inputs_quantity];
	memset(error_of_previous_layer, 0, sizeof(double) * inputs_quantity);

	// ������ ������ �� ������ ����������� ����
	for (int i = 0; i < inputs_quantity; i++)
		for (int j = 0; j < neurons_quantity; j++)
			error_of_previous_layer[i] += hidden_errors[j][i];

	delete[] errors;
	for (int i = 0; i < neurons_quantity; i++)
		delete[] hidden_errors[i];
	delete[] hidden_errors;

	return error_of_previous_layer;
}


std::vector<double> HiddenLayer::get_outputs()
{
	std::vector<double> result;

	for (int i = 0; i < neurons_quantity; i++)
		result.push_back(neurons[i]->sigm_conversion());
	return result;
}