#ifndef BOTAO_H
#define BOTAO_H

#include <SDL/SDL.h>
#include "util.h"

#define REFRESH 0
#define KATANA 1
#define NUNCHAKU 2
#define MARIKI 3
#define SHURIKEN 4
#define KUNAI 5
#define BOMBA 6

class botao{
	SDL_Surface* image;
	SDL_Rect box;
	int type;
public:
	botao(int tipo, int x, int y);
	~botao();
	void onClick();
	void show();
	void handleEvents(SDL_Event* event);
	bool clicked(int x, int y);
};

#endif