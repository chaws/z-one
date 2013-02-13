#ifndef INIMIGO_H
#define INIMIGO_H

#include <SDL/SDL.h>

class inimigo{
	SDL_Surface* image; //imagem do inimigo
	
	int xVel;
	int yVel;

	float xf;
	float yf;

	// bool colisao(SDL_Rect* rect1, SDL_Rect* rect2);
public:
	SDL_Rect box; //retangulo que representa o inimigo
	bool isVivo;
	int pontosDeVida;
	inimigo(SDL_Surface* img, int x, int y, int w, int h, int xvel, int yvel); //Construtor
	~inimigo(); //Destrutor
	void show();
	void move(Uint32 deltaTime);

	void update(Uint32 deltaTime);
};

#endif