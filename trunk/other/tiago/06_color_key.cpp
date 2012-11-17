#include "SDL/SDL.h"

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
	//Imagem é uma nova superficie
	SDL_Surface* screen, *image;
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Regulando FPS
	const int FPS=30;
	Uint32 start;	//

	Uint32 color = SDL_MapRGB(screen->format,0xff,0xff,0xff); //Cor
	Uint32 color2 = SDL_MapRGB(screen->format,0xff,0x00,0x00);
	
	//Carregando a imagem
	image = SDL_DisplayFormat(SDL_LoadBMP("imagem.bmp"));
	
	//Loop do jogo
	bool running = true;
	while(running){
		start = SDL_GetTicks();
		//Tratando os eventos
		//Estrutura dos eventos onde ficam os eventos
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				//Le clicar no Fechar da janela
				case SDL_QUIT:
					running = false;
					break;
			}
		}
		
		//logica
		
		//renderizacao
		SDL_FillRect(screen,&screen->clip_rect,color);

		//Copiando a imagem na tela
		SDL_BlitSurface(image,NULL,screen,NULL);
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	//Se copiou tem que liberar a imagem da memória
	SDL_FreeSurface(image);
	SDL_Quit();
	return 0;
}
