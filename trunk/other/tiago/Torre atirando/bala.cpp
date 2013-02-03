#include "bala.h"

bala::bala(int x, int y, int w, int h, int xvel, int yvel){
	//image=img;
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
	color = SDL_MapRGB(screen->format,0xff,0x00,0x00);
	xVel=xvel;
	yVel=yvel;
}

void bala::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}