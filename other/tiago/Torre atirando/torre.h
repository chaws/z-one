#ifndef TORRE_H
#define TORRE_H

#include <SDL/SDL.h>

class torre{
	SDL_Surface* image; //imagem da torre
	

	Uint32 cor;
	
	SDL_Rect alcance; //area de percepcao da torre

	float DPS; //tiros por segundo
	float shotSpeed; // velocidade do tiro

	
public:
	SDL_Rect box; //retangulo que representa a torre
	bool mouseOver;

	torre(SDL_Surface* img, int x, int y, int w, int h); //Construtor
	~torre(); //Destrutor
	void show();
	void showAlcance();
	bool isInimigoProximo(SDL_Rect* inimigo);
	void DetectMouseOver(int x, int y); //se o mouse esta sobre ela
	//void shoot(); //em quem atirar

	void setCor(Uint8 r, Uint8 g, Uint8 b);
};

#endif