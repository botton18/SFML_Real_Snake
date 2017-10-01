#include "Snake.h"

Snake::Snake(int blocksize)
{
	size = blocksize;
	rect.setSize(sf::Vector2f(size - 1, size - 1));
	Reset();

}

void Snake::setDirection(Direction _dir)
{
	dir = _dir;
}

Direction Snake::GetDirection()
{
	return dir;
}

sf::Vector2i Snake::GetPosition()
{
	if (!Body.empty())
	{
		return Body.front().position;
	}
	else
	{
		return sf::Vector2i(1, 1);
	}
}

int Snake::GetSpeed()
{
	return speed;
}

int Snake::GetLives()
{
	return lives;
}

int Snake::GetScore()
{
	return score;
}

void Snake::IncreaseScore()
{
	score += 10;
}

bool Snake::HasLost()
{
	return lost;
}

void Snake::Lose()
{
	lost = true;
}

void Snake::ToggleLost()
{
	lost = !lost;
}

void Snake::CheckCollision()
{
	if (Body.size() > 5)
	{
		SnakeSegment& head = Body.at(0);
		for (auto itr = Body.begin() + 1; itr != Body.end(); ++itr)
		{
			if (itr->position == head.position)//Collision detected
			{
				int segments = Body.end() - itr;
				Cut(segments);
				break;
			}
		}
	}
}

void Snake::Extend()
{
	if (Body.empty())
	{
		return;
	}

	SnakeSegment& tailhead = Body.at(Body.size() - 1); // set tailhead to last index of the snake

	if (Body.size() > 1)
	{
		SnakeSegment& tailbone = Body.at(Body.size() - 2);
		if (tailhead.position.x == tailbone.position.x) //Snake is on the same x axis, so it's moving either up or down
		{
			if (tailhead.position.y > tailbone.position.y) //Snake is moving up
			{
				Body.push_back(SnakeSegment(tailhead.position.x, tailhead.position.y + 1));
			}
			else
			{
				Body.push_back(SnakeSegment(tailhead.position.x, tailhead.position.y - 1));
			}
		}
		else if (tailhead.position.y == tailbone.position.y) //Snake is on the same y axis, so it's moving either left or right
		{
			if (tailhead.position.x > tailbone.position.x) //Snake is moving left
			{
				Body.push_back(SnakeSegment(tailhead.position.x + 1, tailhead.position.y));
			}
			else
			{
				Body.push_back(SnakeSegment(tailhead.position.x - 1, tailhead.position.y));
			}
		}
	}
	else
	{
		if (dir == Direction::Up)
		{
			Body.push_back(SnakeSegment(tailhead.position.x, tailhead.position.y + 1));
		}
		else if (dir == Direction::Down)
		{
			Body.push_back(SnakeSegment(tailhead.position.x, tailhead.position.y - 1));
		}
		else if (dir == Direction::Left)
		{
			Body.push_back(SnakeSegment(tailhead.position.x + 1, tailhead.position.y));
		}
		else if (dir == Direction::Right)
		{
			Body.push_back(SnakeSegment(tailhead.position.x - 1, tailhead.position.y));
		}
		
	}

}

void Snake::Reset()
{
	Body.clear();

	Body.push_back(SnakeSegment(5, 7));
	Body.push_back(SnakeSegment(5, 6));
	Body.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);
	speed = 15;
	lives = 3;
	score = 0;
	lost = false;
}

void Snake::Move()
{
	for (int i = Body.size() - 1; i > 0; --i)
	{
		Body.at(i).position = Body.at(i - 1).position;
	}
	if (dir == Direction::Up)
	{
		--Body.at(0).position.y;
	}
	else if (dir == Direction::Down)
	{
		++Body.at(0).position.y;
	}
	else if (dir == Direction::Left)
	{
		--Body.at(0).position.x;
	}
	else if (dir == Direction::Right)
	{
		++Body.at(0).position.x;
	}
}

void Snake::Tick()
{
	if (Body.empty())
	{
		return;
	}
	if(dir == Direction::None)
	{
		return;
	}
	Move();
	CheckCollision();
}

void Snake::Cut(int segment)
{
	for (int i = 0; i < segment; ++i)
	{
		Body.pop_back();
	}
	--lives;
	if (lives == 0)
	{
		Lose();
		return;
	}

}

void Snake::Render(sf::RenderWindow window)
{
	if (Body.empty())
	{
		return;
	}
	
	auto head = Body.begin();
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(head->position.x * size, head->position.y * size);
	window.draw(rect);

	rect.setFillColor(sf::Color::Green);
	for (auto itr = Body.begin(); itr != Body.end(); ++itr)
	{
		rect.setPosition(itr->position.x * size, itr->position.y * size);
		window.draw(rect);
	}
	
}
