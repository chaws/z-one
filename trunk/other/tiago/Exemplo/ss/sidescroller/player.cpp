#include "player.h"
#include "base.h"

player::player(SDL_Surface* img)
{
	image=img;
	box.x=30;
	box.y=20;
	box.w=TILE_SIZE;
	box.h=TILE_SIZE;
	ground=0;
	xvel=yvel=0;
	frame=0.;
	for(int i=0;i<4;i++)
	{
		clips[i].x=i*TILE_SIZE;
		clips[i].y=0;
		clips[i].w=clips[i].h=TILE_SIZE;
	}
	jump=0;
	health=10;
	direction='r';
	moving=false;
}

player::~player()
{
	SDL_FreeSurface(image);
}

int player::getX()
{
	return box.x;
}

int player::getXvel()
{
	return xvel;
}

void player::setXvel(int vel)
{
	xvel=vel;
}

void player::setMoving(bool b)
{
	moving=b;
}

char player::getDirection()
{
	return direction;
}

void player::show(SDL_Surface* screen)
{
/*	if(direction=='r')
		SDL_BlitSurface(image,&clips[0],screen,&box);
	else
		SDL_BlitSurface(image,&clips[1],screen,&box);	*/
	SDL_BlitSurface(image,&clips[(int)(frame+0.5)],screen,&box);
}

void player::move(const std::vector<std::vector<int> >& map)
{
	int start=(baseclass::coord.x-(baseclass::coord.x%TILE_SIZE))/TILE_SIZE;
	int end=(baseclass::coord.x+baseclass::coord.w+(TILE_SIZE-(baseclass::coord.x+baseclass::coord.w)%TILE_SIZE))/TILE_SIZE;
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
			SDL_Rect destrect= {j*TILE_SIZE-baseclass::coord.x,i*TILE_SIZE,TILE_SIZE,TILE_SIZE};
			if(collision(&destrect,&box))
			{
	//			std::cout << destrect.x << " " << destrect.y << " " << box.x << " " << box.y << std::endl;
				nc=1;
				if(destrect.y>=box.y+box.h-11) //collision - the block is under the player
				{
						ground=1;
						yvel=0;
				}else if(destrect.y+destrect.h<=box.y+11)
				{
		//			std::cout << "fenn" << std::endl;
					box.y++;
					yvel=5;
				}
//if(box.x+box.w>=destrect.x-5 && box.y+box.h>=destrect.y+6)
				if(box.x+box.w>=destrect.x-5 && box.y+box.h>=destrect.y+6 && box.x+box.w<=destrect.x+20) //collision - right to the player
				{	
					xvel=0;
//					std::cout << "cooll" << std::endl;
					box.x--;
					moving=false;
				}
				else if(box.x<=destrect.x+destrect.w && box.y+box.h>=destrect.y+6) //collision - left to the player
				{
//					std::cout << "cooll2" << std::endl;
					xvel=0;
					box.x++;
					moving=false;
				}
			}
		}
//	std::cout << "--------------" << std::endl;
	if(!nc && !jump)
	{
		yvel=5;
		ground=0;
	}
	if(jump && yvel<5)
		yvel++;
	else
		jump=0;
	box.x+=xvel;
	box.y+=yvel;
	if(moving)
	{
		frame+=0.2f;
//		std::cout << (int)(frame+0.5) << std::endl;
		if(direction=='r' && frame>=1.4)
			frame=0.f;
		else if(direction=='l' && frame>=3.0f)
			frame=1.6f;
	}
		
}

void player::setJump()
{
	if(ground && !jump)
	{
		ground=0;
		jump=1;
		yvel=-17;
		box.y-=5;
	}
}

SDL_Rect* player::getRect()
{
	return &box;
}

int player::getHealth()
{
	return health;
}

void player::setHealth(int heal)
{
	health=heal;
}

void player::setDirection(const char dir)
{
	if((dir=='r' || dir=='l') && direction!=dir)
	{
		direction=dir;
		if(direction=='r')
			frame=0.0;
		else
			frame=2.6;
	}
}
