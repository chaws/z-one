/**
 *@file sound.hpp
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Arquivo com a classe responsável por controle do audio
 **/

#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL/SDL.h>

using namespace std;

/**
 *@class Sound
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Classe responsável por funcionalidades relacionadas ao controle da placa de som
 */
class Sound
{

public:

	/**
	 *
	 */
	int init();

	/**
	 *
	 */
	void play();

	/**
	 *
	 */
	void playFile(string file);

	/**
	 *
	 */
	void mix(Uint8 * stream, unsigned int len);

};

#endif
