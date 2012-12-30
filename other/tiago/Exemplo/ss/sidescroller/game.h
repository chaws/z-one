#include <iostream>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "base.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#ifndef GAME_H
#define GAME_H

class game : public baseclass{
	SDL_Surface* load_image(const char* c);
	SDL_Rect camera;	//the relative coordinate of the game
	std::vector<std::vector<int> > map;
	std::vector<enemy*> enemies;
	SDL_Surface* blocks,*screen,*background;
	void loadmap(const char* c);
	void showmap();
	void handleEvent();
	bool running;
	bool direction[2];
	player* player1;
	std::vector<bullet*> bullets;
	TTF_Font* font;
	SDL_Rect finish;
	static const int SCREEN_WIDTH=640;
	static const int SCREEN_HEIGHT=480;	
	public:
	game();
	~game();
	void start();
	int showmenu(SDL_Surface*);
	void showMessage(const char* c);
};

#endif
