#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include "ball.h"
#include "paddle.h"

#define WIDTH 640
#define HEIGHT 480

#define SPEED 3

#define FPS 30

SDL_Surface* load_image(const char* c, Uint32 colorkey=0){
	SDL_Surface* tmp = SDL_LoadBMP(c);
	if(colorkey!=0){
		SDL_SetColorKey(tmp,SDL_SRCCOLORKEY,colorkey);
	}
	return tmp;
}

int main(){
	SDL_Surface* screen, *icon;
	screen=SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_SWSURFACE); //inicializa a tela
	icon = load_image("icon.bmp");
	SDL_WM_SetIcon(icon,NULL);
	SDL_WM_SetCaption("Pong",NULL);
	//Fonte inicializando e setando a fonte
	TTF_Init();
	TTF_Font* font;
	font=TTF_OpenFont("Air.ttf",20); //abrindo a fonte
	SDL_Color color = {0xff,0xff,0xff}; //cor utilizada na fonte

	//Inicializando os sons
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	//Mix_Music *music;
	Mix_Chunk* effect;
	//music=Mix_LoadMUS("");
	effect=Mix_LoadWAV("hit.wav");
	//Mix_PlayMusic(music,-1);

	SDL_Event event; //captura eventos
	Uint32 start; //regular fps
	bool running=true; //booleano para rodar o jogo

	bool arr[4] = {0,0,0,0}; //direções

	//jogadores
	paddle player1(load_image("paddle.bmp"),0,225,10,60,SPEED);
	paddle player2(load_image("paddle.bmp"),WIDTH-10,225,10,60,SPEED);
	//bola
	ball ball(load_image("ball.bmp",SDL_MapRGB(screen->format,0x00,0xff,0xff)),320,240,20,20,SPEED,SPEED);

	while(running){
		
		start=SDL_GetTicks();
		
		//eventos
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT: //apertar no x da janela
					running=false;
					break;
				case SDL_KEYDOWN: //apertar uma tecla
					switch(event.key.keysym.sym){
						case SDLK_UP: //tecla "pra cima"
							arr[0]=1;
							break;
						case SDLK_DOWN: //tecla "pra baixo"
							arr[1]=1;
							break;

						case SDLK_w: //tecla "w"
							arr[2]=1;
							break;
						case SDLK_s: //tecla "s"
							arr[3]=1;
							break;
					}
					break;

				case SDL_KEYUP: //solta uma tecla
					switch(event.key.keysym.sym){
						case SDLK_UP: //tecla "pra cima"
							arr[0]=0;
							break;
						case SDLK_DOWN: //tecla "pra baixo"
							arr[1]=0;
							break;

						case SDLK_w: //tecla "w"
							arr[2]=0;
							break;
						case SDLK_s: //tecla "s"
							arr[3]=0;
							break;
					}
					break;
			}
		}

		//logica
		if(arr[0])
			player2.moveUp();
		if(arr[1])
			player2.moveDown();
		if(arr[2])
			player1.moveUp();
		if(arr[3])
			player1.moveDown();
		ball.move(player1.getRect(), player2.getRect(), effect);

		switch(ball.isOut()){
			case 1:
				player2.incpoint();
				player1.setBack(0,225,10,60,SPEED);
				player2.setBack(WIDTH-10,225,10,60,SPEED);
				ball.setBack(320,240,20,20,SPEED,SPEED);
				break;
			case 2:
				player1.incpoint();
				player1.setBack(0,225,10,60,SPEED);
				player2.setBack(WIDTH-10,225,10,60,SPEED);
				ball.setBack(320,240,20,20,SPEED,SPEED);
				break;
		}

		//renderização
		SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));
		player1.show();
		player2.show();
		ball.show();

		//Escrevendo o placar na tela
		char c[5]; //variavel com texto
		SDL_Rect tmp = {10,0}; //retangulo do texto
		sprintf(c,"%d",player1.getPoints()); //escrevendo o texto na variavel c
		SDL_Surface* text = TTF_RenderText_Solid(font,c,color); //escrevendo texto na superficie texto
		SDL_BlitSurface(text,NULL,screen,&tmp); //desenha o texto na tela

		tmp.x=WIDTH-40;
		sprintf(c,"%d",player2.getPoints());
		text = TTF_RenderText_Solid(font,c,color);
		SDL_BlitSurface(text,NULL,screen,&tmp);
		//libera o texto
		SDL_FreeSurface(text);

		SDL_Flip(screen);

		//regulando FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));

	}
	//Mix_FreeMusic(music);
	SDL_FreeSurface(icon);
	Mix_FreeChunk(effect);
	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}