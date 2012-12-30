#pragma once

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

class Game{
	
	SDL_Surface* load_image(string img);
	
	static const int SCREEN_WIDTH = 800;	
	static const int SCREEN_HEIGHT = 600;
	static const int BPP = 32;
	const int FPS = 30;
	
	public:	
		game();
		~game();
		void start();
}
