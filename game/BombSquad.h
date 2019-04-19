#pragma once
#include "bomb.h"
#include "AlienSquad.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class BombSquad
{
private:
	Vector2f position;
public:
	list<Bombclass> bombsdropped;

	BombSquad()
	{}

	void dropBomb(Vector2f position)
	{
		Bombclass addbomb(position);

		bombsdropped.push_back(addbomb);
	}

	void moveBomb(int level)
	{
		list<Bombclass>::iterator iter;

		for (iter = bombsdropped.begin(); iter != bombsdropped.end(); iter++)
		{
			iter->moveBomb(level);
		}
	}

	void displayBombs(RenderWindow &win)
	{
		list<Bombclass>::iterator iter;

		for (iter = bombsdropped.begin(); iter != bombsdropped.end(); iter++)
		{
			iter->displayBomb(win);
		}
	}
};