#include "game.hpp"

using namespace std;

void Game::start(){
    // Carrega a logo da equipe na tela (não funciona no 'make install'!)
    SDL_Surface* logo = load_image("../media/image/z_one_logo_800_600.png");
    apply_surface(0,0,logo,screen);

	//while(true) {
	    update_time();
	    get_input();
	    colision_detect();
	    render();
	//}
	
	SDL_FreeSurface(logo);
}

void Game::update_time(){
    
}

void Game::get_input(){

}

void Game::colision_detect(){

}

void Game::render(){
    SDL_Flip(screen);
}

void Game::delay(int usec) {
    SDL_Delay(usec);
}



void Game::apply_surface(int x, int y, SDL_Surface* src, SDL_Surface* dest) {
    // Estrutura que irá conter as coordenadas indicado aonde será aplicada a superfície 'src' dentro da superície 'dest'
    SDL_Rect offset;
    
    // Definindo as coordenadas
    offset.x=x;
    offset.y=y;
    
    // Dando o Blit das superfícies
    SDL_BlitSurface( src, NULL, dest, &offset);
}

SDL_Surface* Game::load_image(string img){
    //Inicializa a imagem a se carregada
	SDL_Surface* loadedImage = NULL;
	//Inicializa a imagem otimizada
	SDL_Surface* optimizedImage =  NULL;
	
	//Carrega a imagem
	loadedImage = IMG_Load(img.c_str());
	
	//Se a imagem foi carrega
	if(loadedImage != NULL){
		//Cria a imagem otimizada
        optimizedImage = SDL_DisplayFormat(loadedImage);
        //Libera a imagem antiga da memória
        SDL_FreeSurface(loadedImage);
	}
    
    return optimizedImage;
}

Game::Game(){
    // Inicializa todos os componentes do SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    // Define a tela do jogo 
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,BPP,VIDEO_OPTIONS);
	// Define o título da tela do jogo
	SDL_WM_SetCaption("Ninja Siege", "Ninja Siege");
	printf("Ninja Siege, by Z-One Team.\n");
}

Game::~Game(){
    // Libera a estrutura da tela do jogo
    SDL_FreeSurface(screen);
    // Libera todas as alocações do SDL (desliga)
    SDL_Quit();
}
