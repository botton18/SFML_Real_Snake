#include "World.h"
#include <ctime>

World::World(sf::Vector2u windowsize)
{
	BlockSize = 16;
	windowSize = windowsize;
	RespawnApple();
	appleShape.setFillColor(sf::Color::Red);
	appleShape.setRadius(BlockSize / 2);

	for (int i = 0; i < 4; ++i)
	{
		bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
		{
			bounds[i].setSize(sf::Vector2f(windowSize.x, BlockSize)); //Top and bottom
		}
		else
		{
			bounds[i].setSize(sf::Vector2f(BlockSize, windowSize.y)); //Left and right
		}

		if (i < 2)
		{
			bounds[i].setPosition(0, 0);
		}
		else
		{
			bounds[i].setOrigin(bounds[i].getSize());
			bounds[i].setPosition(sf::Vector2f(windowSize));
		}
	}
}

int World::getBlockSize()
{
	return BlockSize;
}

void World::RespawnApple()
{
	int MaxX = (windowSize.x / BlockSize) - 2;
	int MaxY = (windowSize.y / BlockSize) - 2;
	item = sf::Vector2i(rand() % MaxX + 1, rand() % MaxY + 1);
	appleShape.setPosition(item.x * BlockSize, item.y * BlockSize);
}

void World::update(Snake & player)
{
	if (player.GetPosition() == item)
	{
		player.Extend();
		player.IncreaseScore();
		RespawnApple();
	}

	int gridSizeX = windowSize.x / BlockSize; // Checks if it touches Left Or Right
	int gridSizeY = windowSize.y / BlockSize; // checks if it touches Top Or Bottom

	if (player.GetPosition().x <= 0 || player.GetPosition().x >= gridSizeX - 1 || player.GetPosition().y <= 0 || player.GetPosition().y >= gridSizeY - 1)
	{
		player.Lose();
	}
}

void World::Render(sf::RenderWindow window)
{
	for (int i = 0; i < 4; ++i)
	{
		window.draw(bounds[i]);
	}
	window.draw(appleShape);
}

