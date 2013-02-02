#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#ifndef BALL_H
#define BALL_H

class ball{
	//int x, y; //coordenadas da posição // não precisa pois o box tem x e y
	int xvel, yvel; //velocidades de movimento
	SDL_Surface* image; //imagem da bola
	SDL_Rect box; //representa a bola (colisões e tals)
	bool collision(SDL_Rect* rect1, SDL_Rect* rect2);
public:
	ball(SDL_Surface* img, int x, int y, int w, int h, int xVel, int yVel); //Construtor
	~ball(); //destrutor
	void show(); //mostra a bola na tela
	void move(SDL_Rect* player1, SDL_Rect* player2, Mix_Chunk* effect); //mexe de acordo com velocidade
	int isOut();
	void setBack(int x, int y, int w, int h, int xVel, int yVel);
};

#endif