#include "Snake.hpp"



Snake::Snake(const int cells_num)
{
	state = true;

	for (int i = 0; i < INITIAL_SNAKE_LEN; i++)
		snake.push_back(std::pair<int, int>((cells_num / 2) + i, cells_num / 2));

	dir = direction::left;
}


Snake::~Snake()
{
}


void Snake::move()
{
	for (size_t i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1];

	switch (dir)
	{
	case left:
		snake[0].first--;
		break;
	case right:
		snake[0].first++;
		break;
	case up:
		snake[0].second--;
		break;
	case down:
		snake[0].second++;
		break;
	default:
		// No implementation
		break;
	}
	fitness++;
}


void Snake::draw(sf::RenderWindow *window, const int CELL_WIDTH, const int CELL_HEIGHT, const int origin_x, const int origin_y)
{
	for (size_t i = 0; i < snake.size(); i++)
	{
		sf::RectangleShape body(sf::Vector2f(CELL_WIDTH - 1, CELL_HEIGHT - 1));
		body.setPosition(origin_x + snake[i].first * CELL_WIDTH, origin_y + snake[i].second * CELL_HEIGHT);
		body.setFillColor(i == 0 ? sf::Color::Blue : sf::Color::Red);
		window->draw(body);
	}
}