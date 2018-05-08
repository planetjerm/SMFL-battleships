/*	Authors:		Jeremy Thomas, Jared Ridlington, William Brighton, Matt Perry, Jason Herning
 *	Filename:		board.hpp
 *	Class :			CS 202
 *	Purpose:		Group Project: BattleShips
 */

#ifndef __BOARD_HPP__
#define __BOARD_HPP__
#include <SFML/Graphics.hpp>

class Board {
public:
	Board();

	void draw(sf::RenderWindow & window);
	int getMouseSquare(sf::RenderWindow & window) const;
private:
	std::vector<sf::RectangleShape> _boardSquares;

	sf::Texture _backgroundImage;
	sf::Sprite _backgroundSprite;
};
#endif
