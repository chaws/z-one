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
	
	box.x+= (int)((alvoX-box.x)*0.2);
	box.y+= (int)((alvoY-box.y)*0.2);
}

void bala::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

SDL_Rect* bala::getRect(){
	return &box;
}