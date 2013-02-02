#include "paddle.h"

//Construtor
paddle::paddle(SDL_Surface* img, int x, int y, int w, int h, int yVel){
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
	image=img;
	yvel=yVel;
	point=0;
}

paddle::~paddle(){
	SDL_FreeSurface(image);
}

void paddle::moveUp(){
	if(box.y>0)
		box.y-=yvel;
}

void paddle::moveDown(){
	if(box.y+box.h<SDL_GetVideoSurface()->clip_rect.h)
		box.y+=yvel;
}

//Mostra a bola na tela
void paddle::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

//getRect
SDL_Rect* paddle::getRect(){
	return &box;
}

//aumenta pontos
void paddle::incpoint(){
	point++;
}

//Reinicia os pedais
void paddle::setBack(int x, int y, int w, int h, int yVel){
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
	yvel=yVel;
}

//Retorna o numero de pontos
int paddle::getPoints(){
	return point;
}