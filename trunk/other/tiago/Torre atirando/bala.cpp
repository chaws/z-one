#include "bala.h"

bala::bala(int x, int y, int w, int h, int xvel, int yvel){
	//image=img;
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
	color = SDL_MapRGB(SDL_GetVideoSurface()->format,0xff,0x00,0x00);
	xVel=xvel;
	yVel=yvel;
}

void bala::show(){
	// //Desenha o retangulo (onde,o que, cor)
	// SDL_FillRect(SDL_GetVideoSurface(),&SDL_GetVideoSurface()->clip_rect,color);
	// SDL_BlitSurface(NULL,SDL_GetVideoSurface(),&box);
}