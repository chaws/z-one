#include "torre.h"
#include <iostream>

using namespace std;

torre::torre(SDL_Surface* img, int x, int y, int w, int h){
	image=img;
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;

	//Inicializando a area de percepcao da torre
	alcance.x = x-w;
	alcance.y = y-h;
	alcance.w = w*3;
	alcance.h = h*3;
	cor = SDL_MapRGB(SDL_GetVideoSurface()->format,0x00,0xff,0x00);

	mouseOver = 0;
}

torre::~torre(){
	SDL_FreeSurface(image);
}

void torre::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

void torre::showAlcance(){
	//cout << "mostrou o alcance." << endl;
	SDL_FillRect(SDL_GetVideoSurface(),&alcance,cor);
	SDL_UpdateRect(SDL_GetVideoSurface(),alcance.x,alcance.y,alcance.w,alcance.h);
}

bool torre::isInimigoProximo(SDL_Rect* inimigo){
	if(alcance.y >= inimigo->y + inimigo->h)
		return 0;
	if(alcance.x >= inimigo->x + inimigo->w)
		return 0;
	if(alcance.y + alcance.h <= inimigo->y)
		return 0;
	if(alcance.x + alcance.w <= inimigo->x)
		return 0;
	return 1;
}

void torre::DetectMouseOver(int x, int y){
	if(x>box.x && x<box.x+box.w && y>box.y && y<box.y+box.h)
		mouseOver = 1;
	else mouseOver = 0;
}
// void torre::shoot(){
// 	bala tiro(int x, int y, int w, int h, int xvel, int yvel);
// }

void torre::setCor(Uint8 r, Uint8 g, Uint8 b){
	cor = SDL_MapRGB(SDL_GetVideoSurface()->format,r,g,b);
}