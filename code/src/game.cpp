/**
 *@file game.cpp
 *@date 4/01/2013
 *@author Matheus Fonseca
 *@brief Arquivo com as a implementação do controle lógico do jogo
 **/

#include <SDL/SDL.h>
#include <iostream>
#include <game.hpp>
#include <commonTypes.hpp>
#include <environment.hpp>
#include <screen.hpp>
#include <event.hpp>
#include <sound.hpp>
#include <string>

using namespace std;

/**
 *	Inicia o jogo
 */
int Game::start()
{
	int rc = OK;

	// Inicia toda a galera
	screen = new Screen;
	event = new Event;
	sound = new Sound;

	//TODO: perguntar pro edson se compensa validar alocação de objeto

	// Inicia tela, captura de input e placa de som
	this->screen->init();
	this->event->init();
	this->sound->init();

	// Verifica se tudo ocorreu bem
	// if()
	
	// Carrega os mapas, ou os menus, chama os botoes, toca musica, controla a lógica do jogo
	// Se tudo ocorrer bem, retorna ok
	return rc;
}

/**
 *	Introdução do jogo
 */
void Game::showEntry()
{
    // Carrega a logo da equipe na tela (não funciona no 'make install'!)
    SDL_Surface * logo = Env::loadImage("media/image/z_one_logo_800_600.png");
    //SDL_Surface * logo = load_image("media/image/exemplo.bmp");
    
    // Joga na tela e mostra pro usuario
    this->screen->applySurface(0, 0, logo);
	this->screen->render();

	// Espera uns 3 segundos
	SDL_Delay(3000);
	
	// Libera a logo, e pela lógica entra no menu principal do jogo
	SDL_FreeSurface(logo);
}

void Game::mainLoop()
{
	this->showMenu();


	while(this->status != ENDING)
	{
		// Chama o inicio do controlador de FPS
		this->screen->controlBFPS();

		// Lê os inputs
		this->event->getInput();

		// Faz a lógica do jogo, atualizando a tela logicamente
		this->process();

		// Renderiza
		this->screen->render();

		// Toca o som, joga dados na PCM
		this->sound->play();

		// Chama a segunda parte do controlador de FPS
		this->screen->controlBFPS();
	}
}

/**
 *
 */
void Game::process()
{
	this->processInputs();
	this->processColisions();
	this->processLogic();
}

/**
 *
 */
void Game::processInputs()
{
	// Processa os eventos/inputs
	Evt * e;
	while((e = this->event->next()))
	{
		cout << "Evento capturado" << endl;
		if (e->type == QUIT)
		{
			cout << "QUIT!!!" << endl;
			// Pergunta se deseja mesmo sair
			this->status = ENDING;
		}
	}
}

/**
 *
 */
void Game::processColisions()
{

}

/**
 *
 */
void Game::processLogic()
{

}

/**
 *	Função chamada quando é detectado um evento que a tela do jogo perde o foco, então espera até a volta do jogador
 */
void Game::pause()
{

}

/**
 *	Quando o jogador clica em "continue"
 */
void Game::unPause()
{

}

/**
 *	Não sei se aplica ao nosso caso, mas caso o jogador queira reiniciar o jogo, a implementação vem aqui
 */
void Game::reboot()
{

}

/**
 *	Ops, o jogador clicou em fechar, ou veio killall do OS
 *	Tratar sinal!!!
 */
void Game::shutdown()
{
	// Desaloca tudo o que o SDL alocou
	this->screen->destroy();

    // Grava o arquivo com o avanço do jogador, salva os mapas, salva o estado do jogo
}

/**
 *	Apresenta o menu inicial
 */
void Game::showMenu()
{
	this->screen->mainMenu();
}
