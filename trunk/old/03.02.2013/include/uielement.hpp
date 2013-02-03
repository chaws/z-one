/**
 *@file screen.hpp
 *@date 14/01/2013
 *@author Charles Oliveira
 *@brief Arquivo com as declarações das classe abstrata pra desenhar interface de usuario
 **/

#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include <SDL/SDL.h>

/**
 *@class UIElement
 *@date 14/1/2013
 *@author Charles Oliveira
 *@brief Classe abstrata representando elementos de interface para usuario
 */
class UIElement
{
public:
	/**
	 *
	 */
	int x;

	/**
	 *
	 */
	int y;

	/**
	 *
	 */
	int w;

	/**
	 *
	 */
	int h;

	/**
	 *
	 */
	SDL_Surface * label;

	/**
	 *
	 */
	SDL_Color * color;

	/**
	 *
	 */
	virtual void draw(SDL_Surface * base) = 0;
};

#endif
