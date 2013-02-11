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
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    this->imagem = SDL_CreateRGBSurface(0, Tela::WIDTH, Tela::HEIGHT, Tela::BPP,
                                   rmask, gmask, bmask, amask);
}

int Mapa::desenhar()
{
	this->gerarSuperficieEmBranco();
	
	int contX = 0;
	int contY = 0;
	
	SDL_Surface * tileImagem = NULL;
	SDL_Rect tileRect = {0, 0, 40, 40};
	
	for (int i=0; i<300; i++)
	{
		switch(this->tiles[i])
		{
			case NAO_UTILIZAVEL:
				tileImagem = Ambiente::carregarImagem("tile2.jpg");
				break;

			case CAMINHO:
				tileImagem = Ambiente::carregarImagem("wooden_floor.bmp");
				break;

			case UTILIZAVEL:
				tileImagem = Ambiente::carregarImagem("tile1.jpg");
				break;
			
			case ENTRADA:
				tileImagem = Ambiente::carregarImagem("red_carpet.bmp");
				break;
				
			case SAIDA:
				tileImagem = Ambiente::carregarImagem("red_carpet.bmp");
				break;

		}
		
		tileRect.x = contX*40;
		tileRect.y = contY*40;
		
		SDL_BlitSurface(tileImagem, NULL, this->imagem, &tileRect);
		
		contX++;
		if(contX==20)
		{
			contX = 0;
			contY++;
		}
	}

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
}

Mapa::~Mapa()
{

}
