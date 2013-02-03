#ifndef BALA_H
#define BALA_H

#include <SDL/SDL.h>

class bala{
	//SDL_Surface* image;
	SDL_Rect box;
	int xVel;
	int yVel;
	Uint32 color

public:
	bala(int x, int y, int w, int h, int xvel, int yvel);
	void show();
};

#endif