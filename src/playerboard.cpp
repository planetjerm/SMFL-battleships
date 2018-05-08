/*	Authors:		Jeremy Thomas, Jared Ridlington, William Brighton, Matt Perry, Jason Herning
 *	Filename:		playerboard.cpp
 *	Class :			CS 202
 *	Purpose:		Group Project: BattleShips
 */

#include "../include/playerboard.hpp"
#include "../include/ship.hpp"

#include <SFML/Audio.hpp>

#include <utility>
#include <vector>
#include <stdexcept>

sf::SoundBuffer buffer;
sf::Sound sound;

// Constructors
PlayerBoard::PlayerBoard()
{
	_board = std::vector< std::pair<bool,bool> >{100};
	_shots = std::vector<sf::CircleShape>{_board.size()};

	for (auto index = 0; index < _board.size(); ++index)
	{
		_board[index].first = false; // has been fired at
		_board[index].second = false; // contains ship

		auto column = index % 10;
        auto row = (index - column)/ 10;

        sf::Vector2f position{(float) column*40 + 10, (float) row*40 + 10};

        _shots[index].setRadius(10);
        _shots[index].setPosition(position);
        _shots[index].setFillColor(sf::Color::Transparent);
	}
};

// Member functions
void PlayerBoard::draw(sf::RenderWindow & window, bool turn)
{
	for (auto shot : _shots)
	{
		if ( !turn )
		{
			window.draw(shot);
		}
		else
		{
			shot.setPosition(shot.getPosition().x, shot.getPosition().y + 440);
			window.draw(shot);
			shot.setPosition(shot.getPosition().x, shot.getPosition().y - 440);
		}
	}
};

bool PlayerBoard::addShip(const Ship & newShip)
{
	int index = newShip.getPosition();
	int width = newShip.getWidth();
	int height = newShip.getHeight();

	if ( width > 1 && index%10 + width < 10 )
	{
		// check for intersecting ships
		for (int i = 0; i < width; i++)
		{
			if ( _board[index +i].second ) return false;
		}
		// place ship
		for (int i = 0; i < width; i++)
		{
			_board[index +i].second = true;
		}

		return true;
	}
	else if ( height > 1 && index + (height-1)*10 < 100)
	{
		// check for intersecting ships
		for (int i = 0; i < height; i++)
		{
			if ( _board[index +i*10].second ) return false;
		}
		// place ship
		for (int i = 0; i < height; i++)
		{
			_board[index +i*10].second = true;
		}

		return true;
	}
	else if ( height == 1 && width == 1 )
	{
		throw std::logic_error("Error in PlayerBoard::addShip -- Ship has dimensions 1x1.");
	}
	else
	{
		return false;
	}
};

int PlayerBoard::victoryConditions()
{
	for (auto i:_board)
	{
		if ( i.first == false && i.second == true )
		{
			return 0;
		}
	}
	return 1;
};

std::pair<bool,bool> PlayerBoard::getSquare(int index)
{
	if(index >= 0 && index <= 99)
	{
		return _board[index];
	}
	else
	{
		throw std::logic_error("Error in PlayerBoard::getSquare -- Out of bounds index requested");
	}
};

void PlayerBoard::setSquare(int index, const std::pair<bool,bool> & newSquare)
{


	if(index >= 0 && index <= 99)
	{
		_board[index] = newSquare;

		// If the index has been fired at
		if (newSquare.first) {
			// If the index contains a ship
			if(newSquare.second) {
				if (!buffer.loadFromFile("../sounds/hit.wav")) {
					throw std::runtime_error("Error loading sound file");
				}
				sound.setBuffer(buffer);
				_shots[index].setFillColor(sf::Color::Red);
				sound.play();
				// Is a hit
			} else {
				// Is a miss
				if (!buffer.loadFromFile("../sounds/miss.wav")) {
					throw std::runtime_error("Error loading sound file");
				}
				sound.setBuffer(buffer);
				_shots[index].setFillColor(sf::Color::White);
				sound.play();
				
			}
		}
	}
	else
	{
		throw std::logic_error("Error in PlayerBoard::setSquare -- Out of bounds index requested");
	}
};
