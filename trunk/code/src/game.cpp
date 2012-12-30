#include "game.hpp"

using namespace std;

SDL_Surface* Game::load_image(string img){
	//Inicializa a imagem a se carregada
	SDL_Surface* loadedImage = NULL;
	//Inicializa a imagem otimizada
	SDL_Surface* optimizedImage =  NULL;
	
	//Carrega a imagem
	loadedImage = IMG_Load(img.c_str());
	
	//Se a imagem foi carrega
	if(loadedImage != NULL){
		
	}
}

void Game::game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,BPP,SDL_SWSURFACE);
	
}

void Game::start(){
	
	
}
