#ifndef MAPA_H
#define MAPA_H

#include <desenhavel.h>

typedef enum
{
	CAMINHO,
	UTILIZAVEL,
	NAO_UTILIZAVEL
} tile;

class Mapa : Desenhavel
{	
public:
	tile tiles[300];
	
	Mapa();
	~Mapa();	
};

#endif
