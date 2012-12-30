#include "enemy.h"

enemy::enemy(SDL_Surface* img,int x,int y,int xVel,int yVel)
{
	image=img;
	box.x=x;
	box.y=y;
	box.w=image->clip_rect.w/2;
	box.h=image->clip_rect.h;
	xvel=xVel;
	yvel=yVel;
	ground=0;
	clips[0].x=clips[0].y=0;
	clips[0].w=clips[0].h=40;
	clips[1].x=40;
	clips[1].y=0;
	clips[1].w=clips[1].h=40;
	frame=0.0;
		
}

enemy::~enemy()
{
	SDL_FreeSurface(image);
}

SDL_Rect* enemy::getRect()
{
	return &box;
}

void enemy::move(std::vector<std::vector<int> >& map)
{
	int start=(baseclass::coord.x-(baseclass::coord.x%TILE_SIZE))/TILE_SIZE-2;
	int end=(baseclass::coord.x+baseclass::coord.w+(TILE_SIZE-(baseclass::coord.x+baseclass::coord.w)%TILE_SIZE))/TILE_SIZE+2;
	bool nc=0;
	if(end>map[0].size())
		end=map[0].size();
	if(start<0)
		start=0;


	for(int i=0;i<map.size();i++)
		for(int j=start;j<end;j++)
		{
			if(map[i][j]==0)
				continue;

			SDL_Rect destrect= {j*TILE_SIZE,i*TILE_SIZE,TILE_SIZE,TILE_SIZE};
				if(collision(&destrect,&box))
				{
		//			std::cout << box.x << std::endl;
					if(destrect.y>=box.y+box.h-11)
					{
							ground=1;
							yvel=0;
							nc=1;
					}
					if(box.x+box.w>=destrect.x-5 && box.y+box.h>=destrect.y+6 && box.x+box.w<=destrect.x+20) //collision - right to the player
					{	
						xvel=-xvel;
					}
					else if(box.x<=destrect.x+destrect.w && box.y+box.h>=destrect.y+6) //collision - left to the player
					{
						xvel=-xvel;
					}
				}
		}
	if(!nc)
		yvel=5;
	box.x+=xvel;
	box.y+=yvel;
	frame+=0.1;
	if(frame>=1.4)
		frame=0.0;
}


void enemy::show(SDL_Surface* screen)
{
//	std::cout << box.x << " " << baseclass::coord.x << std::endl;
	SDL_Rect tmp= {box.x-baseclass::coord.x,box.y,TILE_SIZE,TILE_SIZE};
	SDL_BlitSurface(image,&clips[(int)(frame+0.5)],screen,&tmp);
}

double enemy::getXvel()
{
	return xvel;
}

void enemy::setXvel(double vel)
{
	xvel=vel;
}
