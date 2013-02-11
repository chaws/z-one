#include <vector>

#include <mapa.h>
#include <tela.h>
#include <ambiente.h>
#include <iostream>

using namespace std;

void Mapa::carregarCodigosTiles(vector <Tile> * vetorCodigosTiles)
{
	for (unsigned int i=0; i < vetorCodigosTiles->size(); i++)
	{
		this->tiles[i] = vetorCodigosTiles->at(i);
	}
}

void Mapa::configurarMapa()
{
	switch(this->tipo)
	{
		case JARDIM_EXTERNO:
			this->carregarCodigosTiles(Ambiente::carregarConfiguracaoMapa("externGarden.map"));
			break;

		case SALA_TREINAMENTO:
			this->carregarCodigosTiles(Ambiente::carregarConfiguracaoMapa("trainingRoom.map"));
			break;

		case SALA_BANHO:
			this->carregarCodigosTiles(Ambiente::carregarConfiguracaoMapa("showerRoom.map"));
			break;
	}
}

void Mapa::gerarSuperficieEmBranco()
{
    this->imagem = SDL_CreateRGBSurface(0, Tela::WIDTH, Tela::HEIGHT, Tela::BPP,
                                   NULL, NULL, NULL, NULL);
}

void Mapa::gerarSuperficieMapa()
{
	this->gerarSuperficieEmBranco();

	int contX = 0;
	int contY = 0;
	
	SDL_Surface * tileNaoUtilizavel = Ambiente::carregarImagem("tile2.jpg");
	SDL_Surface * tileCaminho = Ambiente::carregarImagem("wooden_floor.bmp");
	SDL_Surface * tileUtilizavel = Ambiente::carregarImagem("tile1.jpg");
	SDL_Surface * tileEntrada = Ambiente::carregarImagem("red_carpet.bmp");
	SDL_Surface * tileSaida = Ambiente::carregarImagem("red_carpet.bmp");
	SDL_Surface * tileParaBlit =  NULL;

	SDL_Rect tileRect = {0, 0, 40, 40};
	
	for (int i=0; i<300; i++)
	{
		switch(this->tiles[i])
		{
			case NAO_UTILIZAVEL:
				tileParaBlit = tileNaoUtilizavel;
				break;

			case CAMINHO:
				tileParaBlit = tileCaminho;
				break;

			case UTILIZAVEL:
				tileParaBlit = tileUtilizavel;
				break;
			
			case ENTRADA:
				tileParaBlit = tileEntrada;
				break;
				
			case SAIDA:
				tileParaBlit = tileSaida;
				break;
		}

		tileRect.x = contX*40;
		tileRect.y = contY*40;
		
		SDL_BlitSurface(tileParaBlit, NULL, this->imagem, &tileRect);

		contX++;
		if(contX==20)
		{
			contX = 0;
			contY++;
		}
		
	}
	
	SDL_FreeSurface(tileNaoUtilizavel);
	SDL_FreeSurface(tileCaminho);
	SDL_FreeSurface(tileUtilizavel);
	SDL_FreeSurface(tileEntrada);
	SDL_FreeSurface(tileSaida);
}

int Mapa::desenhar()
{
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
}

Mapa::Mapa(TipoMapa tipo)
{
	// Carrega as configuracoes de cada tipo especifico de mapa
	this->tipo = tipo;
	this->rect = new SDL_Rect;
	this->rect->x = 0;
	this->rect->y = 0;
	this->rect->w = Tela::WIDTH;
	this->rect->h = Tela::HEIGHT;
	this->imagem = NULL;

	this->configurarMapa();
	this->gerarSuperficieMapa();
}

Mapa::~Mapa()
{
	
}
