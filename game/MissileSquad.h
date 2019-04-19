
#pragma once
#include "Missile.h"
#include "Alien.h"
#include <list>

//This class should hold multiple instances for 
//a missile, calls the function to delete the bullet
//when it collides with an alien
class MissileSquad
{
private:
	Texture missileTexture;
public:
	list<Missile> bullets;

	MissileSquad() 
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}

	}

	void addToList(Vector2f &ShipPosition)
	{
		Missile temp(ShipPosition, missileTexture);

		bullets.push_back(temp);
	}

	void draw(RenderWindow &win)
	{
		list<Missile>::iterator it;
		for (it = bullets.begin(); it != bullets.end(); it++)
		{
			it->draw(win);
		}
	}

	void move(RenderWindow &win)
	{
		list<Missile>::iterator it;
		for (it = bullets.begin(); it != bullets.end(); it++)
		{
			it->moveMissile(win);
		}
	}

	void erase(list<Missile>::iterator iter)
	{
		bullets.erase(iter);
	}

};