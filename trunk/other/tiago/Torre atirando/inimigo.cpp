#include "inimigo.h"
#include "util.h"
#include <iostream>

using namespace std;

#define W 40
#define H 40


inimigo::inimigo(int tipo, int x, int y){
	box.x = x; xf=x;
	box.y = y; yf=y;
	box.w = 40;
	box.h = 40;
	isVivo=true;
	
	switch(tipo){
		case CAPITAO:
			image = carregaImagem("pirata_capitao.png");
			xVel = 60;
			yVel = 0;
			pontosDeVida = 20;
			break;
		case SAQUEADOR:
			image = carregaImagem("pirata_saqueador.png");
			xVel = 100;
			yVel = 0;
			pontosDeVida = 10;
			break;
	}


}
//Destrutor
inimigo::~inimigo(){
	SDL_FreeSurface(image);
}

void inimigo::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

void inimigo::move(Uint32 deltaTime){
	xf += xVel * (deltaTime/1000.f);
	box.x = (int) xf;
	if(box.x <= 0)
		xVel = -xVel;
	if(box.x+box.w >= SDL_GetVideoSurface()->clip_rect.w)
		xVel = -xVel;
}

void inimigo::update(Uint32 deltaTime){
	if(pontosDeVida<=0){
		isVivo = false;
	}
		
	move(deltaTime);
}
