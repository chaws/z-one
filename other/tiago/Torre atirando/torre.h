#ifndef TORRE_H
#define TORRE_H

#include <SDL/SDL.h>
#include <vector>
#include "inimigo.h"
#include "bala.h"

#define KATANA 1
#define NUNCHAKU 2
#define MARIKI 3
#define SHURIKEN 4
#define KUNAI 5
#define BOMBA 6

using namespace std;

class torre{
	SDL_Surface* image; //imagem da torre
	SDL_Surface* ataque;
	Uint32 cor;
	
	SDL_Rect alcance; //area de percepcao da torre

	float DPS; //tiros por segundo
	float shotSpeed; // velocidade do tiro

	Uint32 comecaAtirar;
	int dano;
	SDL_Rect box;
	bool mouseOver;
	bool atacando;
	inimigo *alvo;
	
	void showAlcance();
	bool isInimigoProximo(SDL_Rect* inimigo);
public:

	// torre(SDL_Surface* img, SDL_Surface* imgAtaque,int x, int y, int w, int h); //Construtor
	torre(int tipo, int x, int y); //Construtor
	~torre(); //Destrutor
	void show();
	void DetectMouseOver(int x, int y); //se o mouse esta sobre ela
	void update(Uint32 deltaTime, vector<inimigo*> *piratas, vector<bala*> *balas);

	void setCor(Uint8 r, Uint8 g, Uint8 b);
};

#endif