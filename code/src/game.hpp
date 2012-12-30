#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Game{
	
	static const int SCREEN_WIDTH = 800;	
	static const int SCREEN_HEIGHT = 600;
	static const int BPP = 32;
	const int FPS = 30;
	
	public:	
		game();
		void start();
}
