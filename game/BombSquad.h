#pragma once
#include "bomb.h"
#include "AlienSquad.h"
#include <SFML/Graphics.hpp>
using namespace sf;

//This is the class for the list of bombs
class BombSquad
{
private:
	Vector2f position;		//positoin holds the position of the bomb
	Texture bombTexture;	//this is the texture of the bomb
public:
	list<Bombclass> bomblist;

	//default constructer
	BombSquad()
	{
		if (!bombTexture.loadFromFile("bomb.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	////////////////////////////////////////
	//dropBomb: This adds a Bombclass member to 
	//		the list
	////////////////////////////////////////
	void dropBomb(Vector2f position)
	{
		Bombclass addbomb(position, bombTexture);

		bomblist.push_back(addbomb);
	}

	///////////////////////////////////////////
	//moveBomb: This  calls the move function
	//		for the list of Bombclass
	//////////////////////////////////////////
	void moveBomb(int level)
	{
		list<Bombclass>::iterator iter;

		for (iter = bomblist.begin(); iter != bomblist.end(); iter++)
		{
			iter->moveBomb(level);
		}
	}

	////////////////////////////////////////////////
	//displayBombs: This calls the display function
	//		for the list of Bombclass
	////////////////////////////////////////////////
	void displayBombs(RenderWindow &win)
	{
		list<Bombclass>::iterator iter;

		for (iter = bomblist.begin(); iter != bomblist.end(); iter++)
		{
			iter->displayBomb(win);
		}
	}


};