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
	estado = ESPERANDO;
	comecaAtirar = 0;
	// atirei=false;
	cor = SDL_MapRGB(SDL_GetVideoSurface()->format,0x00,0xff,0x00);

	//Inicializando os dados de animação (vetor de frames)
	// frames[ESPERANDO][0].x = frames[ESPERANDO][1].x = frames[ESPERANDO][2].x = frames[ESPERANDO][3].x = 0;
	// frames[ESPERANDO][0].y = frames[ESPERANDO][1].y = frames[ESPERANDO][2].y = frames[ESPERANDO][3].y = 0;
	// frames[ESPERANDO][0].w = frames[ESPERANDO][1].w = frames[ESPERANDO][2].w = frames[ESPERANDO][3].w = W;
	// frames[ESPERANDO][0].h = frames[ESPERANDO][1].h = frames[ESPERANDO][2].h = frames[ESPERANDO][3].h = H;

	// frames[ATACANDO][0].x = 0;
	// frames[ATACANDO][1].x = 40;
	// frames[ATACANDO][2].x = 80;
	// frames[ATACANDO][3].x = 120;
	// frames[ATACANDO][0].y = frames[ATACANDO][1].y = frames[ATACANDO][2].y = frames[ATACANDO][3].y = 0;
	// frames[ATACANDO][0].w = frames[ATACANDO][1].w = frames[ATACANDO][2].w = frames[ATACANDO][3].w = W;
	// frames[ATACANDO][0].h = frames[ATACANDO][1].h = frames[ATACANDO][2].h = frames[ATACANDO][3].h = H;

	//Inicializando os dados de cada tipo de torre
	switch(tipo){
		
		case KATANA:
			image=carregaImagem("img/ninja_katana.png");
			ataque=carregaImagem("img/katana.png");
			alcance.x = x-(W/2);
			alcance.y = y-(H/2);
			alcance.w = W*2;
			alcance.h = H*2;
			DPS = 5;
			dano = 2;
			break;

		case SHURIKEN:
			image=carregaImagem("img/ninja_shuriken.png");
			ataque=carregaImagem("img/shuriken.png");
			alcance.x = x-W;
			alcance.y = y-H;
			alcance.w = W*3;
			alcance.h =H*3;
			DPS = 3;
			dano = 1;
			break;

		case BOMBA:
			image=carregaImagem("img/ninja_bomba.png");
			ataque=carregaImagem("img/bomba.png");
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
	SDL_FreeSurface(ataque);
}

void torre::show(){
	//se o mouse estiver sobre o ninja, desenha o alcance dele
	if(mouseOver)
		showAlcance();

	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
	// SDL_BlitSurface(image,&frames[estado][frame],SDL_GetVideoSurface(),&box);
}

void torre::showAlcance(){
	//cout << "mostrou o alcance." << endl;
	SDL_FillRect(SDL_GetVideoSurface(),&alcance,cor);
	SDL_UpdateRect(SDL_GetVideoSurface(),alcance.x,alcance.y,alcance.w,alcance.h);
}

void torre::update(Uint32 deltaTime, vector<inimigo*> *piratas, vector<bala*> *balas){
	if(estado!=ATACANDO){
		for(int j=0;j<piratas->size();j++){
			if(isInimigoProximo(&piratas->at(j)->box)){
				estado = ATACANDO;
				alvo = piratas->at(j);
			}
		}
	}
	//TODO:tem que melhorar essa condicional
	else if(!alvo->isVivo){
		estado = ESPERANDO;
	}
	else{ //arrumar essa criação de balas, tah alocando uma imagem pra cada bala
		comecaAtirar+=deltaTime;
		cout << deltaTime << endl;
		if(comecaAtirar > (1000/DPS)){
			comecaAtirar-= 1000/DPS; //regula o numero de ataques por segundo
			balas->push_back(new bala(ataque, box.x+20, box.y+20, 10, 10, 12, 1,alvo->box.x+20,alvo->box.y+20));
			//causa dano no alvo
			frame = 0;
			atirei = true;
			alvo->pontosDeVida -= dano;
		}
		//controla o ninja realizar um movimento de ataque por vez que atira
		if(atirei){
			frame++;
			if(frame>3){
				frame=0;
				atirei=false;
			}
		}
		//confere se o inimigo ainda esta proximo
		if(!isInimigoProximo(&alvo->box)){
			//se não estiver, para de atacar e perde o alvo
			estado = ESPERANDO;
			alvo = NULL;
			comecaAtirar = 0;
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

void torre::DetectMouseOver(int x, int y){
	if(x>box.x && x<box.x+box.w && y>box.y && y<box.y+box.h)
		mouseOver = 1;
	else mouseOver = 0;
}

void torre::setCor(Uint8 r, Uint8 g, Uint8 b){
	cor = SDL_MapRGB(SDL_GetVideoSurface()->format,r,g,b);
}
