#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Snake.h"
#include "World.h"

class Game
{
private:
	World world;
	Snake snake;

public:
	Game();
	void Update();
	void Render();
};