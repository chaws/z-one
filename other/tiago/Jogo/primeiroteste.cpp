#include "SDL/SDL.h"

#define VELOCIDADE 2;

#define WIDTH 640
#define HEIGHT 480
#define BPP 32 //Bits por pixel

bool colisao(SDL_Rect* rect1, SDL_Rect* rect2);

int main(int argc, char** argv){
	//Inicializando SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
	//Inicializando a tela
	SDL_Surface* screen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_SWSURFACE);
	
	//Estabilizando FPS
	const int FPS = 30;
	Uint32 start;
	
	//Direção do movimento
	bool direcao[4] = {0,0,0,0};
	
	//Algumas cores
	Uint32 branco = SDL_MapRGB(screen->format,0xff,0xff,0xff);
	Uint32 preto = SDL_MapRGB(screen->format,0x00,0x00,0x00);
	Uint32 azul = SDL_MapRGB(screen->format,0x00,0x00,0xff);
	Uint32 verde = SDL_MapRGB(screen->format,0x00,0xff,0x00);
	Uint32 vermelho = SDL_MapRGB(screen->format,0xff,0x00,0x00);
	
	//Criando retangulos
	SDL_Rect inimigo = {50,50,20,20}; //x,y,w,h
	SDL_Rect chegada = {550,50,20,20};
		
	SDL_FillRect(screen,&chegada,verde);

	SDL_Rect mapa[7];
	
	mapa[0].x = WIDTH/4;
	mapa[0].y = 0;
	mapa[0].w = 50;
	mapa[0].h = 420;
	
	mapa[1].x = WIDTH/2;
	mapa[1].y = 60;
	mapa[1].w = 50;
	mapa[1].h = 420;

	mapa[2].x = (WIDTH/4)*3;
	mapa[2].y = 0;
	mapa[2].w = 50;
	mapa[2].h = 420;
	//Paredes
	mapa[3].x = 0;
	mapa[3].y = 0;
	mapa[3].w = WIDTH;
	mapa[3].h = 30;
	
	mapa[4].x = 0;
	mapa[4].y = 0;
	mapa[4].w = 30;
	mapa[4].h = HEIGHT;
	
	mapa[5].x = WIDTH-30;
	mapa[5].y = 0;
	mapa[5].w = 30;
	mapa[5].h = HEIGHT;
	
	mapa[6].x = 0;
	mapa[6].y = HEIGHT-30;
	mapa[6].w = WIDTH;
	mapa[6].h = 30;

	for(int i=0;i<7;i++){
		SDL_FillRect(screen,&mapa[i],branco);
	}
	
	//Loop do jogo
	bool running = true;
	while(running){
		start = SDL_GetTicks();
		SDL_Event event;
		
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_UP:
							direcao[0] = 1;
							break;
						case SDLK_LEFT:
							direcao[1] = 1;
							break;
						case SDLK_DOWN:
							direcao[2] = 1;
							break;
						case SDLK_RIGHT:
							direcao[3] = 1;
							break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_UP:
							direcao[0] = 0;
							break;
						case SDLK_LEFT:
							direcao[1] = 0;
							break;
						case SDLK_DOWN:
							direcao[2] = 0;
							break;
						case SDLK_RIGHT:
							direcao[3] = 0;
							break;
					}
					break;
			}
		}
		SDL_FillRect(screen,&inimigo,preto);
		//Lógica
		if(direcao[0]){
			inimigo.y = inimigo.y-VELOCIDADE;	//decrescer o Y faz subir
			//Se tiver uma colisão move pra trás
			for(int i=0;i<4;i++)
				if(colisao(&inimigo,&mapa[i]))
					inimigo.y = inimigo.y+VELOCIDADE;

		}
		if(direcao[1]){
			inimigo.x = inimigo.x-VELOCIDADE;
			for(int i=0;i<4;i++)
				if(colisao(&inimigo,&mapa[i]))
					inimigo.x = inimigo.x+VELOCIDADE;
		}
		if(direcao[2]){
			inimigo.y = inimigo.y+VELOCIDADE;
			for(int i=0;i<4;i++)
				if(colisao(&inimigo,&mapa[i]))
					inimigo.y = inimigo.y-VELOCIDADE;
		}
		if(direcao[3]){
			inimigo.x = inimigo.x+VELOCIDADE;
			for(int i=0;i<4;i++)
				if(colisao(&inimigo,&mapa[i]))
					inimigo.x = inimigo.x-VELOCIDADE;
		}
		
		
		
		//Renderização
		SDL_FillRect(screen,&inimigo,azul);	//Desenha o retangulo na "screen"
		SDL_Flip(screen);	//Desenha a janela
		
		//Regulando FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS - (SDL_GetTicks()-start));
	}

	//Finaliza SDL
	SDL_Quit();
	return 0;
}

bool colisao(SDL_Rect* rect1, SDL_Rect* rect2){
	//se um retangulo estiver acima do outro
	if(rect1->y >= rect2->y + rect2->h)
		return 0;
	//se um retangulo estiver a esquerda do outro
	if(rect1->x >= rect2->x + rect2->w)
		return 0;
	//se um retangulo estiver abaixo do outro
	if(rect1->y + rect1->h <= rect2->y)
		return 0;
	//se um retangulo estiver a direita do outro
	if(rect1->x + rect1->w <= rect2->x)
		return 0;
	//se todos forem falsos retorna verdadeiro
	return 1;
}












