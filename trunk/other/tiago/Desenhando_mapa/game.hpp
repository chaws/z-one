#ifndef GAME_HPP
#define GAME_HPP

//#include <fstream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "draw.hpp"
#include "map.hpp"
#include "tile.hpp"
#include <string>

using namespace std;

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

	Map loadMap(const char * map_name);
	SDL_Surface * loadImage(string img);
};

#endif