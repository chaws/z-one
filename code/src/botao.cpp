#include <botao.h>
#include <ambiente.h>
#include <SDL/SDL.h>
#include <iostream>
#include <util.h>
#include <torre.h>

using namespace std;

Botao::Botao(string rotulo)
{
	this->rect = new SDL_Rect;
	this->rect->x = -1;
	this->rect->y = -1;

	// Futuramente o width e o height podem ser independentes hehe

	this->imagem = Ambiente::carregarTexto(rotulo);

	this->rect->w = imagem->w; 
	this->rect->h = imagem->h;

	this->clicado = false;
}

Botao::Botao(SDL_Surface * imagem)
{
	this->rect = new SDL_Rect;
	this->rect->x = -1;
	this->rect->y = -1;

	// Futuramente o width e o height podem ser independentes hehe
	this->rect->w = imagem->w; 
	this->rect->h = imagem->h;

	this->imagem = imagem;
	this->clicado = false;	
}

Botao::Botao(SDL_Surface * imagem, TipoTorre tipo)
{
	this->rect = new SDL_Rect;
	this->rect->x = -1;
	this->rect->y = -1;

	// Futuramente o width e o height podem ser independentes hehe
	this->rect->w = imagem->w; 
	this->rect->h = imagem->h;
	
	this->tipo = tipo;
	
	this->imagem = imagem;
	this->clicado = false;	
}

Botao::Botao(int x, int y, int w, int h, string rotulo)
{
	this->rect = new SDL_Rect;
	this->rect->x = x;
	this->rect->y = y;

	// duas linhas abaixo soh para tirar warnings
	this->rect->w = w; 
	this->rect->h = h;

	// Futuramente o width e o height podem ser independentes hehe
	this->imagem = Ambiente::carregarTexto(rotulo);
	this->rect->w = imagem->w; 
	this->rect->h = imagem->h;

	this->clicado = false;
}

Botao::Botao(int x, int y, int w, int h, SDL_Surface * imagem)
{
	this->rect = new SDL_Rect;
	this->rect->x = x;
	this->rect->y = y;

	// duas linhas abaixo soh para tirar warnings
	this->rect->w = w; 
	this->rect->h = h;

	// Futuramente o width e o height podem ser independentes hehe
	this->rect->w = imagem->w; 
	this->rect->h = imagem->h;

	this->imagem = imagem;
	this->clicado = false;
}

Botao::~Botao()
{
	//if(this->imagem) delete this->imagem;
	//if(this->rect) 	 delete this->rect;
}

int Botao::desenhar()
{
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
	return 0;
}

int Botao::detectarEvento()
{
	if(Escutavel::evento.type == SDL_MOUSEBUTTONDOWN)
	{
		if(Escutavel::evento.button.button == SDL_BUTTON_LEFT)
		{
			int x = Escutavel::evento.button.x;
			int y = Escutavel::evento.button.y;

			// Verifica se o clique foi em cima desse botao em especifico
			if(this->rect->x <= x && x <= this->rect->x + this->rect->w &&
				this->rect->y <= y && y <= this->rect->y + this->rect->h)
			{
				this->clicado = true;
				Util::estadoInterno = COMPRANDO;
				Util::torreCompra = this->tipo;
				Util::imagemCompra.configurarImagem(this->tipo);
			}
		}
	}
	return 0;
}

bool Botao::foiClicado()
{
	bool temp = this->clicado;
	this->clicado = false;
	return temp;
}
