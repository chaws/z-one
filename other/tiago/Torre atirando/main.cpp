#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include "torre.h"
#include "inimigo.h"
using namespace std;

#define SCREEN_W 400
#define SCREEN_H 300
#define FPS 60
#define TILE_W 40
#define TILE_H 40
#define VEL_X 3
#define VEL_Y 0

SDL_Surface * loadImage(const char* img);

int main(){

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* screen;
	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE); //inicializa a tela
	SDL_WM_SetCaption("Torre atirando",NULL);

	SDL_Event event; //captura eventos
	Uint32 start; //regular fps
	bool running=true; //booleano para rodar o jogo

	//criando uma torre
	torre ninja(loadImage("ninja_katana.png"),50, 50, TILE_W, TILE_H);
	inimigo pirata(loadImage("pirata_capitao.png"),300,100,TILE_W,TILE_H,VEL_X,VEL_Y);

	//Loop do jogo	
	while(running){
		//Coloca os milisegundos na variável start
		start = SDL_GetTicks();
		//Tratando os eventos
		//Estrutura dos eventos onde ficam os eventos
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_x: //tecla "x"
							//ninja.shot();
						break;
					}
					break;
				case SDL_MOUSEMOTION:
					ninja.DetectMouseOver(event.motion.x,event.motion.y);
					break;
			}
		}
		
		/**LOGICA**/
		pirata.move();
		if(ninja.isInimigoProximo(&pirata.box)){
			ninja.setCor(0xff,0x00,0x00);
			//atire no inimigo!
		}
		else
			ninja.setCor(0x00,0xff,0x00);

		

		/**RENDERIZACAO**/
		SDL_FillRect(screen,&screen->clip_rect,0);
		if(ninja.mouseOver)
			ninja.showAlcance();
		ninja.show();
		pirata.show();
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}

SDL_Surface * loadImage(const char* img){
	// Deve-se fazer um tratamento para verificar a extensão da imagem
	// Inicializa a imagem a se carregada
	SDL_Surface * loadedImage = NULL;
	
	// Inicializa a imagem otimizada
	SDL_Surface * optimizedImage =  NULL;
	
	// Carrega a imagem
	//cout << "Abrindo: " << img.c_str() << endl;
	loadedImage = IMG_Load(img);
	//loadedImage = SDL_LoadBMP(img.c_str());
	
	// Se a imagem foi carregada
	if(!loadedImage)
	{
		cout << "Erro ao abrir: " << SDL_GetError() << endl;
		return NULL;
	}
	//cout << "Aberta com sucesso!" << endl;
	// Cria a imagem otimizada
    optimizedImage = SDL_DisplayFormat(loadedImage);
    
    // Libera a imagem antiga da memória
    SDL_FreeSurface(loadedImage);
    
    // Fazer o colorKey
    Uint32 colorkey = SDL_MapRGB(optimizedImage->format,0x00,0xff,0xfc);
    SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);

    return optimizedImage;
}