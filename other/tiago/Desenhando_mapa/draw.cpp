#include "draw.hpp"
#include <iostream>
#include "SDL/SDL.h"

using namespace std;

void drawMap(Map map, SDL_Surface* screen){
	Uint32 color;
	int contx = 0;
	int conty = 0;
	//SDL_Rect recarr[300];
	//cout << "Desenhando mapa...\nLinha 0";
	
	for(int i=0;i<300;i++){
		//le o codigo do tile no mapa
		//seleciona cor baseada no codigo
		cout << map.tiles[i].code << "\n";
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
		//cout << "Retangulo " << i << " x: " << rect.x << " y: " << rect.y << "\n";
		//carrega os retangulos em um vetor de retangulos
		//recarr[i] = rect;
		SDL_FillRect(screen,&rect,color);
		contx++;
		//atualiza os conts
		if(contx==20){
			contx = 0;
			//cout << "Linha " << conty << "\n"; 
			conty++;
		}
		
	}
	//Desenha os retangulos
	// for(int i=0;i<300;i++){
	// 	SDL_FillRect(screen,&recarr[i],color);
	// }
	
	SDL_Flip(screen);
	
}