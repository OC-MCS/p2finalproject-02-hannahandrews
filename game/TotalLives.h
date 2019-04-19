#pragma once
#include "SingleLife.h"
#include <list>
#include "Alien.h"

class totalLives
{
private:
public:
	list<singleLife> lives;
	int livesRemaining;

	totalLives(RenderWindow &win)
	{
		livesRemaining = 3;

		for (int i = 0; i < livesRemaining; i++)
		{
			Vector2f position;

			position.x = 40 * i;
			position.y = 10;

			singleLife tempLife(position);

			lives.push_back(tempLife);
		}
	}

	void drawLives(RenderWindow &win)
	{
		list<singleLife>::iterator iter;

		for (iter = lives.begin(); iter != lives.end(); iter++)
		{
			iter->drawLife(win);
		}
	}

	void shipHit(list<Alien> &aliens, Vector2f shipPos)
	{
		list<Alien>::iterator alienIter = aliens.begin();
		list<singleLife>::iterator livesIter = lives.begin();
		Vector2f shipLoc = shipPos;
		Vector2f alienLoc = alienIter->alienLocation();

		if (alienLoc.y == shipLoc.x)
		{
			lives.erase(livesIter);
			livesRemaining--;
		}
	}
};