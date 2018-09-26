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

	// ошибка выходов
	double *errors = new double[neurons_quantity];
	// ошибка весов предыдущего слоя
	double** hidden_errors = new double*[neurons_quantity];
	for (int i = 0; i < neurons_quantity; i++)
		hidden_errors[i] = new double[inputs_quantity];

	// Высчитываем ошибку на выходах
	std::vector<double> outputs = get_outputs();

	for (int i = 0; i < targets_length; i++)
		errors[i] = targets[i] - outputs[i];

	// Высчитываем ошибку на весах предыдущего слоя и обновляем весовые коэффициенты
	for (int i = 0; i < neurons_quantity; i++)
		for (int j = 0; j < inputs_quantity; j++)
		{
			hidden_errors[i][j] = errors[i] * (neurons[i]->weights[j] / neurons[i]->weights_sum());
			neurons[i]->weights[j] += hidden_errors[i][j] * learning_grate;
		}

	// ошибка на выходе предыдущего слоя
	double *error_of_previous_layer = new double[inputs_quantity];
	memset(error_of_previous_layer, 0, sizeof(double) * inputs_quantity);

	// Расчет ошибки на выходе предыдущего слоя
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