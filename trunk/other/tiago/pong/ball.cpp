#include "ball.h"

//Construtor
ball::ball(SDL_Surface* img, int x, int y, int w, int h, int xVel, int yVel){
	image=img;
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
	xvel=xVel;
	yvel=yVel;
}

//Destrutor
ball::~ball(){
	SDL_FreeSurface(image);
}


//Mostra a bola na tela
void ball::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

//Movimentação da bola
void ball::move(SDL_Rect* player1, SDL_Rect* player2, Mix_Chunk* effect){
	box.x+=xvel;
	box.y+=yvel;
	if(box.y<=0)
		yvel=-yvel;
	if(box.y+box.h>=SDL_GetVideoSurface()->clip_rect.h)
		yvel=-yvel;
	//checando colisão
	if(collision(&box,player1)){
		Mix_PlayChannel(-1,effect,0);
		if(box.x+3 < player1->x+player1->w)
			yvel=-yvel;
		else
			xvel=-xvel;
	}
		
	if(collision(&box,player2)){
		Mix_PlayChannel(-1,effect,0);
		if(box.x+box.w-3 > player2->x)
			yvel=-yvel;
		else
			xvel=-xvel;	
	}		
}

//Colisão da bola
bool ball::collision(SDL_Rect* rect1, SDL_Rect* rect2){
	if(rect1->y >= rect2->y + rect2->h)
		return 0;
	if(rect1->x >= rect2->x + rect2->w)
		return 0;
	if(rect1->y + rect1->h <= rect2->y)
		return 0;
	if(rect1->x + rect1->w <= rect2->x)
		return 0;
	return 1;

}

//Retorna valor se a bola sair da tela
int ball::isOut(){
	if(box.x<=0)
		return 1;
	if(box.x>=SDL_GetVideoSurface()->clip_rect.w)
		return 2;
}

//Retorna bola pra posição inicial
void ball::setBack(int x, int y, int w, int h, int xVel, int yVel){
	box.x=x;
	box.y=y;
	box.w=w;
	box.h=h;
	xvel=xVel;
	yvel=yVel;
}