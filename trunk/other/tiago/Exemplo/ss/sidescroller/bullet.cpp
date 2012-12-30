#include "bullet.h"

bullet::bullet(SDL_Surface* img,int x,int y,int xVel,int yVel)
{
	image=img;
	box.x=x;
	box.y=y;
	box.w=image->clip_rect.w;
	box.h=image->clip_rect.h;
	xvel=xVel;
	yvel=yVel;
}

bullet::~bullet()
{
	SDL_FreeSurface(image);
}

SDL_Rect* bullet::getRect()
{
	return &box;
}

void bullet::move()
{
	box.x+=xvel;
	box.y+=yvel;
}

void bullet::show(SDL_Surface* screen)
{
	SDL_BlitSurface(image,NULL,screen,&box);
}
