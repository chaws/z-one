#ifndef INIMIGO_H
#define INIMIGO_H

#include <SDL/SDL.h>

class inimigo{
	SDL_Surface* image; //imagem do inimigo
	SDL_Rect box; //retangulo que representa o inimigo

	int xVel;
	int yVel;

	bool colisao(SDL_Rect* rect1, SDL_Rect* rect2);
public:
	inimigo(SDL_Surface* img, int x, int y, int w, int h, int xvel, int yvel); //Construtor
	~inimigo(); //Destrutor
	
	void show();
	void move();
};

#endif