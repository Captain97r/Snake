#include <SFML/Graphics.hpp>
#include <random>
#pragma once

class Food
{
	int field_size;
	sf::Vector2f food_coords;	
	
public:
	Food(int cells_num);
	~Food();

	sf::Vector2f get_next();
};

