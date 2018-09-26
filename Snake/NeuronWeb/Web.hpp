#pragma once
#include <SFML/Graphics.hpp>
#include "InputLayer.hpp"
#include "HiddenLayer.hpp"

class Web
{
	InputLayer *input_layer;
	HiddenLayer **hidden_layers;
	HiddenLayer *output_layer;

	int hidden_layers_num;
	int outputs_num;
	int* neurons_in_hidden_layers;
	int inputs_num;

	int selection(Web** best_webs, Web** webs, float* fitnesses, int num, int fitness_treshold);
	void crossover(Web** webs, Web** best_webs, int num, int best_num);
	void mutation(Web** webs, int num);


	int partition(float *a, int p, int r);
	void quicksort(float *a, int p, int r);
	int search(float *f, float num, int n, int except = -1);

public:

	Web(int inputs_num, int hidden_layers_num, int* neurons_in_hidden_layers, int outputs_num);
	~Web();
	void back_propagation(double *targets);

	bool evolution(Web** webs, float* fitnesses, int num, int fitness_treshold);

	void set_inputs(std::vector<float> inputs); 
	void set_inputs(sf::Vector2f inputs);
	void set_inputs(std::pair<float, float> inputs);
	std::vector<double> get_outputs();
};

