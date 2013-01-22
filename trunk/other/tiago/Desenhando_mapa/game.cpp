#include "game.hpp"
#include "draw.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

game::game(){
	screen = SDL_SetVideoMode(SCREEN_HEIGHT,SCREEN_WIDTH, BPP, SDL_SWSURFACE);
	running = true;
}

game::~game(){
	SDL_Quit();
}

Map game::loadMap(const char * map_name){
	
	Map m;

	fstream reader;
	if (!reader.is_open())
    {
        reader.open(map_name);

        if (!reader)
        {
            cerr << "Failed to open " << reader << endl;
            //exit(EXIT_FAILURE);  //abort program
        }
    }
	
	char aux;

	for(int i = 0;i<300;i++){
		aux = reader.get();
		if(aux==32 || aux==10){
			i--;
		}
			
		else{
			m.tiles[i].code = aux;
		}
	}
	cout << "Mapa carregado com sucesso!\n";
	reader.close();

	return m;
}

void game::render(){

	SDL_Flip(screen);
}

void game::handleEvent(){
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
					case SDLK_UP:
						
						break;
				}
				break;
		}
	}
}


void game::start(){
	//std::ifstream in("mapa1.txt");

	//Inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("Primeiro mapa",NULL);
	Uint32 start = SDL_GetTicks();

	Map mapa1 = loadMap("map.map");
	drawMap(mapa1, screen);
	//render();
	//bool running = true;
	while(running){
		handleEvent();
		
		
		//Se a velocidade que o programa faz um ciclo for menor que o FPS temos que atrasa-lo
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
}

