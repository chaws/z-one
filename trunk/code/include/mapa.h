#ifndef MAPA_H
#define MAPA_H

#include <desenhavel.h>

enum Tile
{
	CAMINHO,
	UTILIZAVEL,
	NAO_UTILIZAVEL
};

class Mapa : Desenhavel
{	
public:
	Tile tiles[300];
	
	Mapa();
	~Mapa();	
	int desenhar();
};

#endif
