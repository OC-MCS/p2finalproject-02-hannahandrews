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
	Sprite bomb;
	Vector2f position;
public:
	Bombclass(Vector2f pos)
	{
		Texture bombTexture;

		if (!bombTexture.loadFromFile("bomb.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}

		position = pos;

		bomb.setTexture(bombTexture);
		bomb.setPosition(position);
	}

	void moveBomb(const int move)
	{
		const int distance = move * 20;
		bomb.move(0, distance);
	}

	void displayBomb(RenderWindow &win)
	{
		win.draw(bomb);
	}
};