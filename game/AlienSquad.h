#pragma once
#include <list>
#include "Alien.h"
#include "MissileSquad.h"
#include <ctime>
#include <cstdlib>
using namespace sf;

//This class should contain multiple a link list
//of aliens
class AlienSquad
{
private:
	Texture alienTexture;
	Vector2f position;
public:
	int numAliensHit =0;
	list<Alien> alienList;		//this is the list that contains the set of 10 aliens

	////////////////////////////////////////////////////
	//Constructer: This is a constructer that creates 
	//	the initial 10 aliens that appear on the screen
	/////////////////////////////////////////////////////
	AlienSquad(RenderWindow &win, int levelnumber)
	{
		if (levelnumber == 1)
		{
			if (!alienTexture.loadFromFile("alien1.png"))
			{
				cout << "Unable to load ship texture!" << endl;
				exit(EXIT_FAILURE);
			}
		}
		else if (levelnumber == 2)
		{
			if (!alienTexture.loadFromFile("alien2.png"))
			{
				cout << "Unable to load ship texture!" << endl;
				exit(EXIT_FAILURE);
			}
		}


		for (int i=0; i < 10; i++)
		{
			position.x = i * 75;
			position.y = 20;

			Alien alienHolder(alienTexture, position);
		
			alienList.push_back(alienHolder);
		}
	}
	////////////////////////////////////////////////////////////
	//draw: This is the function that calls the alien.h function
	//		that draws the aliens
	////////////////////////////////////////////////////////////
	void draw(RenderWindow &win)
	{
		list<Alien>::iterator it;
		for (it = alienList.begin(); it != alienList.end(); it++)
		{
			it->draw(win);
		}
	}
	///////////////////////////////////////////////////////
	//move: This function is what calls the alien.h function
	//		that moves the aliens down the screen		
	///////////////////////////////////////////////////////
	void move(RenderWindow &win, int levelnumber)
	{
		list<Alien>::iterator it;
		for (it = alienList.begin(); it != alienList.end(); it++)
		{
			it->move(win,  levelnumber);
		}
	}

	////////////////////////////////////////////////////////
	//checkIntersection: This function checks to see if the 
	//		missile has colided with an alien
	//currently working if you dont rapid fire
	////////////////////////////////////////////////////////
	void AlienHitByMissile(list<Missile> &missiles)
	{
		bool alienHit = false;
		list<Alien>::iterator alienIter = alienList.begin();
		list<Missile>::iterator missileIter;

		for (int i=0; i < alienList.size() && alienHit == false; i++)
		{
      			missileIter = missiles.begin();
 			for (int j=0; j < missiles.size() && alienHit == false; j++)
			{
				Vector2f position = (missileIter->missileLoc());

				if (alienIter->testAlienHit(position) == true)
				{
					alienList.erase(alienIter);
					missiles.erase(missileIter);
					numAliensHit++;
					alienHit = true;
				}
				else missileIter++;
			}
			if (alienHit == false)
			{
				alienIter++;
			}
		}
	}

	Vector2f getRandomAlienLocation()
	{
		Vector2f location;
		list<Alien>::iterator iter;

		unsigned seed = time(0);

		srand(seed);

		 int position = rand() % alienList.size();
		
		iter = alienList.begin();

	
		for(int i=0; i < position; i++)
		{
			iter++;
		}

		location = iter->alienLocation();

		return location;
	}
};