/*	Authors:		Jeremy Thomas, Jared Ridlington, William Brighton, Matt Perry, Jason Herning
 *	Filename:		ship.hpp
 *	Class :			CS 202
 *	Purpose:		Group Project: BattleShips
 */

#ifndef __SHIP_HPP__
#define __SHIP_HPP__

#include <SFML/Graphics.hpp>

class Ship
{
public:
	// Constructors
	Ship(int position, int width, int height);

	// Member Functions
	void draw(sf::RenderWindow & window, bool turn);

	int getWidth() const;
	int getHeight() const;
	int getPosition() const;

	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setPosition(int newPosition);


private:
	int _position;
	int _width;
	int _height;

	sf::RectangleShape _ship;
};






#endif
