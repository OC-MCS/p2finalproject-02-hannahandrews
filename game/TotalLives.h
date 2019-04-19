#pragma once
#include "SingleLife.h"
#include <list>
#include "Alien.h"
#include "BombSquad.h"
#include "Bomb.h"

class totalLives
{
private:
	Texture heartTexture;		//this is the texture for each life
public:
	list<singleLife> lives;		//this is the list of lives the user has
	int livesRemaining;			//this int represents the amount in the lives list...
								//aka lives the user has left

	//construcer
	totalLives(RenderWindow &win, int currentLives)
	{
		if (!heartTexture.loadFromFile("Heart.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}

		livesRemaining = currentLives;

		for (int i = 0; i < livesRemaining; i++)
		{
			Vector2f position;

			position.x = 40 * i;
			position.y = 10;

			singleLife tempLife(position, heartTexture);

			lives.push_back(tempLife);
		}
	}

	///////////////////////////////////////////////
	//drawLives: this calls the function to draw
	//		the lives on the screen
	///////////////////////////////////////////////
	void drawLives(RenderWindow &win)
	{
		list<singleLife>::iterator iter = lives.begin();

		for (int i=0; i < livesRemaining; i++)
		{
			iter->drawLife(win);
			iter++;
		}
	}

	//////////////////////////////////////////////
	//alienHitShip: this tests to see if an alien
	//		collided with the ship
	//////////////////////////////////////////////
	bool alienHitShip(AlienSquad aliens, Vector2f shipPos)
	{
		bool shipStruck = false; 

		list<Alien>::iterator alienIter = aliens.alienList.begin();
		list<singleLife>::iterator livesIter = lives.begin();
		Vector2f shipLoc = shipPos;

		if (alienIter ->testContainsShip(shipLoc))
		{
			lives.erase(livesIter);
			livesRemaining--;
			shipStruck = true;
		}


		return shipStruck;
	}

	/////////////////////////////////////////////////
	//bombHitShip: this tests to see if a bomb collided
	//		with the ship
	///////////////////////////////////////////////////
	bool bombHitShip(BombSquad bomb, Vector2f shipPos)
	{
		bool shipStruck = false;

		list<Bombclass>::iterator bombIter = bomb.bomblist.begin();
		list<singleLife>::iterator livesIter = lives.begin();
		Vector2f shipLoc = shipPos;

		for (int i=0; i < bomb.bomblist.size() && shipStruck == false; i++)
		{
			if (bombIter->testContainsShip(shipLoc) == true)
			{
				lives.erase(livesIter);
				livesRemaining--;
				shipStruck = true;
			}

			bombIter++;
		}


		return shipStruck;
	}
};