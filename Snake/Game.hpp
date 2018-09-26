#include "SFML/Graphics.hpp"
#include "Food.hpp"
#include "Snake.hpp"
#include <vector>
#pragma once

class Game
{
	sf::Event event;
	sf::RectangleShape *field;
	sf::RenderWindow *window;	

	//Snake *snake;
	Snake **snake;
	Food *food;

	sf::Vector2f food_coords;
	
	sf::Clock clock;
	float time;
	int num;

	sf::Vertex vertical_lines[62];
	sf::Vertex horizontal_lines[62];


	const int BORDER_WIDTH = 20;
	const int BORDER_HEIGHT = 20;

	const int DATA_WIDTH = 200;

	const int CELL_WIDTH = 20;
	const int CELL_HEIGHT = 20;

	const int CELLS_NUM = 30;


	int origin_x = 2 * BORDER_WIDTH + DATA_WIDTH;
	int origin_y = BORDER_HEIGHT;


	void draw_objects();
	void keyboard_handler();
	void collision_detector();

public:

	Game(int num);
	~Game(); 
	void go(std::vector<std::vector<double>> inputs);
	std::vector<std::vector<float>> get_distances();
	float* get_fitness();

	bool is_all_dead();

	sf::RenderWindow* get_window() { return window; }
};
