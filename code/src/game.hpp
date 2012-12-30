#pragma once

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

class Game{
    // Constantes
    static const int SCREEN_WIDTH = 800;    
	static const int SCREEN_HEIGHT = 600;
	static const int BPP = 32;
	static const int FPS = 30;
    
    // Atributos
    SDL_Surface *screen;
    
    //Métodos
	SDL_Surface* load_image(string img);
    void apply_surface(int x, int y, SDL_Surface* src, SDL_Surface* dest);
	void update_time();
    void get_input();
    void colision_detect();
    void render();
	
	public:	
		Game();
		~Game();
		void start();
}
