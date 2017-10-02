#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Snake.h"
#ifndef WORLD_H
#define WORLD_H

using namespace std;
class World
{
private:
	sf::Vector2u windowSize;
	sf::Vector2i item;
	int BlockSize;

	sf::CircleShape appleShape;
	sf::RectangleShape bounds[4];

public:
	World(sf::Vector2u windowsize);

	int getBlockSize();

	void RespawnApple();

	void update(Snake& player);

	void Render(sf::RenderWindow & window);

};
#endif