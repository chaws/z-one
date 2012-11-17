#include "SDL/SDL.h"

bool collision(SDL_Rect* rect1,SDL_Rect* rect2){
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

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	//Cria um ponteiro para uma tela
	SDL_Surface* screen;
	
	//Inicializa a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Regulando FPS
	const int FPS=60;
	Uint32 start;	//
	
	//4 direções
	bool b[4] = {0,0,0,0};
	
	//Cores
	Uint32 branco = SDL_MapRGB(screen->format,0xff,0xff,0xff); //Cor
	Uint32 preto = SDL_MapRGB(screen->format,0x00,0x00,0x00);
	
	//Criando um retangulo
	SDL_Rect rect;
	rect.x = 10;	//posicao horizontal
	rect.y = 10;	//posicao vertical
	rect.w = 20;	//width = profundidade
	rect.h = 20;	//height = altura
	//Criando outro retangulo
	//SDL_Rect rect2 = {40,40,30,100};
	
	//Outros retangulos (array de retangulos)
	SDL_Rect recarr[4];
	recarr[0].x=70;
	recarr[0].y=0;
	recarr[0].h=200;
	recarr[0].w=10;
	
	recarr[1].x=500;
	recarr[1].y=60;
	recarr[1].h=10;
	recarr[1].w=140;
	
	recarr[2].x=300;
	recarr[2].y=60;
	recarr[2].h=200;
	recarr[2].w=10;
	
	recarr[3].x=10;
	recarr[3].y=300;
	recarr[3].h=10;
	recarr[3].w=140;

	//Desenhando os novos retangulo
	for(int i=0;i<4;i++){
		SDL_FillRect(screen,&recarr[i],branco);
	}
	//SDL_FillRect(screen,&rect2,branco);
	
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
				//Le uma tecla quando é precionada
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_UP:
							b[0]=1;
							break;
						case SDLK_LEFT:
							b[1]=1;
							break;
						case SDLK_DOWN:
							b[2]=1;
							break;
						case SDLK_RIGHT:
							b[3]=1;
							break;
					}
					break;
					//Quando o jogador solta a tecla
					case SDL_KEYUP:
					switch(event.key.keysym.sym){
						case SDLK_UP:
							b[0]=0;
							break;
						case SDLK_LEFT:
							b[1]=0;
							break;
						case SDLK_DOWN:
							b[2]=0;
							break;
						case SDLK_RIGHT:
							b[3]=0;
							break;
					}
					break;
			}
		}
		//Desenha um retangulo preto
		SDL_FillRect(screen,&rect,preto);
		//Mexe	
		//logica
		if(b[0]){
			rect.y--;	//decrescer o Y faz subir
			//Se tiver uma colisão move pra trás
			for(int i=0;i<4;i++)
				if(collision(&rect,&recarr[i]))
					rect.y++;

		}
		if(b[1]){
			rect.x--;
			for(int i=0;i<4;i++)
				if(collision(&rect,&recarr[i]))
					rect.x++;
		}
		if(b[2]){
			rect.y++;
			for(int i=0;i<4;i++)
				if(collision(&rect,&recarr[i]))
					rect.y--;
		}
		if(b[3]){
			rect.x++;
			for(int i=0;i<4;i++)
				if(collision(&rect,&recarr[i]))
					rect.x--;
		}

		//renderizacao
		//Desenha um retangulo branco
		SDL_FillRect(screen,&rect,branco);
		//SDL_FillRect(screen,&screen->clip_rect,branco);
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}

	SDL_Quit();
	return 0;
}
