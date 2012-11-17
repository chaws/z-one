#include "SDL/SDL.h"

void setrects(SDL_Rect* clip){
	for(int i=0;i<=10; i++){
		clip[i].x = 0+i*80;
		clip[i].y = 0;
		clip[i].w = 80;
		clip[i].h = 68;
	}
}

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
	//Imagem é uma nova superficie
	SDL_Surface* screen, *image;
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Regulando FPS
	const int FPS=30;
	Uint32 start;

	Uint32 color = SDL_MapRGB(screen->format,0xff,0xff,0xff); //Cor
	Uint32 color2 = SDL_MapRGB(screen->format,0xff,0x00,0x00);
	
	//Carregando a imagem
	image = SDL_DisplayFormat(SDL_LoadBMP("low.bmp"));
	//Elimina a cor azul de fundo
	SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0x00,0xff,0xff));
	
	//Frames da animação
	SDL_Rect rects[11];
	setrects(rects);
	int frame =0;
	
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

		SDL_Rect rect;
		rect.x = 200;
		rect.y = 100;

		SDL_BlitSurface(image,&rects[frame],screen,&rect);
		
		SDL_Flip(screen);
		frame++;
		if(frame==11)
			frame=0;
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	//Se copiou tem que liberar a imagem da memória
	SDL_FreeSurface(image);
	SDL_Quit();
	return 0;
}
