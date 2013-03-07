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
	
	direcao[0]=1;
	direcao[1]=0;
	hp_verde.x = x;
	hp_verde.y = y-5;
	hp_verde.w = 40;
	hp_verde.h = 5;

	hp_vermelho.x = x;
	hp_vermelho.y = y-5;
	hp_vermelho.w = 40;
	hp_vermelho.h = 5;


	frame = 0.;
	for(int i=0;i<10;i++){
		clip[i].x = i*40;
		clip[i].y = 0;
		clip[i].h = clip[i].w = 40;
	}

	int dir_aux;

	if(direcao[0]){
		dir_aux = -1;
		offset = 0;
	} else{
		dir_aux = 1;
		offset = 5;
	}

	switch(tipo){
		case CAPITAO:
			image = carregaImagem("img/pirata_capitao.png");
			xVel = 100 * dir_aux;
			yVel = 0;
			vida_total = pontosDeVida = 20;
			for(int i=0;i<10;i++){
				clip[i].x = i*45;
				clip[i].y = 0;
				clip[i].h = clip[i].w = 45;
			}
			box.w = 45;
			box.h = 45;
			hp_verde.w = 45;
			hp_vermelho.w = 45;
			break;
		case SAQUEADOR:
			image = carregaImagem("img/pirata_saqueador.png");
			xVel = 100 * dir_aux;
			yVel = 0;
			vida_total = pontosDeVida = 10;
			break;
		
		case PERNADEPAU:
			image = carregaImagem("img/pirata_pernadepau.png");
			xVel = 100 * dir_aux;
			yVel = 0;
			vida_total = pontosDeVida = 10;
			break;

		case CORSARIO:
			image = carregaImagem("img/pirata_corsario.png");
			xVel = 100 * dir_aux;
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
	
	SDL_BlitSurface(image,&clip[(int) (frame + 0.5)+offset],SDL_GetVideoSurface(),&box);
}

void inimigo::move(Uint32 deltaTime){

	xf += xVel * (deltaTime/1000.f);
	hp_vermelho.x = hp_verde.x = box.x = (int) xf;

	if(box.x <= 0){ //andando para a esquerda
		xVel = -xVel;
		direcao[0] = 0; //esquerda
		direcao[1] = 1; //direita
		offset = 5;
	}
	if(box.x+box.w >= SDL_GetVideoSurface()->clip_rect.w){ //andando para a direita
		xVel = -xVel;
		direcao[0] = 1; //esquerda
		direcao[1] = 0; //direita	
		offset = 0;
	}

	frame+=0.2f;
	if(frame>=4)
		frame=0.f;

}

void inimigo::update(Uint32 deltaTime){
	//calculo tah feio ainda
	hp_verde.w =(int) (40 * ((float)pontosDeVida/(float)vida_total));
		
	if(pontosDeVida<=0){
		isVivo = false;
	}
		
	move(deltaTime);
}

void inimigo::mudarFrame(){

}