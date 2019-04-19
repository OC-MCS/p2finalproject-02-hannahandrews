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
	Sprite heart;
	Vector2f position;
public:
	singleLife( Vector2f pos, Texture &text)
	{

		position = pos;

		heart.setTexture(text);
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