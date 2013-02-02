#include "draw.hpp"
#include <iostream>
#include "SDL/SDL.h"

using namespace std;

void drawMap(Map map, SDL_Surface* screen){
	Uint32 color;
	int contx = 0;
	int conty = 0;
	
	for(int i=0;i<300;i++){
		//le o codigo do tile no mapa
		//seleciona cor baseada no codigo
		switch(map.tiles[i].code){
			case '0': //branco
				color = SDL_MapRGB(screen->format,0xff,0xff,0xff);
				break;
			case '1': //preto
				color = SDL_MapRGB(screen->format,0x00,0x00,0x00);
				break;
			case '2': //cinza
				color = SDL_MapRGB(screen->format,0x66,0x66,0x66);
				break;
			case '3': //verde
				color = SDL_MapRGB(screen->format,0x00,0xff,0x00);
				break;
			case '4': //vermelho
				color = SDL_MapRGB(screen->format,0xff,0x00,0x00);
				break;
			default:
				color = SDL_MapRGB(screen->format,0x00,0x00,0x00);
		}
		
		//cria o retangulo
		SDL_Rect rect;
		rect.x = contx*40;
		rect.y = conty*40;
		rect.w = 40;
		rect.h = 40;
		//desenha o retangulo
		SDL_FillRect(screen,&rect,color);
		contx++;
		//atualiza os conts
		if(contx==20){
			contx = 0;
			conty++;
		}
		
	}
	
	SDL_Flip(screen);
	
}

void drawImg(SDL_Surface* img, SDL_Surface* screen, int x, int y){

	SDL_Rect r;
	r.x = x*40;
	r.y = y*40;

	SDL_BlitSurface(img,NULL,screen,&r);
	SDL_Flip(screen);
}
