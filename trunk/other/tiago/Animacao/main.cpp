#include <SDL/SDL.h>
#include <iostream>

int main(){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Cria a tela
	SDL_Surface* screen = SDL_SetVideoMode();
	//Estrutura de capturar eventos
	SDL_Event event;

	//Booleano do jogo
	bool running = true;

	while(running){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		//Lógica

		//Renderização

		//Controle de frames

	}


	SDL_FreeSurface(screen);
	SDL_Quit();

	return 0;
}