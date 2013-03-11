#include <vector>
#include <SDL/SDL_mixer.h>
#include <mapa.h>
#include <tela.h>
#include <ambiente.h>
#include <iostream>

using namespace std;

const int Mapa::TILE_WIDTH = 40;
const int Mapa::TILE_HEIGHT = 40;
const int Mapa::NUMERO_TOTAL_TILES = (Tela::WIDTH/Mapa::TILE_WIDTH) * (Tela::HEIGHT/Mapa::TILE_HEIGHT);
const int Mapa::TILES_POR_LINHA = Tela::WIDTH/Mapa::TILE_WIDTH;
PontoTile Mapa::tileSaida;

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

		case SALA_REUNIAO:
			this->tiles = Ambiente::carregarConfiguracaoMapa("showerRoom.map");
			break;
			
		case SALA_ARTES_NEGRAS:
			this->tiles = Ambiente::carregarConfiguracaoMapa("darkmagicRoom.map");
			break;

		case SALA_GUARDA:
			this->tiles = Ambiente::carregarConfiguracaoMapa("meetingRoom.map");
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
	
	int tile_aux;
	for(int i=0;i<5;i++){
		// 0 caminho
		// 1 torre
		// 2 bloqueio
		// 3 saida (objetivos dos inimigos)
		// 4 entrada (por onde os inimigos chegam)
		this->clip[i].x=i*40;
		this->clip[i].y=0;
		this->clip[i].w=40;
		this->clip[i].h=40;
	}

	SDL_Surface* tileset = NULL;
	switch(this->tipo)
	{
		case JARDIM_EXTERNO:
			tileset = Ambiente::carregarImagem("tileset_jardimexterno.png");
			break;
		case SALA_ARTES_NEGRAS:
			tileset = Ambiente::carregarImagem("tileset_artesnegras.png");
			break;
		case SALA_GUARDA:
			tileset = Ambiente::carregarImagem("tileset_guarda.png");
			break;
		case SALA_TREINAMENTO:

		case SALA_REUNIAO:
		
		default:
			tileset = Ambiente::carregarImagem("tileset_default.png");
		break;

	}


	// SDL_Surface * tileNaoUtilizavel = Ambiente::carregarImagem("acid.png");
	// SDL_Surface * tileCaminho 		= Ambiente::carregarImagem("wooden_floor.bmp");
	// SDL_Surface * tileUtilizavel 	= Ambiente::carregarImagem("bricks.png");
	// SDL_Surface * tileEntrada 		= Ambiente::carregarImagem("red_carpet.bmp");
	// SDL_Surface * tileSaida 		= Ambiente::carregarImagem("red_carpet.bmp");
	// SDL_Surface * tileParaBlit 		=  NULL;

	SDL_Rect tileRect = {0, 0, Mapa::TILE_WIDTH, Mapa::TILE_HEIGHT};
	bool achouEntrada = false;
	bool achouSaida = false;
	
	for (int i = 0; i < Mapa::NUMERO_TOTAL_TILES; i++)
	{
		switch(this->tiles->at(i))
		{
			case NAO_UTILIZAVEL:
				// tileParaBlit = tileNaoUtilizavel;
				tile_aux = 2;
				break;

			case CAMINHO:
				// tileParaBlit = tileCaminho;
				tile_aux = 0;

				break;

			case UTILIZAVEL:
				// tileParaBlit = tileUtilizavel;
				tile_aux = 1;

				break;
			
			case ENTRADA:
				if(!achouEntrada)
				{
					this->tileEntrada.x = i % Mapa::TILES_POR_LINHA;
					this->tileEntrada.y = (i / Mapa::TILES_POR_LINHA) + 1;
					achouEntrada = true;
				}
				// tileParaBlit = tileEntrada;
				tile_aux = 4;
				break;
				
			case SAIDA:
				if(!achouSaida)
				{
					Mapa::tileSaida.x = i % Mapa::TILES_POR_LINHA;
					Mapa::tileSaida.y = (i / Mapa::TILES_POR_LINHA);
					achouSaida = true;
				}
				// tileParaBlit = tileSaida;
				tile_aux = 3;
				break;
		}

		tileRect.x = contX * Mapa::TILE_WIDTH;
		tileRect.y = contY * Mapa::TILE_HEIGHT;
		
		SDL_BlitSurface(tileset, &clip[tile_aux], this->imagem, &tileRect);
		// SDL_BlitSurface(tileParaBlit, NULL, this->imagem, &tileRect);

		contX++;
		if(contX == Tela::WIDTH/Mapa::TILE_WIDTH)
		{
			contX = 0;
			contY++;
		}
		
	}

	SDL_FreeSurface(tileset);

	// SDL_FreeSurface(tileNaoUtilizavel);
	// SDL_FreeSurface(tileCaminho);
	// SDL_FreeSurface(tileUtilizavel);
	// SDL_FreeSurface(tileEntrada);
	// SDL_FreeSurface(tileSaida);
}

int Mapa::desenhar()
{
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
	return 0;
}

int Mapa::detectarEvento()
{
	
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
	
	switch(this->tipo)
	{
		case JARDIM_EXTERNO:
			this->tiles = Ambiente::carregarConfiguracaoMapa("externGarden.map");
			this->musicaFundo = Ambiente::carregarMusica("06_Searching.mp3");
			break;

		case SALA_TREINAMENTO:
			this->tiles = Ambiente::carregarConfiguracaoMapa("trainingRoom.map");
			this->musicaFundo = Ambiente::carregarMusica("Jumpshot.mp3");
			break;

		case SALA_BANHO:
			this->tiles = Ambiente::carregarConfiguracaoMapa("showerRoom.map");
			this->musicaFundo = Ambiente::carregarMusica("09_Come_and_Find Me_-_B_mix.mp3");
			break;
			
		case SALA_ARTES_NEGRAS:
			this->tiles = Ambiente::carregarConfiguracaoMapa("darkmagicRoom.map");
			this->musicaFundo = Ambiente::carregarMusica("Digital_Native.mp3");
			break;

		case SALA_GUARDA:
			this->tiles = Ambiente::carregarConfiguracaoMapa("meetingRoom.map");
			this->musicaFundo = Ambiente::carregarMusica("02_HHavok-main.mp3");
			break;
	}
	Mix_VolumeMusic(80);
	Mix_PlayMusic(this->musicaFundo, -1);
}

Mapa::~Mapa()
{
	delete this->imagem;
	delete this->rect;
	delete this->tiles;
	Mix_HaltMusic();
	Mix_FreeMusic(this->musicaFundo);
}
