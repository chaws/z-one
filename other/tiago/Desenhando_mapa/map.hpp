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