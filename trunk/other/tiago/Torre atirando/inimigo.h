#ifndef INIMIGO_H
#define INIMIGO_H

#include <SDL/SDL.h>

#define CAPITAO 1
#define CORSARIO 2
#define SAQUEADOR 3
#define PERNADEPAU 4

class inimigo{
	SDL_Surface* image; //imagem do inimigo
	
	int xVel;
	int yVel;

	float xf;
	float yf;
	
public:
	bool isVivo;
	SDL_Rect box; //retangulo que representa o inimigo
	int pontosDeVida;
	inimigo(int tipo, int x, int y);
	~inimigo(); //Destrutor
	void show();
	void move(Uint32 deltaTime);
	void update(Uint32 deltaTime);

};

#endif