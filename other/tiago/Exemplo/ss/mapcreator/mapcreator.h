//This example program is created by thecplusplusuy for demonstration purposes (no video about this, I think, it's too simple, and not show nothing new, but I put the source up, to make a complete program with the simple sidescroller (there is video about that)). It's a map-creator for the simple sidescroller game.
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
//so other people can see the tutorial
//this file is mapcreator.h
#include <SDL/SDL.h>	//for the 2D graphics
#include <fstream>		//for write the finished map to a file
#include <iostream>		//for write out error (only for test purposes, probobly, it's not need anything else)
#include <vector>			//to store the map
#include <cstdlib>		//for the random number generation
#include <ctime>			//for seed the random number generator (it seems, that Linux is not need this header file for time(0)
#include <cstring>		//and the simple C-style string handling

#ifndef MAPCREATOR_H	//we avoid multiple inclusion
#define MAPCREATOR_H

class mapcreator{
	static const int NUMRECT=8;	//number of rectangle in the blocks.bmp file, change this number, if you want to add more rectangle
															//and than draw the 50x50 rectangle into the image
	SDL_Rect coord,camera;			//the absolute and the relative coordinate (relative is needed for the endless background)
	SDL_Rect blocks_rect[NUMRECT];	//the coordinates of the rectangles (probably you can avoid it, with a little trick)
	SDL_Rect enemy_rect;						//the coordinates of the enemy's first frame
	SDL_Surface* screen,*background,*blocks,*enemy;		//an SDL_Surface for the screen (so the window), background image (endless.bmp), for the blocks
																										//(blocks.bmp) and the enemy (enemy.bmp)
	int current;								//the current block
	int timeshift;							//it's needed to set how often do you want to scroll the background, if your mouse is on the edge of the screen
	std::vector<std::vector<int> > map;	//it's represent the map (dynamically allocated to make our job easier)
	void showmap();	//it will show the map on the screen
	SDL_Surface* load_image(const char* c);	//we load the images with this function
	public:
	mapcreator();	//constructor
	~mapcreator();	//destructor
	void start();	//start the game
	void save();	//save the map
};

#endif
