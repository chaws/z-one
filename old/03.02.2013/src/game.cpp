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
    // Coloca a logo na tela, setando a imagem de transparente até quase opaca em 4 segundos - (não funciona no 'make install'!)
    SDL_Surface * logo = Env::loadImage("media/image/z_one_logo_800_600.png");
    int alpha = SDL_ALPHA_TRANSPARENT;
    const int ENTRY_FRAMES = 50;
    
	for (int i=0; i < ENTRY_FRAMES; i++, alpha++) {
        SDL_SetAlpha(logo, SDL_SRCALPHA, alpha);
        this->screen->applySurface(0, 0, logo);
		this->screen->render();
		SDL_Delay(40);
	}
	
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
		this->screen->controlAFPS();
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

/*
Map Game::loadMap(const char * map_name){
	
	Map m;

	fstream reader;
	if (!reader.is_open())
    {
        reader.open(map_name);

        if (!reader)
        {
            cerr << "Failed to open " << reader << endl;
            //exit(EXIT_FAILURE);  //abort program
        }
    }
	
	char aux;

	for(int i = 0;i<300;i++){
		aux = reader.get();
		if(aux==32 || aux==10){
			i--;
		}
			
		else{
			m.tiles[i].code = aux;
		}
	}
	cout << "Mapa carregado com sucesso!\n";
	reader.close();

	return m;
} */