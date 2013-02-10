#include <ambiente.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

using namespace std;

SDL_Surface * Ambiente::carregarImagem(string caminho)
{
	SDL_Surface * loadedImage = NULL;
	SDL_Surface * optimizedImage =  NULL;
	loadedImage = IMG_Load(caminho.c_str());

	if(!loadedImage)
	{
		cout << "Erro ao abrir: " << SDL_GetError() << endl;
		return NULL;
	}

    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    
    return optimizedImage;
}

