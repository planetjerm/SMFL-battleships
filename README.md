# Battleships (CS 202 Group Project)

### Introduction
This project uses [SFML](https://www.sfml-dev.org/) to manage graphics and poll for mouse clicks.


### Steps to compile (Note that this method requires cmake 2.6 or later and SFML 2.4.2 or later to be installed)
1. Create a new folder in the project folder called 'build'.
2. navigate into /build
3. 'cmake ..'
4. 'make'
5. Run the battleship game

### How to play the game
1. Player one will place their ships, followed by player two. The game will prompt how this is done.
2. The game will display which player's turn is available. Click on a grid square on the upper map to attempt to 'shoot' that location.
3. When it is player one's turn, the bottom board will show player one's ships and player two's shot history, and the upper board will show player one's shot history.
