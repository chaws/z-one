#include <SDL/SDL.h>
#include <inimigo.h>
#include <iostream>
#include <ambiente.h>

Inimigo::Inimigo(int tipo, int x, int y)
{
	switch(tipo)
	{
		case CAPITAO:
			this->tipo = CAPITAO;
			this->imagem = Ambiente::carregarImagem("pirata_capitao_40_40.png");
			this->rect = new SDL_Rect;
			this->rect->w = 40;			
			this->rect->h = 40;
			this->rect->x = x;
			this->rect->y = y;
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			break;

		case SAQUEADOR:
			this->tipo = SAQUEADOR;
			this->imagem = Ambiente::carregarImagem("pirata_saqueador_40_40.png");			
			this->rect = new SDL_Rect;
			this->rect->w = 40;			
			this->rect->h = 40;
			this->rect->x = x;
			this->rect->y = y;
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			break;

		case CORSARIO:
			this->tipo = CORSARIO;
			this->imagem = Ambiente::carregarImagem("pirata_corsario_40_40.png");
			this->rect = new SDL_Rect;
			this->rect->w = 40;			
			this->rect->h = 40;
			this->rect->x = x;
			this->rect->y = y;
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			break;

		case PERNA_DE_PAU:
			this->tipo = PERNA_DE_PAU;
			this->imagem = Ambiente::carregarImagem("pirata_pernadepau_40_40.png");
			this->rect = new SDL_Rect;
			this->rect->w = 40;			
			this->rect->h = 40;
			this->rect->x = x;
			this->rect->y = y;
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			break;
	}
}

Inimigo::~Inimigo()
{
	delete this->imagem;
}

int Inimigo::desenhar()
{
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
}

