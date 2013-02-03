/**
 *@file map.hpp
 *@date 16/01/2013
 *@author Tiago Pereira
 *@brief Definição de um Map, que consiste em uma fase do jogo.
**/

// #ifndef MAP_HPP
// #define MAP_HPP

// #include <SDL/SDL.h>
// #include "tile.hpp"

// class Map{
// private:
// 	static const WIDTH = 20;
// 	static const HEIGTH = 15;
// 	int id;
// 	Tile tiles[WIDTH*HEIGTH];
	
// public:
// 	void loadMap();
// }

// #endif

#ifndef MAP_H
#define MAP_H

#include <string>
#include "tile.hpp"

using namespace std;

class Map{
	
	static const int HEIGHT;
	static const int WIDTH;

	int cod;
	string name;	
public:
	Tile tiles[300];
};

#endif