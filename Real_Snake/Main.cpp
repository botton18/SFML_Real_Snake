#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Snake.h"
#include "World.h"
#include <Windows.h>
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake!");
	sf::Vector2u worldSize(800, 600);
	World world(worldSize);
	Snake snake(16);
	float elapsetime = 0;
	sf::Clock clock;
	float timer = 0;
	sf::Font font;
	font.loadFromFile("arial.tff");
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		float delay = 0.2;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (timer > delay)
		{
			timer = 0;
			snake.Tick();
			world.update(snake);
			if (snake.HasLost())
			{
				snake.Reset();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && snake.GetDirection() != Direction::Down)
		{
			snake.setDirection(Direction::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && snake.GetDirection() != Direction::Right)
		{
			snake.setDirection(Direction::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && snake.GetDirection() != Direction::Up)
		{
			snake.setDirection(Direction::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && snake.GetDirection() != Direction::Left)
		{
			snake.setDirection(Direction::Right);
		}
		

		window.clear();
		snake.Render(window);
		world.Render(window);
		window.display();
	}

	return 0;
}