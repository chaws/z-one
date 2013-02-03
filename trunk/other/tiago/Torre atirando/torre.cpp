#include "torre.h"

torre::torre(SDL_Surface* img, int x, int y, int w, int h){
	image=img;
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
}

torre::~torre(){
	SDL_FreeSurface(image);
}

void torre::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}