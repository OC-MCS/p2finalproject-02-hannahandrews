#pragma once
#include "AlienSquad.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

//This is the class that detemines what level the user is on
class Level
{
private:
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}

	CircleShape startButton;

public:
	int number;
	Level(int level)
	{
		number = level;
	}

	void drawstartScreen(RenderWindow &win)
	{
		Font font;
		if (!font.loadFromFile("C:\\Windows\\Fonts\\georgia.ttf"))
			die("couldn't load font");
		else
		{
			Text startmessage("Press the button to begin or resume", font, 25);
			startmessage.setPosition(200, 100);
			win.draw(startmessage);

			Text pausemessage("Click anywhere on the screen to pause", font, 25);
			pausemessage.setPosition(200, 400);
			win.draw(pausemessage);

			startButton.setFillColor(Color::Red);
			startButton.setPosition(375, 250);
			startButton.setRadius(50);
			win.draw(startButton);
		}
	}

	bool startSelected(Vector2f mouseLocation)
	{
		bool selected = false;
		if (startButton.getGlobalBounds().contains(mouseLocation))
		{
			selected = true;
		}
		
		return selected;
	}
};