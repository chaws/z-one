#include "inimigo.h"
#include <iostream>
using namespace std;
	 //Construtor
	inimigo::inimigo(SDL_Surface* img, int x, int y, int w, int h, int xvel, int yvel){
		image = img;
		box.x = x; xf=x;
		box.y = y; yf=y;
		box.w = w;
		box.h = h;
		xVel = xvel;
		yVel = yVel;
		isVivo=true;
		pontosDeVida = 10;	
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
