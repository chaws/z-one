#include "SDL/SDL.h"

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Cria um ponteiro para uma tela
	SDL_Surface* screen;
	
	//Inicializa a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Regulando FPS
	const int FPS=30;
	Uint32 start;	//
	
	//4 direções
	bool b[4] = {0,0,0,0};
	
	//Criando um retangulo
	SDL_Rect rect;
	rect.x = 10;	//posicao horizontal
	rect.y = 10;	//posicao vertical
	rect.w = 20;	//width = profundidade
	rect.h = 20;	//height = altura
	Uint32 color = SDL_MapRGB(screen->format,0xff,0xff,0xff); //Cor
	Uint32 color2 = SDL_MapRGB(screen->format,0xff,0x00,0x00);
	
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
				//Le uma tecla quando é precionada
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_UP:
							b[0]=1;
							break;
						case SDLK_LEFT:
							b[1]=1;
							break;
						case SDLK_DOWN:
							b[2]=1;
							break;
						case SDLK_RIGHT:
							b[3]=1;
							break;
					}
					break;
					//Quando o jogador solta a tecla
					case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_UP:
							b[0]=0;
							break;
						case SDLK_LEFT:
							b[1]=0;
							break;
						case SDLK_DOWN:
							b[2]=0;
							break;
						case SDLK_RIGHT:
							b[3]=0;
							break;
					}
					break;
			}
		}
		
		//logica
		if(b[0])
			rect.y--;	//decrescer o Y faz subir
		if(b[1])
			rect.x--;
		if(b[2])
			rect.y++;
		if(b[3])
			rect.x++;

		//renderizacao
		SDL_FillRect(screen,&screen->clip_rect,color);
		SDL_FillRect(screen,&rect,color2);
		
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}
