#include "SDL/SDL.h"

int main (int argc, char *argv[])
{
	SDL_Surface* hello = NULL;
	SDL_Surface* screen = NULL;
	
	//Inicia SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
	//Seta a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
	//Carregando a imagem
	hello = SDL_LoadBMP("hello.bmp");
			
	//Aplica imagem na tela
	SDL_BlitSurface(hello, NULL, screen, NULL);

	//Atualiza a tela
	SDL_Flip(screen);
		
	//Pausa
	SDL_Delay(2000);

	//Libera a memoria utilizada pela imagem carregada
	SDL_FreeSurface(hello);	
	
	//Finaliza SDL
	SDL_Quit();
	
	return 0;
}
