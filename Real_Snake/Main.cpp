#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include "Snake.h"
#include "World.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake!");
	sf::Vector2u worldSize(800, 600);
	World world(worldSize);
	Snake snake(16);
	float elapsetime = 0;
	sf::Clock clock;
	float timer = 0;
	int thescore = 0;
	sf::Font font;
	sf::Font arial;

	arial.loadFromFile("arial.ttf");
	font.loadFromFile("Halo.ttf");
	sf::Text text("Score", arial, 20);
	sf::Text score("temp", arial, 20);
	score.setPosition(30, 40);
	text.setPosition(20, 10);
	int lives;
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
		thescore = snake.GetScore();
		std::stringstream ss;
		std::stringstream sd;
		ss << thescore;
		score.setString(ss.str().c_str());
		lives = snake.GetLives();
		sd << lives;
		text.setString(sd.str().c_str());

		window.clear();
		snake.Render(window);
		world.Render(window);
		window.draw(text);
		window.draw(score);
		window.display();
	}

	return 0;
}