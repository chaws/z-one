#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include "base.h"
#ifndef ENEMY_H
#define ENEMY_H

class enemy : public baseclass{
	SDL_Rect box;
	double xvel,yvel;
	SDL_Surface* image;
	int attack;
	bool ground;
	SDL_Rect clips[2];
	double frame;
	public:
	enemy(SDL_Surface* img,int x,int y,int xvel,int yvel);
	~enemy();
	SDL_Rect* getRect();
	void move(std::vector<std::vector<int> >&);
	void show(SDL_Surface*);
	double getXvel();
	void setXvel(double);
};

#endif
