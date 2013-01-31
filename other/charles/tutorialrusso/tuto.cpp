#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	bool running = true;
	const int FPS = 45;
	bool b[4] = {0, 0, 0, 0};
	
	Uint32 start;
	Uint32 colorRect;
	Uint32 colorBack;
	
	SDL_Surface * screen, *text;
	SDL_Event evt;
	SDL_Rect rect;	
	SDL_Rect borda = {40, 40, 30, 100};
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Erro: " << SDL_GetError() << endl;
		return -1;
	}
	
	TTF_Init();
	TTF_Font * fonte = TTF_OpenFont("letters/LETTERS_.TTF", 32);
	
	screen = SDL_SetVideoMode(800, 600, 16, SDL_SWSURFACE);
	if(!screen)
	{
		cout << "Erro: " << SDL_GetError() << endl;
		return -1;
	}
	
	rect.x = 10;
	rect.y = 10;
	rect.w = 20;
	rect.h = 20;
	colorRect = SDL_MapRGB(screen->format, 100, 100, 100);
	colorBack = SDL_MapRGB(screen->format, 0, 0, 0);
	SDL_Color colorFont = {50, 50, 50};
	text = TTF_RenderText_Solid(fonte, "Hello World", colorFont);
	
	SDL_FillRect(screen, &borda, colorRect);
	
	while(running)
	{
		start = SDL_GetTicks(); // Miliseconds
		while(SDL_PollEvent(&evt))
		{
			switch(evt.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(evt.key.keysym.sym)
					{
						case SDLK_UP:
							b[0] = 1;
							break;
						case SDLK_LEFT:
							b[1] = 1;
							break;
						case SDLK_DOWN:
							b[2] = 1;
							break;
						case SDLK_RIGHT:
							b[3] = 1;
							break;
					}
					break;
				case SDL_KEYUP:
					switch(evt.key.keysym.sym)
					{
						case SDLK_UP:
							b[0] = 0;
							break;
						case SDLK_LEFT:
							b[1] = 0;
							break;
						case SDLK_DOWN:
							b[2] = 0;
							break;
						case SDLK_RIGHT:
							b[3] = 0;
							break;
					}
					break;
			}
		}
		
		if(b[0])
			rect.y--;
		if(b[1])
			rect.x--;
		if(b[2])
			rect.y++;
		if(b[3])
			rect.x++;
		
		// Lógica
		//SDL_FillRect(screen, &screen->clip_rect, colorBack);
		SDL_BlitSurface(text, NULL, screen, NULL);
		SDL_FillRect(screen, &rect, colorRect);
		
		
		// Joga do buffer pra tela
		SDL_Flip(screen);
		
		// Ve se precisa de um atraso
		if((1000 / FPS) > (SDL_GetTicks() - start))
			SDL_Delay((1000 / FPS) - (SDL_GetTicks() - start));
	}
	SDL_FreeSurface(text);
	TTF_CloseFont(fonte);
	SDL_Quit();
	TTF_Quit();
	return 0;
	// |\ |
}

