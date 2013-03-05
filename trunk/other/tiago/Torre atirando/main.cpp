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

#define NORMAL 1
#define COMPRANDO 2

#define SCREEN_W 800
#define SCREEN_H 600
#define FPS 60
#define TILE_W 40
#define TILE_H 40
#define VEL_X 40
#define VEL_Y 0
#define MAX_BALAS 10;

int main(){

	//elementos do jogo
	vector<bala*> balas;
	vector<torre*> ninjas;
	vector<inimigo*> piratas;

	Timer delta; //temporizador utilizado para contar o tempo dentro do jogo

	int gameEstate = 1; //gameEstate inicial
	int tipo_torre = 0; //tipo de torre sendo comprada

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* screen;
	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE); //inicializa a tela
	SDL_WM_SetCaption("Torre atirando",NULL);

	Uint32 corFundo = SDL_MapRGB(screen->format,0xaa,0xaa,0xaa);

	SDL_Event event; //captura eventos
	Uint32 start; //regular fps
	bool running=true; //booleano para rodar o jogo

	SDL_Surface* compra = NULL;
	SDL_Rect compra_box = {0,0,40,40};
	//criando torres
	// ninjas.push_back(new torre(SHURIKEN,50, 50));
	// ninjas.push_back(new torre(KATANA,200,170));
	//criando inimigos
	piratas.push_back(new inimigo(CAPITAO,300,100));
	piratas.push_back(new inimigo(SAQUEADOR,100,220));

	//criando os botões
	botao *botaoShuriken = new botao(SHURIKEN,0,SCREEN_H-40);
	botao *botaoBomba = new botao(BOMBA,40,SCREEN_H-40);

	//Botão para realizar o teste
	botao *botao_refresh = new botao(0,SCREEN_W-40,SCREEN_H-40);
	//inicia o timer
	delta.start();

	//Loop do jogo	
	while(running){
		//Coloca os milisegundos na variável start
		start = SDL_GetTicks();
		//Tratando os eventos
		//MAQUINA DE ESTADOS
		switch(gameEstate){
			case NORMAL:
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
						
						//eventos de clique do mouse
						case SDL_MOUSEBUTTONDOWN:
							if(event.button.button == SDL_BUTTON_LEFT){
								int x = event.button.x;
								int y = event.button.y;

								if(botaoShuriken->clicked(x,y)){
									tipo_torre = SHURIKEN; //MUDAR
									compra = carregaImagem("img/ninja_shuriken.png");
									SDL_SetAlpha(compra,SDL_SRCALPHA,127);
									gameEstate = COMPRANDO;
								}

								if(botaoBomba->clicked(x,y)){
									tipo_torre = BOMBA; //MUDAR
									compra = carregaImagem("img/ninja_bomba.png");
									SDL_SetAlpha(compra,SDL_SRCALPHA,127);
									gameEstate = COMPRANDO;
								}

								if(botao_refresh->clicked(x,y)){
									piratas.push_back(new inimigo(CAPITAO,300,100));
									piratas.push_back(new inimigo(SAQUEADOR,100,220));
								}
							}
						break;
					}
				}
			break;

			case COMPRANDO:
				while(SDL_PollEvent(&event)){
					switch(event.type){
						case SDL_MOUSEMOTION:
							compra_box.x = event.motion.x - 20; // -20 pra centralizar a imagem
							compra_box.y = event.motion.y - 20;
						break;

						case SDL_MOUSEBUTTONDOWN:
							//realiza a compra
							if(event.button.button == SDL_BUTTON_LEFT){
								ninjas.push_back(new torre(tipo_torre,event.button.x - 20,event.button.y - 20));
								SDL_FreeSurface(compra);
								gameEstate = NORMAL;
							}
							//cancela a compra
							if(event.button.button == SDL_BUTTON_RIGHT){
								SDL_FreeSurface(compra);
								gameEstate = NORMAL;
							}
						break;
					}
				}
			break;
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
				// i--;
			}
		}

		//conferir os pontos de vida dos inimigos e deletar os mortos
		for(int i=0;i<piratas.size();i++){
			if(!piratas[i]->isVivo){
				delete piratas.at(i);
				piratas.erase(piratas.begin()+i);
				
			}
		}
		//apos a logica 
		delta.start(); //reinicia o timer

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

		if(gameEstate == COMPRANDO){
			SDL_BlitSurface(compra,NULL,SDL_GetVideoSurface(),&compra_box);
		}

		//desenhando os botões
		botaoShuriken->show();
		botaoBomba->show();
		botao_refresh->show();
		//mostra a tela desenhada
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}
