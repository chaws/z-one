#include "game.hpp"

game::game(){
	screen = SDL_SetVideoMode(SCREEN_HEIGHT,SCREEN_WIDTH, BPP, SDL_SWSURFACE);
	running = true;
}

game::~game(){
	SDL_Quit();
}

void game::render(){

	loadMap();

	SDL_Flip(screen);
}

void game::handleEvent(){
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
}


void game::start(){
	//std::ifstream in("mapa1.txt");

	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("Primeiro mapa",NULL);
	Uint32 start = SDL_GetTicks();

	//bool running = true;
	while(running){
		handleEvent();
		render();

		//Se a velocidade que o programa faz um ciclo for menor que o FPS temos que atrasa-lo
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
}

