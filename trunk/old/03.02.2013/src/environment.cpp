/**
 *@file environment.cpp
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Arquivo com a implementação da classe responsável por interações com o ambiente (SO)
 **/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <environment.hpp>
#include <commonTypes.hpp>

using namespace std;

SDL_Surface * Env::loadImage(string img)
{
	// Deve-se fazer um tratamento para verificar a extensão da imagem
	// Inicializa a imagem a se carregada
	SDL_Surface * loadedImage = NULL;
	
	// Inicializa a imagem otimizada
	SDL_Surface * optimizedImage =  NULL;
	
	// Carrega a imagem
	cout << "Abrindo: " << img.c_str() << endl;
	loadedImage = IMG_Load(img.c_str());
	//loadedImage = SDL_LoadBMP(img.c_str());
	
	// Se a imagem foi carregada
	if(!loadedImage)
	{
		cout << "Erro ao abrir: " << SDL_GetError() << endl;
		return NULL;
	}
	cout << "Aberta com sucesso!" << endl;
	// Cria a imagem otimizada
    optimizedImage = SDL_DisplayFormat(loadedImage);
    
    // Libera a imagem antiga da memória
    SDL_FreeSurface(loadedImage);
    
    return optimizedImage;
}

void Env::printError(int er)
{
	switch((Error)er)
	{
		case OK:
			break;
		case OUT_OF_MEMORY:
			cout << "Sem memoria!!!" << endl;
			break;
		default:
			cout << "Erro ["<< er <<"] desconhecido" << endl;
	}
}
