#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	SDL_Surface * screen;
	SDL_Surface * background;
	SDL_Surface * image;
	SDL_Rect src, dest;
	Uint32 colorkey;
	
	// Tenta iniciar o driver de video
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Chama SDL_Quit ao sair
	atexit(SDL_Quit);
	
	// Tenta iniciar uma janela 640x480
	screen = SDL_SetVideoMode(640, 480, 16, 0);
	if(screen == NULL)
	{
		printf("Pala ao iniciar a janela %s\n", SDL_GetError());
		return 1;
	}
	
	// Carrega o background e o penguin
	image      = SDL_LoadBMP("penguin.bmp");
	background = SDL_LoadBMP("background.bmp");
	if(!image || !background)
	{
		printf("Pala ao carregar bmp %s\n", SDL_GetError());
		return 1;
	}
	
	// Desenha o background na tela
	src.x = src.y = dest.x = dest.y = 0; // Posição na imagem e na janela
	src.w = dest.w = background->w;      // width
	src.h = dest.h = background->h;      // height
	SDL_BlitSurface(background, &src, screen, &dest);
	
	// Desenha o penguin sem a cor-chave
	src.x = src.y = 0;			// Posição a ser copiada da fonte
	dest.x = 30;				// Posição de inicio da cópia na janela
	dest.y = 90;				// mesma coisa, só que para y
	src.w = dest.w = image->w;  // width
	src.h = dest.h = image->h;	// height
	SDL_BlitSurface(image, &src, screen, &dest);
	
	// Desenha com a cor chave, seleciona o azul
	colorkey = SDL_MapRGB(image->format, 0, 0, 255);
	
	// Setamos a cor-chave como o azul dentro da imagem, isto é
	// tudo que for azul, fica transparente
	// Para remover a cor-chave, basta chamar a mesma função
	// colocando 0 ao inves de SDL_SRCCOLORKEY
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
	
	// Inicia a cópia do penguin com colorkey
	src.x = src.y = 0;
	src.w = dest.w = image->w;
	src.h = dest.h = image->h;
	dest.x = screen->w - image->w - 30;
	dest.y = 90;
	SDL_BlitSurface(image, &src, screen, &dest);

	// Atualiza a janela com o conteúdo de screen
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	
	// Sleep de 10 segundos
	SDL_Delay(10000);
	
	// Libera recursos
	SDL_FreeSurface(background);
	SDL_FreeSurface(image);
	
	return 0;
}

