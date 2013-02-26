#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include "util.h"
#include "torre.h"
#include "inimigo.h"
#include "bala.h"
#include "timer.h"
#include "botao.h"

using namespace std;

#define KATANA 1
#define NUNCHAKU 2
#define MARIKI 3
#define SHURIKEN 4
#define KUNAI 5
#define BOMBA 6

#define CAPITAO 1
#define CORSARIO 2
#define SAQUEADOR 3
#define PERNADEPAU 4

#define SCREEN_W 400
#define SCREEN_H 300
#define FPS 60
#define TILE_W 40
#define TILE_H 40
#define VEL_X 40
#define VEL_Y 0
#define MAX_BALAS 10;


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

	Uint32 corFundo = SDL_MapRGB(screen->format,0xaa,0xaa,0xaa);

	SDL_Event event; //captura eventos
	Uint32 start; //regular fps
	bool running=true; //booleano para rodar o jogo

	//criando uma torre
	ninjas.push_back(new torre(SHURIKEN,50, 50));
	ninjas.push_back(new torre(KATANA,200,170));
	piratas.push_back(new inimigo(CAPITAO,300,100));
	piratas.push_back(new inimigo(SAQUEADOR,100,220));

	//criando um botao
	botao *botaoShuriken = new botao(SHURIKEN,0,SCREEN_H-40);
	botao *botaoBomba = new botao(BOMBA,40,SCREEN_H-40);

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
			
			botaoBomba->handleEvents(&event);
			botaoShuriken->handleEvents(&event);

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
		
		for(int i=0;i<ninjas.size();i++){
			ninjas[i]->update(delta.get_ticks(), &piratas, &balas);
		}

		//movimenta as balas
		for(int i=0;i<balas.size();i++){
			balas[i]->update(delta.get_ticks());
		}

		//deleta as balas que ja completaram o caminho
		for(int i=0;i<balas.size();i++){
			if(balas.at(i)->cheguei == true){				
				balas.erase(balas.begin()+i);
			}
		}

		//TEM BUG AQUI
		//conferir os pontos de vida dos inimigos e deletar os mortos
		for(int i=0;i<piratas.size();i++){
			if(!piratas[i]->isVivo){
				delete piratas.at(i);
				piratas.erase(piratas.begin()+i);
				
			}
		}

		//apos a logica 
		delta.start(); 
		/**RENDERIZACAO**/
		//redesenha a tela com uma cor
		SDL_FillRect(screen,&screen->clip_rect,corFundo);
		
		//desenha os ninjas
		for(int i=0;i<ninjas.size();i++){
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

		botaoShuriken->show();
		botaoBomba->show();
		//mostra a tela desenhada
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}
