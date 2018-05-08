/*  Authors:        Jeremy Thomas, Jared Ridlington, William Brighton, Matt Perry, Jason Herning
 *  Filename:       board.cpp
 *  Class :         CS 202
 *  Purpose:        Group Project: BattleShips
 */

#include "../include/board.hpp"

Board::Board()
{
    // Load the background texture.
    if ( !_backgroundImage.loadFromFile("../sprites/water.png") )
    {
        throw std::runtime_error("Failed to load _backgroundImage in Board::Board.");
    }
    _backgroundImage.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundImage);
    _backgroundSprite.scale(sf::Vector2f(1.5f, 1.5f));

    // Build the grid
    sf::Vector2f rectangleSize(40, 40);
    const float outlineThickness = 2;

    _boardSquares = std::vector<sf::RectangleShape>{200};

    for (auto index = 0; index < _boardSquares.size(); ++index)
    {
        auto column = index % 10;
        auto row = (index - column)/ 10;

        // Shift the second board one row down
        if ( row >= 10 ) row += 1;

        sf::Vector2f position{(float) column*40, (float) row*40};

        _boardSquares[index].setSize(rectangleSize);
        _boardSquares[index].setPosition(position);
        _boardSquares[index].setFillColor(sf::Color::Transparent);
        _boardSquares[index].setOutlineColor(sf::Color::White);
        _boardSquares[index].setOutlineThickness(outlineThickness);
    }
};

void Board::draw(sf::RenderWindow & window)
{
    // Draw background
    window.draw(_backgroundSprite);

    // Draw squares
    for (auto temp : _boardSquares)
    {
        window.draw(temp);
    }
};

// Returns -1 on fail otherwise returns the index of the square the mouse is over
int Board::getMouseSquare(sf::RenderWindow & window) const
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    // Local positions less than

    auto column = localPosition.x / 40;
    auto row = localPosition.y / 40;

    if ( column < 0 || column >= 10 || row < 0 || row >= 21 || row == 10 )
    {
        // invalid coordinates and the *raw* row 10 is empty because the second board is shifted down
        return -1;
    }
    else if ( row > 10 )
    {
        // Second board is shifted down by one row
        return (row - 1) * 10 + column;
    }
    else
    {
        return row * 10 + column;
    }
};
