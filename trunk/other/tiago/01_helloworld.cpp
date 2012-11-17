#include "SDL/SDL.h"

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Cria um ponteiro para uma tela
	SDL_Surface* screen;
	
	//Inicializa a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
	
	//Loop do jogo
	bool running = true;
	while(running){
		//Tratando os eventos
		//Estrutura dos eventos onde ficam os eventos
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
			}
		}
		//logica e renderizacao
		
		SDL_Flip(screen);
	}

	SDL_Quit();
	return 0;
}
