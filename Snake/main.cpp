#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "NeuronWeb/Web.hpp"

int inputs = 6;
int hidden_layers = 2;
int neurons_in_hidden_layers[2] = { 5, 4 };
int outputs = 4;
int fitness_treshold = 50;

int webs_num = 100;

int main()
{
	bool first = true;
	bool create_new = true;
	Web **web = new Web*[webs_num];

	for (;;)
	{
		if (create_new)
		{
			for (int i = 0; i < webs_num; i++)
			{
				if (!first) delete web[i];
				web[i] = new Web(inputs, hidden_layers, neurons_in_hidden_layers, outputs);
			}
		}
		first = false;

		Game game(webs_num);

		std::vector<std::vector<float>> distances;
		std::vector<std::vector<double>> outputs;

		while (game.get_window()->isOpen())
		{
			distances = game.get_distances();

			for (int i = 0; i < webs_num; i++)
			{
				web[i]->set_inputs(distances[i]);
				outputs.push_back(web[i]->get_outputs());
			}
			game.go(outputs);
			outputs.clear();
			if (game.is_all_dead()) break;
		}

		float *fitnesses = game.get_fitness();
		create_new = web[0]->evolution(web, fitnesses, webs_num, fitness_treshold);

		delete[] fitnesses;
	}
	return 0;
}