/**
 *@file tile.hpp
 *@date 16/01/2013
 *@author Tiago Pereira
 *@brief Definição de um Tile, elemento gráfico que compõe a tela.
**/

#ifndef TILE_HPP
#define TILE_HPP

#include <SDL/SDL.h>


class Tile{
private:
	SDL_Rect *rect;
	int cod;
	Uint32 color;
	static const int HEIGTH = 40;
	static const int WIDTH = 40;
public:

}

#endif