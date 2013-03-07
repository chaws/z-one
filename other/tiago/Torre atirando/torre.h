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

#define ESTADOS 2 //quantidade de estados que um ninja pode ter
#define FRAMES 4

#define ESPERANDO 0
#define ATACANDO 1

using namespace std;

class torre{
	SDL_Surface* image; //imagem da torre
	SDL_Surface* ataque;
	Uint32 cor;
	
	// int frame;
	// SDL_Rect frames[ESTADOS][FRAMES];

	int estado;
	bool atirei;
	SDL_Rect alcance; //area de percepcao da torre

	float DPS; //tiros por segundo
	float shotSpeed; // velocidade do tiro

	Uint32 comecaAtirar;
	int dano;
	SDL_Rect box;
	bool mouseOver;
	int comprado;
	bool atacando;
	inimigo *alvo;
	
	void showAlcance();
	bool isInimigoProximo(SDL_Rect* inimigo);
	void setCor(Uint8 r, Uint8 g, Uint8 b);
public:

	// torre(SDL_Surface* img, SDL_Surface* imgAtaque,int x, int y, int w, int h); //Construtor
	torre(int tipo, int x, int y); //Construtor
	~torre(); //Destrutor
	void show();
	void DetectMouseOver(int x, int y); //se o mouse esta sobre ela
	void update(Uint32 deltaTime, vector<inimigo*> *piratas, vector<bala*> *balas);

};

#endif