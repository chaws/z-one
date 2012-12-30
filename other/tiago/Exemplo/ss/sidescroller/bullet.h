#include <SDL/SDL.h>
#include <iostream>
#include <vector>

#ifndef BULLET_H
#define BULLET_H

class bullet{
	SDL_Rect box;
	int xvel,yvel;
	SDL_Surface* image;
	public:
	bullet(SDL_Surface* img,int x,int y,int xVel,int yVel);
	~bullet();
	SDL_Rect* getRect();
	void move();
	void show(SDL_Surface* screen);
};

#endif
