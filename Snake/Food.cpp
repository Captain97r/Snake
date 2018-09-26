#include "Food.hpp"

Food::Food(int cells_num)
{
	field_size = cells_num;
}


Food::~Food()
{
}


sf::Vector2f Food::get_next()
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_real_distribution<> distribution(0, field_size - 1);

	food_coords = sf::Vector2f(round(distribution(generator)), round(distribution(generator)));
	return food_coords;
}