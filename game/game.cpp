//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 
#include "MissileSquad.h"
#include "AlienSquad.h"
#include "Level.h"
#include "TotalLives.h"
#include "BombSquad.h"

//============================================================
// Hannah Andrews
//============================================================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen
void moveShip(Sprite& ship)
{
	const float DISTANCE = 5.0;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// left arrow is pressed: move our ship left 5 pixels
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		ship.move(-DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// right arrow is pressed: move our ship right 5 pixels
		ship.move(DISTANCE, 0);
	}
}


int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	Texture shipTexture;
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}

	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite background;
	background.setTexture(starsTexture);
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);

	// create sprite and texture it
	Sprite ship;
	ship.setTexture(shipTexture);


	// initial position of the ship will be approx middle of screen
	float shipX = window.getSize().x /2.0f;
	float shipY = 7*(window.getSize().y) / 8.0f;
	ship.setPosition(shipX, shipY);

	Vector2f shipPosition;
	shipPosition.x = shipX;
	shipPosition.y = shipY;

	//These are my variables 
	totalLives lives(window, 3);				//lives is the lives the user has remaining, initialized at 3
	Level level(1);								//level is the level the user is playing, initialized at 1
	AlienSquad displayedAliens(level.number);	//displayedAliens is the set of aliens currently being displayed
	MissileSquad missiles;						//missiles is the missiles being shot fom the ship
	BombSquad bombsDropped;						//bombsDropped are the bombs being dropped by the aliens

	int frameCount = 0;							//framCount counts the frams that have occurred to determine how
												//often to drop bombs

	int aliensKilled = 0;						//aliensKilled keeps track of how many aliens the user has killed

	bool startClicked = false;

	while (window.isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			else if(event.type == Event::MouseButtonReleased)		//this section of code test if the start button is selected
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				startClicked=level.startSelected(mousePos);
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)				//this section of code tests for is the space bar is pressed
				{
					Vector2f shotfrom;
					shotfrom = ship.getPosition();
					missiles.addToList(shotfrom);
				}
			}
		
		}

		//this code is ran if the user selects to start the game
		if (startClicked == true)
		{
			if (displayedAliens.alienList.empty() == true)
			{
				lives.livesRemaining = 3;
				level.number = level.number + 1;
				if (level.number == 1 || level.number == 2)
				{
					displayedAliens.resetFunc(level.number);
				}
			}
			else
			{
				if (level.number != 0 && frameCount % 60 == 0)
				{
					Vector2f pos = displayedAliens.getRandomAlienLocation();
					bombsDropped.dropBomb(pos);
				}

				if (lives.alienHitShip( displayedAliens, ship.getPosition()) == true)
				{
					displayedAliens.resetFunc(level.number);
					BombSquad bombReset;
					bombsDropped = bombReset;

				}
				else if (bombsDropped.bomblist.empty() == false)
				{
					if (lives.bombHitShip(bombsDropped, ship.getPosition()) == true)
					{
						displayedAliens.resetFunc(level.number);
						BombSquad bombReset;
						bombsDropped = bombReset;
					}
				}


			}
		}
		
		//this segment is ran if the user passes level 1
		if (level.number == 1 && displayedAliens.alienList.empty() == true)
		{
			lives.livesRemaining = 3;
			level.number = level.number + 1;
			displayedAliens.resetFunc(level.number);
		}

		//This tests to see if any missile shot is hitting any alien
		if (!missiles.bullets.empty())
		{
			if (displayedAliens.AlienHitByMissile(missiles.bullets) == true)
			{
				aliensKilled++;
			}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);
		 
		//this is displayed if the user lost the game
		if (lives.livesRemaining != 0)
		{
			if (startClicked == false)
			{
				level.drawstartScreen(window);
			}
			else
			{	//this code is animating the game
				if (displayedAliens.alienList.empty() == false)
				{
					bombsDropped.displayBombs(window);
					lives.drawLives(window);
					moveShip(ship);
					// draw the ship on top of background 
					// (the ship from previous frame was erased when we drew background)
					window.draw(ship);
					displayedAliens.draw(window);
					missiles.draw(window);

					bombsDropped.moveBomb(level.number);
					displayedAliens.move(window, level.number);
					missiles.move(window);
				}
				else
				{
					{
						level.beatGame(window, aliensKilled);
					}
				}
			}
		}
		else 
		{
			level.lostGame(window);
		}

		frameCount++;

		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}

