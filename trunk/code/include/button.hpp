/**
 *@file button.hpp
 *@date 14/01/2013
 *@author Charles Oliveira
 *@brief Arquivo com as declarações da classe representativa de um botão
 **/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL/SDL.h>
#include <uielement.hpp>

/**
 *@class Button
 *@date 14/1/2013
 *@author Charles Oliveira
 *@brief Classe que desenha um botão na tela
 */
class Button : public UIElement
{
public:
	/**
	 *
	 */
	void draw(SDL_Surface * base);

	/**
	 *	Construtor
	 */
	Button(int x, int y, int w, int h, SDL_Color * color, SDL_Surface * label = NULL);

	/**
	 *	Destrutor
	 */
	~Button();
};

#endif
