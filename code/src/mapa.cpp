#include <vector>

#include <mapa.h>
#include <tela.h>
#include <ambiente.h>
#include <iostream>

using namespace std;

const int Mapa::TILE_WIDTH = 40;
const int Mapa::TILE_HEIGHT = 40;
const int Mapa::NUMERO_TOTAL_TILES = (Tela::WIDTH/Mapa::TILE_WIDTH) * (Tela::HEIGHT/Mapa::TILE_HEIGHT);
const int Mapa::TILES_POR_LINHA = Tela::WIDTH/Mapa::TILE_WIDTH;

void Mapa::configurarMapa()
{
	switch(this->tipo)
	{
		case JARDIM_EXTERNO:
			this->tiles = Ambiente::carregarConfiguracaoMapa("externGarden.map");
			break;

		case SALA_TREINAMENTO:
			this->tiles = Ambiente::carregarConfiguracaoMapa("trainingRoom.map");
			break;

		case SALA_BANHO:
			this->tiles = Ambiente::carregarConfiguracaoMapa("showerRoom.map");
			break;
	}
}

void Mapa::gerarSuperficieEmBranco()
{
    this->imagem = SDL_CreateRGBSurface(0, Tela::WIDTH, Tela::HEIGHT, Tela::BPP,
                                   0, 0, 0, 0);
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

	SDL_Rect tileRect = {0, 0, Mapa::TILE_WIDTH, Mapa::TILE_HEIGHT};
	bool achouEntrada = false;
	bool achouSaida = false;
	
	for (int i = 0; i < Mapa::NUMERO_TOTAL_TILES; i++)
	{
		switch(this->tiles->at(i))
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
				if(!achouEntrada)
				{
					this->tileEntrada.x = i % Mapa::TILES_POR_LINHA;
					this->tileEntrada.y = (i / Mapa::TILES_POR_LINHA) + 1;
					achouEntrada = true;
				}
				tileParaBlit = tileEntrada;
				break;
				
			case SAIDA:
				if(!achouSaida)
				{
					this->tileSaida.x = i % Mapa::TILES_POR_LINHA;
					this->tileSaida.y = (i / Mapa::TILES_POR_LINHA);
					achouSaida = true;
				}
				tileParaBlit = tileSaida;
				break;
		}

		tileRect.x = contX * Mapa::TILE_WIDTH;
		tileRect.y = contY * Mapa::TILE_HEIGHT;
		
		SDL_BlitSurface(tileParaBlit, NULL, this->imagem, &tileRect);

		contX++;
		if(contX == Tela::WIDTH/Mapa::TILE_WIDTH)
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
	return 0;
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
	delete this->imagem;
	delete this->rect;
	delete this->tiles;
}
