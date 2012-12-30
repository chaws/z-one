#include "game.hpp"

using namespace std;

void Game::start(){
    
	
}

void Game::update_time(){

}

void Game::get_input(){

}

void Game::colision_detect(){

}

void Game::render(){

}

void Game::apply_surface(int x, int y, SDL_Surface* src, SDL_Surface* dest) {
    // Estrutura que irá conter as coordenadas indicado aonde será aplicada a superfície 'src' dentro da superície 'dest'
    SDL_Rect offset;
    
    // Definindo as coordenadas
    offset.x=x;
    offset.y=y;
    
    // Dando o Blit das superfícies
    SDL_BlitSurface( src, NULL, dest, &offset);
}

SDL_Surface* Game::load_image(string img){
    //Inicializa a imagem a se carregada
	SDL_Surface* loadedImage = NULL;
	//Inicializa a imagem otimizada
	SDL_Surface* optimizedImage =  NULL;
	
	//Carrega a imagem
	loadedImage = IMG_Load(img.c_str());
	
	//Se a imagem foi carrega
	if(loadedImage != NULL){
		//Cria a imagem otimizada
        optimizedImage = SDL_DisplayFormat(loadedImage);
        //Libera a imagem antiga da memória
        SDL_FreeSurface(loadedImage);
	}
    
    return optimizedImage;
}

void Game::Game(){
    // Inicializa todos os componentes do SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    // Define a tela do jogo 
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,BPP,SDL_SWSURFACE);
}

void Game::~Game(){
    // Libera a estrutura da tela do jogo
    SDL_FreeSurface(screen);
    // Libera todas as alocações do SDL (desliga)
    SDL_Quit();
}
