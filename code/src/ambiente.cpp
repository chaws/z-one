#include <mapa.h>
#include <stdlib.h>
#include <ambiente.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const string Ambiente::CAMINHO_IMG = "media/image/";
const string Ambiente::CAMINHO_MAPAS = "media/maps/";
const string Ambiente::CAMINHO_AUDIO = "media/audio/";
const string Ambiente::CAMINHO_FONT = "media/font/";

SDL_Surface * Ambiente::carregarImagem(string caminho)
{
	caminho = Ambiente::CAMINHO_IMG + caminho;

	SDL_Surface * loadedImage = NULL;
	SDL_Surface * optimizedImage =  NULL;
	loadedImage = IMG_Load(caminho.c_str());

	if(!loadedImage)
	{
		cout << "Erro ao abrir: " << SDL_GetError() << endl;
		return NULL;
	}

    optimizedImage = SDL_DisplayFormat(loadedImage);
    if( optimizedImage != NULL ) 
    { 
    	//Map the color key 
    	Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF );
    	//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent 
    	SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); 
 	}
    
    SDL_FreeSurface(loadedImage);
    
    return optimizedImage;
}

SDL_Surface * Ambiente::carregarFonte(string texto, int tamanhoFonte, string caminhoFonte)
{
	caminhoFonte = Ambiente::CAMINHO_FONT + caminhoFonte;
	TTF_Font * fonte = TTF_OpenFont(caminhoFonte.c_str(), tamanhoFonte);
	SDL_Color colorFont = {50, 50, 50}; // um cinza qualquer, soh pra funfar
	SDL_Surface * retorno = TTF_RenderText_Solid(fonte, texto.c_str(), colorFont);
	if(!retorno)
	{
		cout << "Pala pra carregar fonte: " << SDL_GetError() << endl;
		return NULL;
	}
	return retorno;
}

SDL_Surface * Ambiente::carregarIcone(string caminho)
{
	caminho = Ambiente::CAMINHO_IMG + caminho;

	SDL_Surface * loadedImage = NULL;
	SDL_Surface * optimizedImage =  NULL;
	loadedImage = SDL_LoadBMP(caminho.c_str());

	if(!loadedImage)
	{
		cout << "Erro ao abrir: " << SDL_GetError() << endl;
		return NULL;
	}

    optimizedImage = SDL_DisplayFormat(loadedImage);
    if( optimizedImage != NULL ) 
    { 
    	//Map the color key 
    	Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF );
    	//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent 
    	SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); 
 	}
    
    SDL_FreeSurface(loadedImage);
    
    return optimizedImage;
}


vector<Tile> * Ambiente::carregarConfiguracaoMapa(string caminho)
{
	caminho = Ambiente::CAMINHO_MAPAS + caminho;
	vector<Tile> * vetorCodigosTiles = new vector<Tile>;
  	ifstream arquivo(caminho.c_str()); // ifstream = padrão ios:in
	if (arquivo.is_open())
	{
		string codigoString;
		Tile codigo;
		while (arquivo >> codigoString)
		{
			codigo = (Tile) atoi(codigoString.c_str());
			vetorCodigosTiles->push_back(codigo);
		}
		arquivo.close();
	}
	
	return vetorCodigosTiles;
}
