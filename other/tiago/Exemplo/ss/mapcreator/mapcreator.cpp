//This example program is created by thecplusplusuy for demonstration purposes (no video about this, I think, it's too simple, and not show nothing new, but I put the source up, to make a complete program with the simple sidescroller (there is video about that)). It's a map-creator for the simple sidescroller game.
//http://www.youtube.com/user/thecplusplusguy
//Free source, modify if you want, LGPL licence (I guess), I would be happy, if you would not delete the link
//so other people can see the tutorial
//this file is mapcreator.cpp
#include "mapcreator.h"	//we include the header, which we have created

mapcreator::mapcreator()
{
	SDL_Init(SDL_INIT_EVERYTHING);	//don't forget to initialize the SDL, it's allocate the needed memory. We initialize everything
	screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);	//open our window
	background=load_image("endless.bmp");	//open our 3 image
	blocks=load_image("blocks.bmp");
	enemy=load_image("enemy.bmp");
	enemy_rect.x=enemy_rect.y=0;	//we set the coordinate of the enemy (it's not animated when you make the map, only in the game)
	enemy_rect.w=enemy_rect.h=40;
	for(int i=0;i<NUMRECT;i++)	//we set the coordinate of the blocks (tiles)
	{
		blocks_rect[i].x=i*50;	//only the x coordinate is change
		blocks_rect[i].y=0;			//we have just 1 row of tiles
		blocks_rect[i].w=50;		//width=50
		blocks_rect[i].h=50;		//hight=50

	}
	current=0;	//we use the current block 0 (green grass for me :D)
	for(int i=0;i<10;i++)	//we make the default map (10*50=500 which is just a little bigger then the 480 height of the window)
	{
		std::vector<int> vec;	//the map is represented by a vector in a vector (a multidimensional dynamically allocated array)
		for(int j=0;j<13;j++)	//13*50=650 which is just a little bigger then the with of the window (640)
			vec.push_back(0);		//default we put nothing in everywhere
		map.push_back(vec);		//and than add it
	}
	coord.x=0;	//we set the default coordinates, nothing to explain here
	coord.y=0;
	coord.w=640;
	coord.h=480;
	camera.x=0;
	camera.y=0;
	camera.w=640;
	camera.h=480;
	timeshift=0;
}

mapcreator::~mapcreator()
{
	SDL_FreeSurface(background);	//free the surfaces and escape from SDL
	SDL_FreeSurface(blocks);
	SDL_FreeSurface(enemy);
	SDL_Quit();
}

void mapcreator::start()	//the main loop is in here
{
	Uint32 start;	//to regulate the FPS
	const int FPS=30;	//we use 30 FPS (if you want you can use SDL_WaitEvent, so you don't need to specify the FPS)
	bool running=true;	//is the program running?
	SDL_Event event;
	int x,y;	//the x,y coordinate of the mouse cursor relative to the window
	while(running)
	{
		start=SDL_GetTicks();	//we fill start with the current time
		while(SDL_PollEvent(&event))	//while there are events
		{
			switch(event.type)	//which event is it?
			{
				case SDL_QUIT:
					running=0;	//if we exited, exit from the program
					break;
				case SDL_MOUSEBUTTONDOWN:	//if a mouse button is down then
					if(event.button.button==SDL_BUTTON_RIGHT)	//if this button is the right mouse button
					{
						x=event.button.x;	//get the coordinate
						y=event.button.y;
						x=x-(x%50);	//Little trickey, but basically we round down to the nearest 50 for example
						y=y-(y%50);	//if we are at 143 x coordinate then we set x to 100 if we are at 49 coordinate we set x to 0
						//if we are at 50 coordinate we leave it as 50, we ded the same to y too.
						current++;	//we increase the current (show the next block)
						if(current>=NUMRECT)	//if we go too far, set it back to -2 (-2 enemy, -1 nothing)
							current=-2;
					}else if(event.button.button==SDL_BUTTON_LEFT)	//if the left button is pressed
					{
						x=event.button.x;	//get the current coordinates
						y=event.button.y;
						x=x-(x%50);//and do the same thing again with the x and y coordinates (round down to the nearest number dividable by 50)
						y=y-(y%50);
						map[((int)(y/50)+coord.y/50)][((int)(x/50)+coord.x/50)]=current+1;
						//that's a little trickey again, but all we do in here is get the index for the tile, and then add our absolute coordinate to it
//for example, if we are at 0,0 coordinate, and we click at 150,200 coordinate, than change the map[3][4] coordinate to the current tile
//you may noticed, it's current+1, that's because originally the 0 is the nothing, and the first tile (according to C rules the 0th) is the 1st
//a little problem, nothing more. So another example, if we are at 1000,0 coordinate and we click at 150,200, than map[3][24]=current+1
					}
					break;
				case SDL_MOUSEMOTION:	//if we moved the mouse
					x=event.motion.x;	//we get the coordinates again
					y=event.motion.y;
					x=x-(x%50);	//and we round to the nearest 50 again
					y=y-(y%50);
					break;
					case SDL_KEYDOWN:
						if(event.key.keysym.sym==SDLK_s)	//if the s key is down
							save();	//save the map
						break;	
			}
		}
//		std::cout << x << std::endl;
					if(x>550)	//if we are at the right edge of the screen
					{
						if(timeshift==0)	//and the timeshift is 0
						{
							timeshift=20;	//change it to 20 (it's mean, that we move the camera 20 frame later)
							coord.x+=50;	//move the camera
							camera.x+=50; //move the camera
							if(camera.x>=2000-640)	//if the background have to be reapeted
								camera.x=0;	//repeat it
							for(int i=0;i<map.size();i++)	//we add on coloumn of nothing to the end of the map
							{
								map[i].push_back(0);
							}
						}else
							timeshift--;	//just decrease the timeshift every time, it's not equal to 0
					}
					if(x<50 && coord.x>=50)	//we do the same thing in the other direction too
					{
						if(timeshift==0)
						{
							timeshift=20;
							coord.x-=50;
							camera.x-=50;
							if(camera.x<=0)
								camera.x=2000-640;
						}else
							timeshift--;
					}

		SDL_BlitSurface(background,&camera,screen,NULL);	//we draw the background at the correct position 
																											//(watch the scrollable background tutorial, if it's not clear
		showmap();	//and we show the map
		SDL_Rect tmp={x,y};
		if(current>=0)	//if the current is not 0 (or less then except the enemy)
			SDL_BlitSurface(blocks,&blocks_rect[current],screen,&tmp);	//draw the block, which we are holding to the position of the mouse cursor
		else if(current==-2)	//if it's an enemy
			SDL_BlitSurface(enemy,&enemy_rect,screen,&tmp);	//draw it
		SDL_Flip(screen);	//show the screen
		if(1000/FPS>(SDL_GetTicks()-start))	//regulate the FPS (watch regulate FPS tutorial, if it's not clear)
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
	}
}

SDL_Surface* mapcreator::load_image(const char* c)	//load the image
{
	SDL_Surface* tmp=SDL_LoadBMP(c);	//load the BMP file
	SDL_Surface* tmp2=SDL_DisplayFormat(tmp);	//then convert it to the format of the screen
	SDL_FreeSurface(tmp);	//free it, we don't need it anymore
	SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0x00,0xff,0xff)); //set a color key, so 00ffff is transparent
	return tmp2;	//return a pointer to the surface
}

void mapcreator::showmap()
{
	//it should be familiar to you, because basically it's the same as in the sidescroller game
	int start=(coord.x-(coord.x%50))/50;	//calculate the first number which is dividable by 50 and it's in the screen
	int end=(coord.x+coord.w+(50-(coord.x+coord.w)%50))/50; //round last number, dividable by 50, which is in the screen
	if(end>map[0].size())	//if the end is too big
		end=map[0].size();	//set it to the size of the map
	if(start<0)	//if start is too small
		start=0;	//set it to the first element
	for(int i=0;i<map.size();i++)
		for(int j=0;j<map[0].size();j++)	//go through the visible map
			if(map[i][j]!=0)	//if it's not "nothing"
			{
				if(map[i][j]==-1)	//if it's an enemy
				{
					//draw it
					SDL_Rect blockrect = {0,0,40,40};
					SDL_Rect destrect= {j*50-coord.x,i*50};
					SDL_BlitSurface(enemy,&blockrect,screen,&destrect);
						continue;	//and don't draw anything else
				}
				//else draw the block which is needed
				SDL_Rect blockrect = {(map[i][j]-1)*50,0,50,50};
				SDL_Rect destrect= {j*50-coord.x,i*50};
				SDL_BlitSurface(blocks,&blockrect,screen,&destrect);
			}
}


void mapcreator::save()
{
	char c[30];	//filename
	sprintf(c,"%d",time(0));	//we use the current time in seconds from 1970.01.01 (it's always changing, so every time it will get a uniqe filename)
	//pretty basic, but easy and fairly effective
	strcat(c,".map");	//we cat the map extension to the end of the number
	std::ofstream out(c);	//open the filestream for output with the current name
//	std::cout << "Saved" << std::endl;	
	out << map[0].size() << " " << map.size() << std::endl;	//first we write out the size of the map
	for(int i=0;i<map.size();i++)	//go through the array
	{
		for(int j=0;j<map[0].size();j++)
		{
			out << map[i][j] << " ";	//and write the tile number separated by space
		}
		out << std::endl;
	}
}
