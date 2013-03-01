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
	
	hp_verde.x = x;
	hp_verde.y = y-5;
	hp_verde.w = 40;
	hp_verde.h = 5;

	hp_vermelho.x = x;
	hp_vermelho.y = y-5;
	hp_vermelho.w = 40;
	hp_vermelho.h = 5;

	switch(tipo){
		case CAPITAO:
			image = carregaImagem("img/pirata_capitao.png");
			xVel = 60;
			yVel = 0;
			vida_total = pontosDeVida = 20;
			break;
		case SAQUEADOR:
			image = carregaImagem("img/pirata_saqueador.png");
			xVel = 100;
			yVel = 0;
			vida_total = pontosDeVida = 10;
			break;
	}


}
//Destrutor
inimigo::~inimigo(){
	SDL_FreeSurface(image);
}

void inimigo::show(){
	SDL_FillRect(SDL_GetVideoSurface(),&hp_vermelho,SDL_MapRGB(SDL_GetVideoSurface()->format,0xff,0x00,0x00));
	SDL_FillRect(SDL_GetVideoSurface(),&hp_verde,SDL_MapRGB(SDL_GetVideoSurface()->format,0x00,0xff,0x00));
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

void inimigo::move(Uint32 deltaTime){
	xf += xVel * (deltaTime/1000.f);
	hp_vermelho.x = hp_verde.x = box.x = (int) xf;

	if(box.x <= 0)
		xVel = -xVel;
	if(box.x+box.w >= SDL_GetVideoSurface()->clip_rect.w)
		xVel = -xVel;
}

void inimigo::update(Uint32 deltaTime){
	//calculo tah feio ainda
	hp_verde.w =(int) (40 * ((float)pontosDeVida/(float)vida_total));
		
	if(pontosDeVida<=0){
		isVivo = false;
	}
		
	move(deltaTime);
}
