#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"	// -lSDL_mixer

int main(int argc, char** argv){
	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Chunk* effect1;
	Mix_Chunk* effect2;
	Mix_Music* music;
	//Inicialização(frequencia,formato,numero do canal(2=serial),)
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	
	//Carregando a musica e os efeitos
	music = Mix_LoadMUS("som/banjos.wav");
//	effect1 = Mix_LoadWAV("nome.wav");
//	effect2 = Mix_LoadWAV("nome.wav");
	Mix_PlayMusic(music,-1);
	//Cria um ponteiro para uma tela
	SDL_Surface* screen;
	
	//Inicializa a tela
	screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	
	
	//Regulando FPS
	const int FPS=60;
	Uint32 start;	//
	
	//Cores
	Uint32 branco = SDL_MapRGB(screen->format,0xff,0xff,0xff); //Cor
	Uint32 preto = SDL_MapRGB(screen->format,0x00,0x00,0x00);
	
	//Criando um retangulo
	SDL_Rect rect;
	rect.x = 10;	//posicao horizontal
	rect.y = 10;	//posicao vertical
	rect.w = 20;	//width = profundidade
	rect.h = 20;	//height = altura
	
	
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
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_1:
							//Mix_PlayChannel(-1,effect1,0);
							break;
						case SDLK_2:
							//Mix_PlayChannel(-1,effect2,0);
							break;
					}
			}
		}

		//renderizacao
		SDL_FillRect(screen,&rect,branco);
		//SDL_FillRect(screen,&screen->clip_rect,branco);
		SDL_Flip(screen);
		
		//Regula FPS
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	Mix_FreeChunk(effect1);
	Mix_FreeChunk(effect2);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}
