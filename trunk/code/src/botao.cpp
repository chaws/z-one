#include <botao.h>
#include <ambiente.h>
#include <SDL/SDL.h>
#include <iostream>
#include <util.h>
#include <torre.h>
#include <hud.h>
#include <ambiente.h>

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

Botao::Botao(SDL_Surface * imagem, TipoBotao tipo)
{
	this->rect = new SDL_Rect;
	this->rect->x = -1;
	this->rect->y = -1;

	// Futuramente o width e o height podem ser independentes hehe
	this->rect->w = imagem->w; 
	this->rect->h = imagem->h;
	this->tipo = tipo;

	// switch(this->tipo){
	// 	case SHURIKEN:
	// 		sprintf(preco,"10");
	// 		break;
	// 	case KATANA:
	// 		sprintf(preco,"10");
	// 		break;
	// 	case NUNCHAKU:
	// 		sprintf(preco,"30");
	// 		break;
	// 	case KUNAI:
	// 		sprintf(preco,"30");
	// 		break;
	// 	case MARIKI:
	// 		sprintf(preco,"50");
	// 		break;
	// 	case BOMBA:
	// 		sprintf(preco,"50");
	// 		break;
	// }

	// this->texto_preco = Ambiente::carregarTexto(preco);

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

bool Botao::estaHabilitado()
{
	bool estaHabilitado = false;
	
	switch (this->tipo)
	{
		case BOTAO_SHURIKEN:
			if (Hud::pontosXP >= PRECO_SHURIKEN)
				estaHabilitado = true;
			
			break;
		case BOTAO_KATANA:
			if (Hud::pontosXP >= PRECO_KATANA)
				estaHabilitado = true;
			
			break;
		case BOTAO_NUNCHAKU:
			if (Hud::pontosXP >= PRECO_NUNCHAKU)
				estaHabilitado = true;
			
			break;
		case BOTAO_MARIKI:
			if (Hud::pontosXP >= PRECO_MARIKI)
				estaHabilitado = true;
			
			break;
		case BOTAO_KUNAI:
			if (Hud::pontosXP >= PRECO_KUNAI)
				estaHabilitado = true;
			
			break;
		case BOTAO_BOMBA:
			if (Hud::pontosXP >= PRECO_BOMBA)
				estaHabilitado = true;
			
			break;
		default:
			estaHabilitado =  true;
	}
	
	return estaHabilitado;
}

int Botao::desenhar()
{
	int alpha =  255;
	
	if (!estaHabilitado())
		alpha = 120;
		
	SDL_SetAlpha(this->imagem, SDL_SRCALPHA, alpha);
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);	
	
	// SDL_BlitSurface(this->texto_preco,NULL,SDL_GetVideoSurface(),this->rect);
	return 0;
}

int Botao::detectarEvento()
{
	static bool estaPausado =  false;
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
				if (this->tipo == BOTAO_PAUSE)
				{
					if(Util::estadoInterno != PAUSADO)
						Util::estadoInterno = PAUSADO;
					else
						Util::estadoInterno = OBSERVANDO;
				}	
				else {
					bool podeComprar = false;
					switch (this->tipo)
					{
						case BOTAO_SHURIKEN:
							if (Hud::pontosXP >= PRECO_SHURIKEN){
								podeComprar = true;
							}
							
							break;
						case BOTAO_KATANA:
							if (Hud::pontosXP >= PRECO_KATANA){
								podeComprar = true;
							}
							
							break;
						case BOTAO_NUNCHAKU:
							if (Hud::pontosXP >= PRECO_NUNCHAKU){
								podeComprar = true;
							}
							
							break;
						case BOTAO_MARIKI:
							if (Hud::pontosXP >= PRECO_MARIKI){
								podeComprar = true;
							}
							
							break;
						case BOTAO_KUNAI:
							if (Hud::pontosXP >= PRECO_KUNAI){
								podeComprar = true;
							}
							
							break;
						case BOTAO_BOMBA:
							if (Hud::pontosXP >= PRECO_BOMBA){
								podeComprar = true;
							}
							
							break;
					}
					if (podeComprar)
					{
						Util::estadoInterno = COMPRANDO;
						Util::torreCompra = (TipoTorre) this->tipo;
						Util::imagemCompra.configurarImagem((TipoTorre) this->tipo);
					} 
				}
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
