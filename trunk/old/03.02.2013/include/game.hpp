/**
 *@file game.hpp
 *@date 10/01/2013
 *@author Matheus Fonseca
 *@brief O arquivo contém a declaração da classe Game
 **/

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <commonTypes.hpp>
#include <screen.hpp>
#include <event.hpp>
#include <sound.hpp>

using namespace std;

/**
 *@class Game
 *@date 11/17/2013
 *@author Matheus Fonseca
 *@brief Classe responsável por controlar as regras do jogo
 */
class Game{

private:
    /**
	 *	
	 */
    Screen * screen;

    /**
	 *
	 */
    Sound * sound;

	/**
	 *
	 */
    Event * event;

	/**
	 *
	 */
	void processInputs();

	/**
	 *
	 */
	void processColisions();

	/**
	 *
	 */
	void processLogic();

public:

	/**
	 *Representa o estado do jogo
	 */	
	GameState status;
	
	/**
	 *
	 */
	int start();

	/**
	 *
	 */
	void showEntry();
	
	/**
	 *
	 */
	void mainLoop();

	/**
	 *
	 */
	void process();

	/**
	 *
	 */
	void pause();

	/**
	 *
	 */
	void unPause();

	/**
	 *
	 */
	void reboot();

	/**
	 *
	 */
	void shutdown();

	/**
	 *
	 */
	void showMenu();
};

#endif

