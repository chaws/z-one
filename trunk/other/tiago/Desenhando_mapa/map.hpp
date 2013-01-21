#ifndef MAP_H
#define MAP_H

#include <string>
#include "tile.hpp"

class Map{
	int cod;
	string name;	
	Tile tiles[300];

public:
	Map* loadMap(string map_name);
};

#endif