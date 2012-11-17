#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

Uint16 CreateHicolorPixel(SDL_PixelFormat * pf, Uint8 red, Uint8 green, Uint8 blue)
{
	Uint16 value;
	value = ((red >> pf->Rloss) << pf->Rshift) +
		 	((green >> pf->Gloss) << pf->Gshift) +
		 	((blue >> pf->Bloss) << pf->Bshift);
	return value;
}

int main()
{
	
	SDL_Surface * screen;
	Uint16 * raw_pixels;
	int x, y;
	
	// Inicia o subsistema de vídeo
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erro ao iniciar video SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Seta função ao sair da main
	atexit(SDL_Quit);
	
	// No livro tenta setar um modo de 256x256...só que 
	// isso altera a config do unbuntu, logo vou deixar
	// o padrão: 1366x768
	screen = SDL_SetVideoMode(1366, 768, 16, 0);
	if(screen == NULL)
	{
		printf("Erro ao setar modo de video SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Antes de alterar o valor dos pixels, locka a tela
	SDL_LockSurface(screen);
	
	// Pega o endereço dos pixels
	raw_pixels = (Uint16 *)screen->pixels;
	
	// Agora faz a mágica
	for(x = 0; x < 256; x++)
	{
		for(y = 0; y < 256; y++)
		{
			Uint16 pixel_color;
			int offset;
			pixel_color = CreateHicolorPixel(screen->format, x, 0, y);
			offset = (screen->pitch / 2 * y + x);
			raw_pixels[offset] = pixel_color;
		}
	}
	
	// Deslocka a surface
	SDL_UnlockSurface(screen);
	
	// Atualiza a tela
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	
	// Espera 3 segundos para ver o resultado
	SDL_Delay(3000);
	 
	printf("*** FIM ***\n\n");
	return 0;
}

