#include "Game.hpp"


Game::Game(int num)
{
	this->num = num;

	sf::Vector2f window_size(BORDER_WIDTH * 3 + DATA_WIDTH + CELLS_NUM * CELL_WIDTH, BORDER_HEIGHT * 2 + CELL_HEIGHT * CELLS_NUM);

	snake = new Snake*[num];
	for (int i = 0; i < num; i++)
		snake[i] = new Snake(CELLS_NUM);

	food = new Food(CELLS_NUM);

	food_coords = food->get_next();

	window = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "Snake"); 
	field = new sf::RectangleShape(sf::Vector2f(768, 768));
	field->setFillColor(sf::Color::Black);


	for (int i = 0; i < CELLS_NUM * 2 + 2; i += 2)
	{
		int x_coord = BORDER_WIDTH * 2 + DATA_WIDTH + (i / 2) * CELL_WIDTH;
		int y_coord = CELL_WIDTH * CELLS_NUM + BORDER_HEIGHT;

		vertical_lines[i] = sf::Vertex(sf::Vector2f(x_coord, BORDER_HEIGHT), sf::Color::White);
		vertical_lines[i + 1] = sf::Vertex(sf::Vector2f(x_coord, y_coord), sf::Color::White);

		x_coord = BORDER_WIDTH * 2 + DATA_WIDTH + CELL_HEIGHT * CELLS_NUM;
		y_coord = (i / 2) * CELL_HEIGHT + BORDER_HEIGHT;

		horizontal_lines[i] = sf::Vertex(sf::Vector2f(BORDER_WIDTH * 2 + DATA_WIDTH, y_coord), sf::Color::White);
		horizontal_lines[i + 1] = sf::Vertex(sf::Vector2f(x_coord, y_coord), sf::Color::White);
	}

	clock.restart();
}


Game::~Game()
{
	delete food;
	delete field;
	delete window;
}


void Game::go(std::vector<std::vector<double>> inputs)
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	time = clock.getElapsedTime().asMicroseconds();

	//keyboard_handler(); 

	if (time > 100000/* && is_alive*/)
	{
		for (int i = 0; i < num; i++)
		{
			if (inputs[i][0] > inputs[i][1] && inputs[i][0] > inputs[i][2] && inputs[i][0] > inputs[i][3] && snake[i]->dir != direction::right) snake[i]->dir = direction::left;
			else if (inputs[i][1] > inputs[i][0] && inputs[i][1] > inputs[i][2] && inputs[i][1] > inputs[i][3] && snake[i]->dir != direction::left) snake[i]->dir = direction::right;
			else if (inputs[i][2] > inputs[i][0] && inputs[i][2] > inputs[i][1] && inputs[i][2] > inputs[i][3] && snake[i]->dir != direction::down) snake[i]->dir = direction::up;
			else if (inputs[i][3] > inputs[i][0] && inputs[i][3] > inputs[i][1] && inputs[i][3] > inputs[i][2] && snake[i]->dir != direction::up) snake[i]->dir = direction::down;
			snake[i]->move();
		}
		clock.restart();
		collision_detector();
	}

	window->clear();
	draw_objects();
	window->display();
}


void Game::draw_objects()
{
	window->draw(*field);
	window->draw(vertical_lines, CELLS_NUM * 2 + 2, sf::Lines);
	window->draw(horizontal_lines, CELLS_NUM * 2 + 2, sf::Lines);

	sf::RectangleShape food_piece(sf::Vector2f(CELL_WIDTH - 1, CELL_HEIGHT - 1));
	food_piece.setPosition(origin_x + food_coords.x * CELL_WIDTH, origin_y + food_coords.y * CELL_HEIGHT);
	food_piece.setFillColor(sf::Color::Green);
	window->draw(food_piece);

	for (int i = 0; i < num; i++)
	{
		if (snake[i]->is_alive())
		{
			snake[i]->draw(window, CELL_WIDTH, CELL_HEIGHT, origin_x, origin_y);
		}
	}
}





//void Game::keyboard_handler()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake->dir != direction::right)
//		snake->dir = direction::left;
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake->dir != direction::left)
//		snake->dir = direction::right;
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake->dir != direction::down)
//		snake->dir = direction::up;
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake->dir != direction::up)
//		snake->dir = direction::down;
//}


void Game::collision_detector()
{
	for (int i = 0; i < num; i++)
	{
		if (snake[i]->get_head_coords().first < 0 ||
			snake[i]->get_head_coords().first >= CELLS_NUM ||
			snake[i]->get_head_coords().second < 0 ||
			snake[i]->get_head_coords().second >= CELLS_NUM)
			snake[i]->kill();

		for (int i = 1; i < snake[i]->get_length(); i++)
		{
			if (snake[i]->get_head_coords() == snake[i]->get_body_piece_coords(i)) snake[i]->kill();
		}

		if (snake[i]->get_head_coords().first == food_coords.x && snake[i]->get_head_coords().second == food_coords.y)
		{
			food_coords = food->get_next();
			snake[i]->feed();
		}
	}
}

std::vector<std::vector<float>> Game::get_distances()
{
	std::vector<std::vector<float>> distances;

	//distances.push_back(snake->get_head_coords().first - food_coords.x);																				// left
	//distances.push_back(sqrt(pow(snake->get_head_coords().first - food_coords.x, 2) + pow(snake->get_head_coords().second - food_coords.y, 2)));		// left-up
	//distances.push_back(snake->get_head_coords().second - food_coords.y);																				// up
	//distances.push_back(sqrt(pow(food_coords.x - snake->get_head_coords().first, 2) + pow(snake->get_head_coords().second - food_coords.y, 2)));		// right-up
	//distances.push_back(food_coords.x - snake->get_head_coords().first);																				// right
	//distances.push_back(sqrt(pow(food_coords.x - snake->get_head_coords().first, 2) + pow(food_coords.y - snake->get_head_coords().second, 2)));		// right-down
	//distances.push_back(food_coords.y - snake->get_head_coords().second);																				// down
	//distances.push_back(sqrt(pow(snake->get_head_coords().first - food_coords.x, 2) + pow(food_coords.y - snake->get_head_coords().second, 2)));		// left-down
	for (int i = 0; i < num; i++)
	{
		std::vector<float> temp;
		temp.push_back(snake[i]->get_head_coords().first - food_coords.x);
		temp.push_back(snake[i]->get_head_coords().second - food_coords.y);
		temp.push_back(snake[i]->get_head_coords().first);
		temp.push_back(CELLS_NUM - snake[i]->get_head_coords().first);
		temp.push_back(snake[i]->get_head_coords().second);
		temp.push_back(CELLS_NUM - snake[i]->get_head_coords().second);

		distances.push_back(temp);
	}

	return distances;
}


bool Game::is_all_dead()
{
	bool flag = false;
	for (int i = 0; i < num; i++)
		flag = snake[i]->is_alive() + flag;

	return !flag;
}



float* Game::get_fitness()
{
	float *fitness = new float[num];

	for (int i = 0; i < num; i++)
		fitness[i] = snake[i]->get_fitness();

	return fitness;
}