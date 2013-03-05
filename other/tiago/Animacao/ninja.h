#ifndef NINJA_H
#define NINJA_H

#include <SDL/SDL.h>
#include "util.h"

class ninja{
	SDL_Surface* imagem;
	SDL_Rect box;

	int frame; //define a frame atual do ninja
	SDL_Rect frames[5]; //recorte de todas as frames do ninja

public:
	ninja();
	~ninja();

	void update();
	void show();
};

#endif