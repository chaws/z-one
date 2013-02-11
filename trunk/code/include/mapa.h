#ifndef MAPA_H
#define MAPA_H

#include <desenhavel.h>

enum Tile
{
	CAMINHO,
	UTILIZAVEL,
	NAO_UTILIZAVEL
};

enum TipoMapa
{
	JARDIM_EXTERNO,
	SALA_BANHO,
	SALA_TREINAMENTO
};

class Mapa : Desenhavel
{	
private:
	TipoMapa tipo;
	void configurarMapa();

public:
	Tile tiles[300];
	
	Mapa(TipoMapa tipo);
	~Mapa();	
	int desenhar();
};

#endif
