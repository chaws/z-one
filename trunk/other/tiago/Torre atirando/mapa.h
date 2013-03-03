#ifndef MAPA_H
#define MAPA_H

#include <SDL/SDL.h>
#include <vector>
#include "util.h"

class mapa{
	static const int HEIGHT;
	static const int WIDTH;

	SDL_Surface* caminho; //tile de caminho
	SDL_Surface* inicio; //tile de nascimento dos inimigos
	SDL_Surface* fim; //tile de destino dos inimigos
	SDL_Surface* pode_por_torre; //tile onde pode colocar torre
	SDL_Surface* n_pode_por_torre; //tile não pode colocar torre

	int cod;
	string name;
	string file;

	vector<tile*> tiles;

public:
	mapa(int tipo);
	~mapa();
	void show();
	void update();
};

#endif