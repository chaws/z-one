/**
 *@file main.cpp
 *@date 10/01/2013
 *@author Matheus Fonseca
 *@brief Arquivo com a função principal, basicamente chama o jogo
 **/

#include <iostream>
#include <game.hpp>
#include <environment.hpp>

int main()
{
	Game game;
	int rc;
	
	// Inicia o jogo e as configuracoes SDL
	rc = game.start();
	if(rc < 0)
	{
		Env::printError(rc);
		exit(-1);
	}

	// Mostra a logo e algumas informações iniciais
	game.showEntry();

	// Entra no principal loop do jogo
	game.mainLoop();

	// Sai do jogo
	game.shutdown();
	
	return 0;
}
