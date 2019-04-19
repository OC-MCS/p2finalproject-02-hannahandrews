#pragma once

//This class should account for a single instance 
//of an alien
class Alien
{
private:
	Sprite alien;
	Vector2f location;
public:	
	
	Alien(Texture &texture, Vector2f &loc)
	{
		alien.setTexture(texture);
		location = loc;
		alien.setPosition(loc);
	}

	Alien()
	{}

	void draw(RenderWindow &win)
	{
		win.draw(alien);
	}

	void move(RenderWindow &win, int levelnumber)
	{
		const float dist = .15 * levelnumber;

		alien.move(0, dist);

		location = alien.getPosition();
	}



	bool testAlienHit(Vector2f missileLoc)
	{
		bool contains = false;

		if (alien.getGlobalBounds().contains(missileLoc))
		{
			contains = true;
		}

		return contains;
	}

	Vector2f alienLocation()
	{
		return location;
	}
};
