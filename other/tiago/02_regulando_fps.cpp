#include "SDL/SDL.h"

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Titulo da janela
	SDL_WM_SetCaption("Teste de TD",NULL);
	//Cria um ponteiro para uma tela
	SDL_Surface* screen;
	
	//Inicializa a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Precisamos saber se o programa esta rodando no tempo que deveria estar rodando. Para 30 FPS temos que dar um novo frame a cada 33.33 milesegundos (1000/30)
	const int FPS=30;
	Uint32 start;
	
	//Loop do jogo
	bool running = true;
	while(running){
		//Coloca os milisegundos na variável start
		start = SDL_GetTicks();
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
		//Se a velocidade que o programa faz um ciclo for menor que o FPS temos que atrasa-lo
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}
