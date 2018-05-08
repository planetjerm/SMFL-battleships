/*	Authors:		Jeremy Thomas, Jared Ridlington, William Brighton, Matt Perry, Jason Herning
*	Filename:		main.cpp
*	Class :			CS 202
*	Purpose:		Group Project: BattleShips
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <../include/board.hpp>
#include <../include/playerboard.hpp>
#include <../include/ship.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>

void placeShips(std::vector<Ship> & ships, sf::RenderWindow & window, sf::Sprite instructions, Board & board, PlayerBoard& playerBoard) {
	std::vector<int> shipPlacement{ 2,3,3,4,5 };

	sf::Texture carrierText, battleshipText, cruiserText, submarineText, destroyerText, continueTwo;
	if (!carrierText.loadFromFile("../sprites/carrier.png")
		|| !battleshipText.loadFromFile("../sprites/battleship.png")
		|| !cruiserText.loadFromFile("../sprites/cruiser.png")
		|| !submarineText.loadFromFile("../sprites/submarine.png")
		|| !destroyerText.loadFromFile("../sprites/destroyer.png")
		|| !continueTwo.loadFromFile("../sprites/continue2.png"))
	{
		throw std::runtime_error("Failed to load instruction sprites.");
	}
	sf::Sprite continueDirectionsTwo{ continueTwo };
	continueDirectionsTwo.setPosition(0, 400);
	std::vector<sf::Sprite> sprites;
	sprites.push_back(sf::Sprite(destroyerText));
	sprites.push_back(sf::Sprite(submarineText));
	sprites.push_back(sf::Sprite(cruiserText));
	sprites.push_back(sf::Sprite(battleshipText));
	sprites.push_back(sf::Sprite(carrierText));

	for (sf::Sprite &temp : sprites)
	{
		temp.setPosition(temp.getPosition().x + 0, temp.getPosition().y + 180);
	}

	while (window.isOpen() && !shipPlacement.empty())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Close window: exit
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				auto index = board.getMouseSquare(window);
				if (index >= 100 && index < 200)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						// Vertical ship placement
						Ship temp{ index - 100, 1, shipPlacement.back() };
						if (playerBoard.addShip(temp))
						{
							ships.push_back(temp);
							shipPlacement.pop_back();
							sprites.pop_back();
						}
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						// Horizontal ship placement
						Ship temp{ index - 100, shipPlacement.back(), 1 };
						if (playerBoard.addShip(temp))
						{
							ships.push_back(temp);
							shipPlacement.pop_back();
							sprites.pop_back();
						}
					}
				}
			}
		}
		window.clear();
		board.draw(window);
		window.draw(instructions);
		if (!sprites.empty()) window.draw(sprites.back());
		for (auto ship : ships)
		{
			ship.draw(window, true);
		}
		window.display();
	}

	while (true) {
		board.draw(window);
		window.draw(continueDirectionsTwo);
		if (!sprites.empty()) window.draw(sprites.back());
		for (auto ship : ships)
		{
			ship.draw(window, true);
		}
		window.display();
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			break;
		}
	}

}


int main()
{
	sf::RenderWindow window{ sf::VideoMode{ 400,840 }, "BATTLESHIPS!!", sf::Style::Titlebar | sf::Style::Close };
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
	if (!music.openFromFile("../sounds/ocean.ogg")) {
		throw std::runtime_error("Error loading music file ocean");
	}
	music.play();
	music.setVolume(50);
	music.setLoop(true);
	sf::Texture bannerOne, bannerTwo, instructions1, instructions2, continueOne,startBanner;
	if (!bannerOne.loadFromFile("../sprites/player_one.png")
		|| !bannerTwo.loadFromFile("../sprites/player_two.png")
		|| !instructions1.loadFromFile("../sprites/player1instructions.png")
		|| !instructions2.loadFromFile("../sprites/player2instructions.png")
		|| !continueOne.loadFromFile("../sprites/continue1.png")
		|| !startBanner.loadFromFile("../sprites/BattleShipLogo.png"))
	{
		throw std::runtime_error("Error in main -- failed to load sprites.");
	}
	sf::Sprite gamelogo{ startBanner };
	gamelogo.setPosition(0, 0);
	sf::Sprite continueDirections{ continueOne };
	continueDirections.setPosition(0, 600);
	sf::Sprite playerOneBanner{ bannerOne };
	playerOneBanner.setPosition(0, 400);
	sf::Sprite playerTwoBanner{ bannerTwo };
	playerTwoBanner.setPosition(0, 400);
	sf::Sprite player1instructions{ instructions1 };
	sf::Sprite player2instructions{ instructions2 };

	sf::Texture victoryTexture;
	sf::Sprite victoryBanner;
	Board board{};
	PlayerBoard player1{};
	PlayerBoard player2{};

	std::vector<Ship> player1Ships;
	std::vector<Ship> player2Ships;
	if (!buffer.loadFromFile("../sounds/hit.wav")) {
		throw std::runtime_error("Error loading sound file");
	}
	sound.setBuffer(buffer);
	sound.play();
	while (true) {

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			break;
		}
		else {
			window.draw(gamelogo);
			window.draw(continueDirections);
			window.display();
		}
	}

	window.clear();

	while (true) {
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			placeShips(player1Ships, window, player1instructions, board, player1);
			break;
		}
		else {
			window.clear();
			window.draw(playerOneBanner);
			window.draw(continueDirections);
			window.display();
		}
	}
	window.clear();

	while (true) {
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			placeShips(player2Ships, window, player2instructions, board, player2);
			break;
		}
		else {
			window.clear();
			window.draw(playerTwoBanner);
			window.draw(continueDirections);
			window.display();
		}
	}
	window.clear();
	while (true) {
		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			break;
		}
		else {
			window.clear();
			window.draw(playerOneBanner);
			window.draw(continueDirections);
			window.display();
		}
	}
	bool player1_turn = true;
	int victory = 0;
	bool victorySprite = false;

	while (window.isOpen())
	{
		if (victory == 0)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Close window and exit
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					auto index = board.getMouseSquare(window);

					if (index >= 0 && index < 100)
					{
						if (player1_turn)
						{
							if (!player2.getSquare(index).first)
							{

								player2.setSquare(index, std::make_pair(true, player2.getSquare(index).second));
								victory = player2.victoryConditions();
								board.draw(window);
								for (auto ship : player1Ships)
								{
									ship.draw(window, player1_turn);
								}
								for (auto ship : player2Ships)
								{
									ship.draw(window, !player1_turn);
								}
								player1.draw(window, player1_turn);
								player2.draw(window, !player1_turn);

								if (player1_turn)
								{
									window.draw(playerOneBanner);
								}
								else
								{
									window.draw(playerTwoBanner);
								}
								window.display();
								for (int i = 0; i < 100000000; i++) {

								}
								while (true) {
									if (window.pollEvent(event)) {
										if (event.type == sf::Event::Closed) {
											window.close();
										}
									}
									else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
										player1_turn = false;
										break;
									}
									else {
										window.clear();
										window.draw(playerTwoBanner);
										window.draw(continueDirections);
										window.display();
									}
								}
							}

						}
						else
						{
							if (!player1.getSquare(index).first)
							{
								player1.setSquare(index, std::make_pair(true, player1.getSquare(index).second));
								victory = 2 * player1.victoryConditions();
								board.draw(window);
								for (auto ship : player1Ships)
								{
									ship.draw(window, player1_turn);
								}
								for (auto ship : player2Ships)
								{
									ship.draw(window, !player1_turn);
								}
								player1.draw(window, player1_turn);
								player2.draw(window, !player1_turn);

								if (player1_turn)
								{
									window.draw(playerOneBanner);
								}
								else
								{
									window.draw(playerTwoBanner);
								}
								window.display();
								for (int i = 0; i < 100000000; i++) {

								}
								while (true) {
									if (window.pollEvent(event)) {
										if (event.type == sf::Event::Closed) {
											window.close();
										}
									}
									else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
										player1_turn = true;
										break;
									}
									else {
										window.clear();
										window.draw(playerOneBanner);
										window.draw(continueDirections);
										window.display();
									}
								}
							}
						}
					}
				}
			}
			window.clear();
			board.draw(window);
			for (auto ship : player1Ships)
			{
				ship.draw(window, player1_turn);
			}
			for (auto ship : player2Ships)
			{
				ship.draw(window, !player1_turn);
			}
			player1.draw(window, player1_turn);
			player2.draw(window, !player1_turn);

			if (player1_turn)
			{
				window.draw(playerOneBanner);
			}
			else
			{
				window.draw(playerTwoBanner);
			}
			window.display();
		}

		else
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Close window and exit
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (victory == 1 && victorySprite == false)
				{
					if (!victoryTexture.loadFromFile("../sprites/player1wins.png"))
					{
						throw std::runtime_error("Error in main -- failed to load victory sprite.");
					}
					if (!buffer.loadFromFile("../sounds/victory.wav")) {
						throw std::runtime_error("Error loading sound file");
					}
					sound.setBuffer(buffer);
					sound.play();
					victoryBanner.setTexture(victoryTexture);
					victorySprite = true;
				}
				else if (victory == 2 && victorySprite == false)
				{
					if (!victoryTexture.loadFromFile("../sprites/player2wins.png"))
					{
						throw std::runtime_error("Error in main -- failed to load victory sprite.");
					}
					if (!buffer.loadFromFile("../sounds/victory.wav")) {
						throw std::runtime_error("Error loading sound file");
					}
					sound.setBuffer(buffer);
					sound.play();
					victoryBanner.setTexture(victoryTexture);
					victorySprite = true;
				}
				else
				{
					window.clear();
					window.draw(victoryBanner);
					window.display();
				}
			}
		}
	}
	return 0;
}