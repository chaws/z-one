#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include "torre.h"
#include "inimigo.h"
#include "bala.h"
#include "timer.h"
using namespace std;

#define SCREEN_W 400
#define SCREEN_H 300
#define FPS 60
#define TILE_W 40
#define TILE_H 40
#define VEL_X 40
#define VEL_Y 0
#define MAX_BALAS 10;

SDL_Surface * loadImage(const char* img);
bool collision(SDL_Rect* rect1, SDL_Rect* rect2);

int main(){

	vector<bala*> balas;
	vector<torre*> ninjas;
	vector<inimigo*> piratas;

	Timer delta;

	int numBalas = 0;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* screen;
	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE); //inicializa a tela
	SDL_WM_SetCaption("Torre atirando",NULL);

	SDL_Event event; //captura eventos
	Uint32 start; //regular fps
	bool running=true; //booleano para rodar o jogo

	//criando uma torre
	ninjas.push_back(new torre(loadImage("ninja_katana.png"),50, 50, TILE_W, TILE_H));
	ninjas.push_back(new torre(loadImage("ninja_katana.png"),200,170, TILE_W, TILE_H));
	piratas.push_back(new inimigo(loadImage("pirata_capitao.png"),300,100,TILE_W,TILE_H,VEL_X,VEL_Y));
	piratas.push_back(new inimigo(loadImage("pirata_capitao.png"),100,200,TILE_W,TILE_H,VEL_X,VEL_Y));

	//inicia o timer
	delta.start();

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
				case SDL_MOUSEMOTION:
					for(int i=0;i<ninjas.size();i++){
						ninjas[i]->DetectMouseOver(event.motion.x,event.motion.y);
					}
					break;
			}
		}
		
		/**LOGICA**/
		//movimenta os piratas
		for(int i=0;i<piratas.size();i++){
			piratas[i]->update(delta.get_ticks());
		}
		
		//se o pirata se aproximar do ninja o ninja ataca
		for(int i=0;i<ninjas.size();i++){
			//se um inimigo se aproximar do ninja
			for(int j=0;j<piratas.size();j++){
				if(ninjas[i]->isInimigoProximo(&piratas[j]->box)){
					//ataque o inimigo! uma shuriken por vez
					if(numBalas<1){
						balas.push_back(new bala(loadImage("shuriken.png"), ninjas[i]->box.x+20, ninjas[i]->box.y+20, 10, 10, 12, 1,piratas[j]->box.x+20,piratas[j]->box.y+20));
						//dano no inimigo
						piratas[j]->pontosDeVida -= ninjas[i]->dano;
						numBalas++;
					}
				}
			}			
		}
		
		//quando as balas chegam no inimigo elas sao destruidas
		for(int i=0;i<balas.size();i++){
			//quando a bala colide com o alvo ela eh destruida
			if((balas[i]->box.x>balas[i]->alvoX-10 && (balas[i]->box.x)<(balas[i]->alvoX+10)) && (balas[i]->box.y>balas[i]->alvoY-10 && balas[i]->box.y<balas[i]->alvoY+10)){
				balas.erase(balas.begin()+i);
				delete balas[i];
				numBalas--;
			}
		}
		//conferir os pontos de vida dos inimigos e deletar os mortos
		for(int i=0;i<piratas.size();i++){
			if(!piratas[i]->isVivo){
				piratas.erase(piratas.begin()+i);
				delete piratas[i];
			}
		}

		//movimenta as balas
		for(int i=0;i<balas.size();i++){
			balas[i]->move();
		}
		//apos a logica 
		delta.start(); 
		/**RENDERIZACAO**/
		//redesenha a tela com uma cor
		SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x19,0x19,0x70));
		
		//desenha os ninjas
		for(int i=0;i<ninjas.size();i++){
			//se o mouse estiver sobre o ninja mostra o alcance do ninja
			if(ninjas[i]->mouseOver)
				ninjas[i]->showAlcance();
			ninjas[i]->show();
		}

		//desenha o pirata
		for(int i=0;i<piratas.size();i++){
			piratas[i]->show();
		}

		//desenha as balas na tela
		for(int i=0;i<balas.size();i++){
			balas[i]->show();
		}
		//mostra a tela desenhada
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