#ifndef BALA_H
#define BALA_H

#include <SDL/SDL.h>

class bala{
	SDL_Surface* image;

	int xVel;
	int yVel;

public:
	int alvoX;
	int alvoY;
	SDL_Rect box;
	SDL_Rect* getRect();
	bala(SDL_Surface* img, int x, int y, int w, int h, int xvel, int yvel,int alvox, int alvoy);
	~bala();
	void show();
	void move();
};

#endif