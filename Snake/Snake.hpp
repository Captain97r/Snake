#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Snake
{
	std::vector<std::pair<int, int>> snake;

	int fitness = 0;
	bool state;
	const int INITIAL_SNAKE_LEN = 4;

public:
	enum direction dir;

	Snake(int cells_num);
	~Snake();
	void move();
	void draw(sf::RenderWindow *window, int CELL_WIDTH, int CELL_HEIGHT, int origin_x, int origin_y);

	int get_length() { return snake.size(); }
	std::pair<int, int> get_body_piece_coords(int i) { return snake[i]; }
	std::pair<int, int> get_head_coords() { return snake[0]; }
	bool is_alive() { return state; }
	void kill() { state = false; }
	void feed() { snake.push_back(std::pair<int, int>(-100, -100)); fitness += 100; }
	int get_fitness() { return fitness; }
};


enum direction { left, right, up, down, null };