#include <iostream>
#include "game.hpp"

int main()
{
	Game *game = new Game();
	game->start();
	game->delay(6000);
	delete game;
	
	return 0;
}
