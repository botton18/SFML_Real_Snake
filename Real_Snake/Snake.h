#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
struct SnakeSegment
{
	sf::Vector2i position;

	SnakeSegment(int x, int y)
	{
		position = sf::Vector2i(x, y);
	}
};

using SnakeContainer = vector<SnakeSegment>;

enum class Direction{ None, Up, Down, Left, Right };

class Snake
{
private:
	int speed;
	int lives;
	int score;
	bool lost;
	int size;
	Direction dir;
	SnakeContainer Body;
	sf::RectangleShape rect;
public:
	Snake(int blocksize);

	void setDirection(Direction _dir);
	Direction GetDirection();
	sf::Vector2i GetPosition();
	int GetSpeed();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();

	void Lose();
	void ToggleLost();
	void CheckCollision();
	void Extend();
	void Reset();
	void Move();
	void Tick();
	void Cut(int segment);
	void Render(sf::RenderWindow window);
};