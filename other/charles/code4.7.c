#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_PENGUINS 100
#define MAX_SPEED	 6

// Estrutura para guardar a informação de um penguin na tela
typedef struct penguin_s
{
	int x, y;
	int dx, dy;
} penguin_t, * penguin_p;

// Vetor de penguins
static penguin_t penguins[NUM_PENGUINS];

// tela e representação agora como global
static SDL_Surface * screen;
static SDL_Surface * penguin;

// Inicia os penguins e suas posições
static void init_penguins()
{
	int i;
	for(i = 0; i < NUM_PENGUINS; i++)
	{
		penguins[i].x = rand() % screen->w;
		penguins[i].y = rand() % screen->h;
		penguins[i].dx = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
		penguins[i].dy = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
	}
}

// Mexe os penguins de acordo com suas dx e dy
static void move_penguins()
{
	int i;
	for(i = 0; i < NUM_PENGUINS; i++)
	{
		penguins[i].x += penguins[i].dx;
		penguins[i].y += penguins[i].dy;
		
		// Se chegar na borda, vira pra tras
		if(penguins[i].x < 0 || penguins[i].x > screen->w - 1)
			penguins[i].dx = -penguins[i].dx;
		if(penguins[i].y < 0 || penguins[i].y > screen->h - 1)
			penguins[i].dy = -penguins[i].dy;
	}
}

// Depois de mexidos, passa a nova disposição dos penguins para a tela
static void draw_penguins()
{
	int i;
	SDL_Rect src, dest;
	for(i = 0; i < NUM_PENGUINS; i++)
	{
		// Pega o penguin inteiro de 0x0 até wxh
		src.x = src.y = 0;
		src.w = penguin->w;
		src.h = penguin->h;
		
		// Desenha o penguin a partir da sua posição (meio)
		dest.x = penguins[i].x - (penguin->w / 2);
		dest.y = penguins[i].y - (penguin->h / 2);
		dest.w = penguin->w;
		dest.h = penguin->h;
		
		// Passa pra janela
		SDL_BlitSurface(penguin, &src, screen, &dest);
	}
}

int main()
{
	SDL_Surface * background;
	SDL_Surface * temp;
	SDL_Rect src, dest;
	int frames;
	
	
	// Inicia o sistema de vídeo
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erro ao iniciar video SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Força a chamada de SDL_Quit ao sair do programa
	atexit(SDL_Quit);
	
	// Tenta iniciar com 640x480 numa janela separada
	screen = SDL_SetVideoMode(640, 480, 16, SDL_DOUBLEBUF);
	if(screen == NULL)
	{
		printf("Erro ao setar modo de video SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Carrega o smallpenguin e o background bmp
	temp = SDL_LoadBMP("background.bmp");
	background = SDL_DisplayFormat(temp);
	if(!background)
	{
		printf("Erro ao abrir bmp: %s\n", SDL_GetError());
		return 1;
	}
	SDL_FreeSurface(temp);
	
	
	temp = SDL_LoadBMP("smallpenguin.bmp");
	// Seta a colorkey no smallpenguin pra ficar com fundo transparente
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, (Uint32)SDL_MapRGB(temp->format, 0, 0, 255));
	
	penguin = SDL_DisplayFormat(temp);
	if(!penguin)
	{
		printf("Erro ao abrir bmp: %s\n", SDL_GetError());
		return 1;
	}
	SDL_FreeSurface(temp);
	
	// Inicia os penguins e suas posições
	init_penguins();
	
	// Anima 300 frames (+/- 10 segundos)
	for(frames = 0; frames < 300; frames++)
	{
		// Desenha o fundo
		src.x = src.y = 0;
		src.w = background->w;
		src.h = background->h;
		dest = src;
		SDL_BlitSurface(background, &src, screen, &dest);
		
		// Desenha os penguins na screen
		draw_penguins();
		
		// Atualiza a janela toda
		SDL_Flip(screen);
		
		SDL_Delay(10);
		
		// Muda as posições dos penguins
		move_penguins();
	}
	
	// Libera os recursos dos bmps
	SDL_FreeSurface(background);
	SDL_FreeSurface(penguin);

	printf("*** FIM ***\n\n");
	return 0;
}

