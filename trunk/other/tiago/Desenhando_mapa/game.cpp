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
	if (!reader.is_open()){
        reader.open(map_name);

        if (!reader){
            cerr << "Failed to open " << reader << endl;
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
	reader.close();

	return m;
}

SDL_Surface * game::loadImage(string img)
{
	// Deve-se fazer um tratamento para verificar a extensão da imagem
	// Inicializa a imagem a se carregada
	SDL_Surface * loadedImage = NULL;
	
	// Inicializa a imagem otimizada
	SDL_Surface * optimizedImage =  NULL;
	
	// Carrega a imagem
	//cout << "Abrindo: " << img.c_str() << endl;
	loadedImage = IMG_Load(img.c_str());
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
	Uint32 start;

	Map mapa1 = loadMap("map.map");
	drawMap(mapa1, screen);
	SDL_Surface * ninjak = loadImage("ninja_katana.png");
	SDL_Surface * ninjaa = loadImage("ninja_amarelo.png");
	SDL_Surface * pirata = loadImage("pirata.png");
	drawImg(ninjak, screen,4,2);
	drawImg(ninjaa, screen,4,4);
	drawImg(pirata, screen,3,1);

	while(running){
		start = SDL_GetTicks();
		handleEvent();
		//Se a velocidade que o programa faz um ciclo for menor que o FPS temos que atrasa-lo
		if(1000/FPS > SDL_GetTicks()-start)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
	SDL_FreeSurface(ninjaa);
	SDL_FreeSurface(ninjak);
	SDL_FreeSurface(pirata);
}

