#include "torre.h"
#include <iostream>
#include "inimigo.h"
#include <vector>
#include "bala.h"
#include "util.h"

#define W 40
#define H 40

using namespace std;

torre::torre(int tipo,int x, int y){
	box.x=x;
	box.y=y;
	box.w=W;
	box.h=H;
	mouseOver = 0;
	alvo = NULL;
	atacando = false;
	comecaAtirar = 0;
	cor = SDL_MapRGB(SDL_GetVideoSurface()->format,0x00,0xff,0x00);

	//Inicializando os dados de cada tipo de torre
	switch(tipo){
		
		case KATANA:
			image=carregaImagem("ninja_katana.png");
			ataque=carregaImagem("katana.png");
			alcance.x = x-(W/2);
			alcance.y = y-(H/2);
			alcance.w = W*2;
			alcance.h = H*2;
			DPS = 1;
			dano = 2;
			break;

		case SHURIKEN:
			image=carregaImagem("ninja_shuriken.png");
			ataque=carregaImagem("shuriken.png");
			alcance.x = x-W;
			alcance.y = y-H;
			alcance.w = W*3;
			alcance.h =H*3;
			DPS = 3;
			dano = 1;
			break;

		case BOMBA:
			image=carregaImagem("ninja_bomba.png");
			ataque=carregaImagem("bomba.png");
			alcance.x = x-W;
			alcance.y = y-H;
			alcance.w = W*3;
			alcance.h = H*3;
			DPS = 1;
			dano = 2;
			break;
	}
}

torre::~torre(){
	SDL_FreeSurface(image);
}

void torre::show(){
	//se o mouse estiver sobre o ninja, desenha o alcance dele
	if(mouseOver)
		showAlcance();

	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

void torre::showAlcance(){
	//cout << "mostrou o alcance." << endl;
	SDL_FillRect(SDL_GetVideoSurface(),&alcance,cor);
	SDL_UpdateRect(SDL_GetVideoSurface(),alcance.x,alcance.y,alcance.w,alcance.h);
}

void torre::update(Uint32 deltaTime, vector<inimigo*> *piratas, vector<bala*> *balas){
	if(!atacando){
		for(int j=0;j<piratas->size();j++){
			if(isInimigoProximo(&piratas->at(j)->box)){
				atacando = true;
				alvo = piratas->at(j);
			}
		}
	}
	else{ //arrumar essa criação de balas, tah alocando uma imagem pra cada bala
		comecaAtirar+=deltaTime;
		if(comecaAtirar > (1000/DPS)){
			comecaAtirar-= 1000/DPS; //regula o numero de ataques por segundo
			balas->push_back(new bala(ataque, box.x+20, box.y+20, 10, 10, 12, 1,alvo->box.x+20,alvo->box.y+20));
			//causa dano no alvo
			alvo->pontosDeVida -= dano;
		}
		//confere se o inimigo ainda esta proximo
		if(!isInimigoProximo(&alvo->box)){
			//se não estiver, para de atacar e perde o alvo
			atacando = false;
			alvo = NULL;
		}
	}
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

// void torre::handleEvents(){
// 	if(event.type == SDL_MOUSEMOTION)
// 		DetectMouseOver(event.motion.x,event.motion.y);
// }

void torre::DetectMouseOver(int x, int y){
	if(x>box.x && x<box.x+box.w && y>box.y && y<box.y+box.h)
		mouseOver = 1;
	else mouseOver = 0;
}

void torre::setCor(Uint8 r, Uint8 g, Uint8 b){
	cor = SDL_MapRGB(SDL_GetVideoSurface()->format,r,g,b);
}