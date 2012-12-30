#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include "bullet.h"
#include "base.h"
class player : public baseclass
{
	SDL_Rect box;
	SDL_Surface* image;
	int xvel,yvel;
	SDL_Rect clips[4];
	double frame;
	bool ground;
	bool jump;
	int health;
	bool moving;
	char direction;
//	bool collision(SDL_Rect*,SDL_Rect*);
	public:
	player(SDL_Surface*);
	~player();
	int getX();
	int getXvel();
	void setXvel(int);
	void show(SDL_Surface*);
	void move(const std::vector<std::vector<int> >&);
	void setJump();
	SDL_Rect* getRect();
	int getHealth();
	void setHealth(int);
	void setDirection(const char dir);
	void setMoving(bool);
	char getDirection();
};
#endif
