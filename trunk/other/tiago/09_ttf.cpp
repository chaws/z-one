#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Inicializando TTF (True Text Format)
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("appleberry.ttf",32);
	//Cria um ponteiro para uma tela
	SDL_Surface* screen, *text;
	
	//Inicializa a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Regulando FPS
	const int FPS=30;
	Uint32 start;
		
	Uint32 color = SDL_MapRGB(screen->format,0x00,0x00,0x00); //Cor
	Uint32 color2 = SDL_MapRGB(screen->format,0xff,0xff,0xff);
	
	SDL_Color color3 = {255,255,255};
	text = TTF_RenderText_Solid(font,"Hello World!",color3);
	
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
		//logica
		
		//renderizacao
		SDL_BlitSurface(text,NULL,screen,NULL);
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
