#pragma once

//This class should account for a single instance 
//of an alien
class Alien
{
private:
	Texture alienTexture;
	Sprite alien;			//this is my sprite value for the alien class
	Vector2f location;		//this is the location of the sprite
public:	
	
	//constructer
	Alien(Texture &texture, Vector2f &loc)
	{
		alienTexture = texture;
		alien.setTexture(alienTexture);
		location = loc;
		alien.setPosition(loc);
	}

	//default constructer
	Alien()
	{}

	/////////////////////////////////////////////
	//draw: This function draws the alien
	/////////////////////////////////////////////
	void draw(RenderWindow &win)
	{
		alien.setTexture(alienTexture);
		win.draw(alien);
	}

	/////////////////////////////////////////////
	//move: This function moves the alien
	/////////////////////////////////////////////
	void move(RenderWindow &win, int levelnumber)
	{
		const float dist = .15 * levelnumber;

		alien.move(0, dist);

		location = alien.getPosition();
	}

	//////////////////////////////////////////////
	//testAlienHit: this code tests if the alien comes
	//		in contact with the missile
	//////////////////////////////////////////////
	bool testAlienHit(Vector2f missileLoc)
	{
		bool contains = false;

		if (alien.getGlobalBounds().contains(missileLoc))
		{
			contains = true;
		}

		return contains;
	}

	//////////////////////////////////////////
	//testContansShip: This code tests to see
	//		if the alien has collided with the 
	//		ship
	//////////////////////////////////////////
	bool testContainsShip(Vector2f shipLoc)
	{
		bool containsShip = false;

		if (alien.getPosition().y >= shipLoc.y)
		{
			containsShip = true;
		}

		return containsShip;
	}

	/////////////////////////////////////////
	//alienLocation: This makes the alien
	//		position avilable to other 
	//		classes while keeping it safe
	/////////////////////////////////////////
	Vector2f alienLocation()
	{
		return location;
	}
};
