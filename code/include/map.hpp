/**
 *@file map.hpp
 *@date 16/01/2013
 *@author Tiago Pereira
 *@brief Definição de um Map, que consiste em uma fase do jogo.
**/

#ifndef MAP_HPP
#define MAP_HPP

#include <SDL/SDL.h>
#include "tile.hpp"

class Map{
private:
	static const WIDTH = 20;
	static const HEIGTH = 15;
	int id;
	Tile tiles[WIDTH*HEIGTH];
	
public:
	void loadMap();
}

#endif