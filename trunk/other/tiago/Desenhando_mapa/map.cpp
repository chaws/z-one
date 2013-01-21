#include "map.hpp"
#include <fstream>

Map* Map::loadMap(string map_name){
	Map* map;
	fstream leitor;
	leitor.open(map_name);
	char aux;

	for(i=0;i<(15*20);i++){
		aux = leitor.get();
		if(aux==32 || aux==10){
			i--;
		}
		else{
			map->tiles->code = aux;
		}

	}
	return map;
}