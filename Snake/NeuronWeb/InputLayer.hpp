#pragma once
#include <vector>

class InputLayer
{

public:
	std::vector<double> outputs;

	InputLayer(int inputs_num);
	~InputLayer();

	void set_inputs(std::vector<double> inputs);
	std::vector<double> get_outputs();
};

