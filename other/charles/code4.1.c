#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

	// Ponteiro pro framebuffer
	SDL_Surface * screen;
	
	// Inicia o subsitema de vídeo
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erro ao iniciar video SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Força a chamada da função SDL_Quit ao sair do main
	atexit(SDL_Quit);
	
	// Tenta setar a configuração de vídeo de 640x480 hicolor
	screen = SDL_SetVideoMode(640, 480, 16, SDL_FULLSCREEN);
	if(screen == NULL)
	{
		printf("Erro ao setar modo de video SDL: %s\n", SDL_GetError());
		return 1;
	}

	printf("*** FIM ***\n\n");
	return 0;
}

