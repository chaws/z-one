/**
 *@file environment.hpp
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Arquivo com a classe responsável por interações com o ambiente (SO)
 **/

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SDL/SDL.h>
#include <string>

using namespace std;

/**
 *@class Environment
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Classe responsável por funcionalidades relacionadas ao SO, como leitura de arquivo, etc
 */
class Env
{
// private:

public:
	/**
	 *
	 */
	static SDL_Surface * loadImage(string img);

	/**
	 *
	 */
	static void printError(int er);

	/**
	 * Pensar em mais funções
	 */
	//File * readFile();
	//int writeFile();
};

#endif
