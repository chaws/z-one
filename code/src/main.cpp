#include <iostream>
#include <game.hpp>
#include <sound.hpp>

int main()
{
	Game * game;
	Sound sound;

	// Inicia o jogo e as configuracoes SDL
	game = new Game;

	// Toca um audio porqueira por enquanto
	sound.playSound("media/audio/translate_tts.wav");

	// Abre a tela
	game->start();



	game->delay(6000);
	delete game;
	
	return 0;
}
