/*	Authors:		Jeremy Thomas, Jared Ridlington, William Brighton, Matt Perry, Jason Herning
 *	Filename:		ship.cpp
 *	Class :			CS 202
 *	Purpose:		Group Project: BattleShips
 */

#include <SFML/Graphics.hpp>

#include "../include/ship.hpp"

#include <stdexcept>

// Constructors
Ship::Ship(int position, int width, int height)
	:_position(position),
	_width(width),
	_height(height)
{
	if ( width != 1 && height != 1 )
	{
		throw std::logic_error("Error in Ship::Ship -- ship does not have a dimension equal to 1.");
	};
	if ( position < 0 || position > 100 )
	{
		throw std::logic_error("Error in Ship::Ship -- Index not in bounds.");
	}

	_ship = sf::RectangleShape{};
	sf::Vector2f rectangleSize(40*width, 40*height);
	auto column = position % 10;
	auto row = (position - column)/ 10;
	sf::Vector2f positionVector{(float) column*40, (float) (row+11)*40};
	_ship.setSize(rectangleSize);
	_ship.setPosition(positionVector);
	_ship.setFillColor(sf::Color{170,170,170,180});
};

// Member Functions
void Ship::draw(sf::RenderWindow & window, bool turn) {
	if (turn)
		window.draw(_ship);
}

int Ship::getWidth() const
{
	return _width;
};

int Ship::getHeight() const
{
	return _height;
};

int Ship::getPosition() const
{
	return _position;
};

void Ship::setWidth(int newWidth)
{
	_width = newWidth;
};

void Ship::setHeight(int newHeight)
{
	_height = newHeight;
};

void Ship::setPosition(int newIndex)
{
	_position = newIndex;
};
