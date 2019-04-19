#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

//This class handles one instance of a missile
//called when spacebar is pressed
class Missile
{
private:
	Sprite missileshot;
	Vector2f position;
public:
	Missile(Vector2f &pos)
	{
		Texture missileTexture;
		if (!missileTexture.loadFromFile("missile.png"))
		{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
		}

		position = pos;

		missileshot.setTexture(missileTexture);
		missileshot.setPosition(position);
	}


	void draw(RenderWindow &win)
	{
		win.draw(missileshot);
	}

	void moveMissile(RenderWindow &win)
	{
		const float Distance = 5.0f;

		missileshot.move(0, -Distance);

		position = missileshot.getPosition();
	}

	Vector2f missileLoc()
	{
		return position;
	}
};