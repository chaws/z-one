#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	SDL_Surface * screen;
	SDL_Surface * image;
	SDL_Rect src, dest;
	
	// Inicia o sistema de vídeo
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erro ao iniciar video SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Força a chamada de SDL_Quit ao sair do programa
	atexit(SDL_Quit);
	
	// Tenta iniciar com 256x256 numa janela separada
	screen = SDL_SetVideoMode(512, 512, 16, 0);
	if(screen == NULL)
	{
		printf("Erro ao setar modo de video SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Carrega uma imagem numa surface
	image = SDL_LoadBMP("smallpenguin.bmp");
	if(image == NULL)
	{
		printf("Erro ao abrir bmp: %s\n", SDL_GetError());
		return 1;
	}
	
	// Prepara para colar na tela
	src.x = src.y = 0;
	src.w = image->w;
	src.h = image->h;
	
	dest.x = dest.y = 0;
	dest.w = image->w;
	dest.h = image->h;
	
	// Copia a imagem para a tela
	// OBS: essa função dispensa o locker da surface
	SDL_BlitSurface(image, &src, screen, &dest);
	
	// Lembra de atualizar a tela
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	
	// Mostra ao usuário
	SDL_Delay(5000);
	
	// Libera a memória usada pra carregar a imagem
	SDL_FreeSurface(image);

	printf("*** FIM ***\n\n");
	return 0;
}

