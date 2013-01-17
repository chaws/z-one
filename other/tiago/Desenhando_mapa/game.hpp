#ifndef GAME_HPP
#define GAME_HPP

//#include <fstream>
#include "SDL/SDL.h"

class game{	
	static const int SCREEN_HEIGHT = 800;
	static const int SCREEN_WIDTH = 600;
	static const int BPP = 32;
	static const int FPS = 30;

	bool running;
	
	SDL_Surface* screen;
public:
	game();
	~game();
	void start();
	void handleEvent();
	void render();
};

#endif