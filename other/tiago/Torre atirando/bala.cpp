#include "bala.h"
#include <iostream>
using namespace std;

bala::bala(SDL_Surface* img, int x, int y, int w, int h, int xvel, int yvel,int alvox, int alvoy){
	image=img;
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
	xVel=xvel;
	yVel=yvel;
	alvoX = alvox;
	alvoY = alvoy;
}

bala::~bala(){
	SDL_FreeSurface(image);
}

void bala::move()
{	
	// float diffX = enemy.position.x - position.x;
	// float diffY = enemy.position.y - position.y;

	// velocity.x = diffX;
	// velocity.y = diffY;

	// position.add(velocity.x * deltaTime, velocity.y * deltaTime);
	
	box.x+= (alvoX-box.x)/2;
	box.y+= (alvoY-box.y)/2;
	//box.y = (a * box.x) + b;
}

void bala::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

SDL_Rect* bala::getRect(){
	return &box;
}