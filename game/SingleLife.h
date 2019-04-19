#pragma once
#include <SFML/Graphics.hpp>
#include "AlienSquad.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class singleLife
{
private:
	Texture heartTexture;
	Sprite heart;
	Vector2f position;
public:
	singleLife( Vector2f pos)
	{
		if(!heartTexture.loadFromFile("Heart.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
		else
		position = pos;

		heart.setTexture(heartTexture);
		heart.setPosition(position);
	}

	singleLife()
	{}

	void drawLife( RenderWindow &win)
	{
		win.draw(heart);
	}

	Vector2f getPositoin()
	{
		return position;
	}

};