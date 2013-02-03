#ifndef TORRE_H
#define TORRE_H

#include <SDL/SDL.h>

class torre{
	SDL_Surface* image; //imagem da torre
	SDL_Rect box; //retangulo que representa a torre

	float DPS; //tiros por segundo
	float shotSpeed; // velocidade do tiro
public:
	torre(SDL_Surface* img, int x, int y, int w, int h); //Construtor
	~torre(); //Destrutor
	void show();
	void shot(); //em quem atirar
};

#endif