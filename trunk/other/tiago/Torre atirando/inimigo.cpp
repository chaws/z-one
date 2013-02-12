#include "inimigo.h"

	 //Construtor
	inimigo::inimigo(SDL_Surface* img, int x, int y, int w, int h, int xvel, int yvel){
		image = img;
		box.x = x;
		box.y = y;
		box.w = w;
		box.h = h;
		xVel = xvel;
		yVel = yVel;
	}
	//Destrutor
	inimigo::~inimigo(){
		SDL_FreeSurface(image);
	}
	
	void inimigo::show(){
		SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
	}

	void inimigo::move(){
		box.x+=xVel;
		box.y+=yVel;
		if(box.x<=0)
			xVel=-xVel;
		if(box.x+box.h>=SDL_GetVideoSurface()->clip_rect.w)
			xVel=-xVel;
	}

	bool inimigo::colisao(SDL_Rect* rect1, SDL_Rect* rect2){

	}
