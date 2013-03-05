#include <ataque.h>
#include <iostream>

using namespace std;

const int Ataque::WIDTH = 10;
const int Ataque::HEIGHT = 10;

Ataque::Ataque(SDL_Surface * imagem, int x, int y, Inimigo * inimigo)
{
	this->imagem=imagem;
	this->rect->x = x;
	this->rect->y = y;
	this->rect->w = Ataque::WIDTH;
	this->rect->h = Ataque::HEIGHT;
	this->deltaX = 0.2;
	this->deltaY = 0.2;
	this->inimigo = inimigo;
	this->cheguei = false;
}

Ataque::~Ataque()
{
	delete this->rect;
}

int Ataque::detectarColisao()
{
	return 0;
}

int Ataque::fazerLogica()
{
	
	this->rect->x += (int)((this->inimigo->rect->x - this->rect->x) * this->deltaX );//* (deltaTime/1000.f));
	this->rect->y += (int)((this->inimigo->rect->y - this->rect->y) * this->deltaY );//* (deltaTime/1000.f));
	
	
	if((this->rect->x > this->inimigo->rect->x-10 && (this->rect->x) < (this->inimigo->rect->x+10)) && (this->rect->y > this->inimigo->rect->y-10 && this->rect->y < this->inimigo->rect->y+10)) 
	{
		this->cheguei = true;
	}
		
	cout << "Fiz logica(" << this << "), nova posicao = " << this->rect->x << "," << this->rect->y  << endl;	
	return 0;
}

int Ataque::desenhar()
{
	
	SDL_BlitSurface(this->imagem,NULL,SDL_GetVideoSurface(),this->rect);
	cout << "Desenhei mano" << endl;
	return 0;
}
