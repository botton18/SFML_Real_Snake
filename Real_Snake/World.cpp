#include "World.h"

World::World(sf::Vector2u windowsize)
{
	BlockSize = 16;
	windowSize = windowsize;
	RespawnApple();
	appleShape.setFillColor(sf::Color::Red);
	appleShape.setRadius(BlockSize / 2);

}

int World::getBlockSize()
{
	return 0;
}

void World::RespawnApple()
{
}

void World::update(Snake & player)
{
}

void World::Render(sf::RenderWindow window)
{
}


