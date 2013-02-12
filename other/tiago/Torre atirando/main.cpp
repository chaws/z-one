#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include "torre.h"
#include "inimigo.h"
#include "bala.h"
using namespace std;

#define SCREEN_W 400
#define SCREEN_H 300
#define FPS 60
#define TILE_W 40
#define TILE_H 40
#define VEL_X 1
#define VEL_Y 0
#define MAX_BALAS 10;

SDL_Surface * loadImage(const char* img);
bool collision(SDL_Rect* rect1, SDL_Rect* rect2);

int main(){

	vector<bala*> balas;
	int numBalas = 0;
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
		//movimenta o inimigo
		pirata.move();
		
		//se o inimigo se aproximar da torre a torre atira
		if(ninja.isInimigoProximo(&pirata.box)){
			//ninja.setCor(0xff,0x00,0x00);
			//atire no inimigo!
			if(numBalas<10){
				balas.push_back(new bala(loadImage("shuriken.png"), ninja.box.x+20, ninja.box.y+20, 10, 10, 12, 1,pirata.box.x+20,pirata.box.y+20));
				numBalas++;
			}
		}
		else
			//ninja.setCor(0x00,0xff,0x00);
		
		//quando as balas chegam no inimigo elas sao destruidas
		for(int i=0;i<balas.size();i++)
			if(collision(balas[i]->getRect(),&pirata.box)){
				delete balas[i];
				balas.erase(balas.begin()+i);
				numBalas--;	
			}
			
		//movimenta as balas
		for(int i=0;i<balas.size();i++){
			balas[i]->move();
		}

		/**RENDERIZACAO**/
		//redesenha a tela com branco
		SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0xff,0xff,0xff));
		//se o mouse estiver sobre o ninja mostra o alcance do ninja
		if(ninja.mouseOver)
			ninja.showAlcance();
		//desenha as balas na tela
		for(int i=0;i<balas.size();i++){
			balas[i]->show();
		}
		//desenha o ninja
		ninja.show();
		//desenha o pirata
		pirata.show();
		//renderiza tudo na tela de jogo
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

bool collision(SDL_Rect* rect1, SDL_Rect* rect2){
	if(rect1->y >= rect2->y + rect2->h)
		return 0;
	if(rect1->x >= rect2->x + rect2->w)
		return 0;
	if(rect1->y + rect1->h <= rect2->y)
		return 0;
	if(rect1->x + rect1->w <= rect2->x)
		return 0;
	return 1;

}