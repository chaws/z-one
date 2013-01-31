#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	SDL_Surface * screen;
	SDL_Event evt;

	// Inicia o SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erro na inicializacao do video %s\n", SDL_GetError());
		return 1;
	}
	
	// Seta função ao sair
	atexit(SDL_Quit);
	
	screen = SDL_SetVideoMode(800, 600, 16, 0);
	if(!screen)
	{
		printf("Erro na inicializacao da janela %s\n", SDL_GetError());
		return 1;
	}
	
	printf("'Q' para sair.\n");
	
	while(SDL_WaitEvent(&evt))
	{
		SDL_keysym keysym;
		
		// Verifica qual evento, tipo pra verificar evento de mouse
		switch(evt.type)
		{
			case SDL_KEYDOWN:
				printf("Tecla pressionada. ");
				keysym = evt.key.keysym;
				printf("SDL keysym is %i. ", keysym.sym);
				printf("(%s) ", SDL_GetKeyName(keysym.sym));
				
				// Mostra qual tecla foi pressionada
				if(evt.key.keysym.mod & KMOD_LSHIFT)
					printf("Left shift is down\n");
				else
					printf("Left shift is up\n");
					
				// A tecla Q foi pressionada ?
				if(keysym.sym == SDLK_q)
				{
					printf("'Q' foi pressionado! saindo...\n");
					exit(0);
				}
				
				break;
			case SDL_KEYUP:
				printf("Key released. ");
				printf("SDL keysym is %i. ", keysym.sym);
				printf("(%s) ", SDL_GetKeyName(keysym.sym));
				
				if(evt.key.keysym.mod & KMOD_LSHIFT)
					printf("Left shift is down\n");
				else
					printf("Left shift is up\n");
				
				break;
			
			case SDL_QUIT:
				printf("Botao fechar!\n");
				exit(0);
		}
	}
	
	printf("Fim |\n");
	return 0;
}

