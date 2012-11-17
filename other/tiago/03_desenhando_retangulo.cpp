#include "SDL/SDL.h"

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Cria um ponteiro para uma tela
	SDL_Surface* screen;
	
	//Inicializa a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Regulando FPS
	const int FPS=30;
	Uint32 start;
	//Criando um retangulo
	SDL_Rect rect;
	rect.x = 10;	//posicao horizontal
	rect.y = 10;	//posicao vertical
	rect.w = 20;	//width = profundidade
	rect.h = 20;	//height = altura
	Uint32 color = SDL_MapRGB(screen->format,0xff,0xff,0xff); //Cor
	Uint32 color2 = SDL_MapRGB(screen->format,0xff,0x00,0x00);
	
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
		//Desenha o retangulo (onde,o que, cor)
		SDL_FillRect(screen,&screen->clip_rect,color); //Desenhando na tela toda
		SDL_FillRect(screen,&rect,color2);
		//Desenha a tela
		SDL_Flip(screen);
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}
