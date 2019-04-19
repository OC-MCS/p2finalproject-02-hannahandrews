#pragma once
#include <SFML/Graphics.hpp>
#include "AlienSquad.h"
#include <iostream>
using namespace std;
using namespace sf;

//This is the class that randomly drops 
//a bomb from a random alien
class Bombclass
{
private:
	Sprite bomb;			//this is the sprite for a bomb instance
	Vector2f position;		//this is the position of the bomb instance
public:

	//constructer
	Bombclass(Vector2f pos, Texture &text)
	{

		position = pos;

		bomb.setTexture(text);
		bomb.setPosition(position);
	}

	/////////////////////////////////////////////////
	//moveBomb: This function moves the bomb a set 
	//		amount depending on the level the user is on
	//////////////////////////////////////////////////
	void moveBomb(const int move)
	{
		const float distance = 2.0f * move;

		bomb.move(0, distance);

		position = bomb.getPosition();
	}

	///////////////////////////////////////////////
	//displayBomb: This function displays the bomb
	///////////////////////////////////////////////
	void displayBomb(RenderWindow &win)
	{
		win.draw(bomb);
	}

	//////////////////////////////////////////////
	//testContainsShip: this checks if the bomb
	//			hits the ship
	//////////////////////////////////////////////
	bool testContainsShip(Vector2f shipLoc)
	{
		bool containShip = false;

		if (bomb.getGlobalBounds().contains(shipLoc))
		{
			containShip = true;
		}

		return containShip;
	}
};