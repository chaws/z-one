#include "game.h"
SDL_Rect baseclass::baseclass::coord;

void game::showMessage(const char* c)
{
	SDL_Color color={255,0,0};
	SDL_Surface* text=TTF_RenderText_Solid(font,c,color);
	SDL_Rect pos={screen->w/2 - text->w/2, 100};
	SDL_BlitSurface(text,NULL,screen,&pos);
	SDL_FreeSurface(text);
	SDL_Flip(screen);
}



int game::showmenu(SDL_Surface* screen)
{
	int x,y;
	bool run=true;
	const int NUMMENU=3;
	const char* array[NUMMENU] = {"Continue","Map creator","Exit"};
	SDL_Surface* menu[NUMMENU];
	bool selected[NUMMENU] = {0,0};
	SDL_Color colors[2] = {{255,255,255},{255,0,0}};

	for(int i=0;i<NUMMENU;i++)
		menu[i]=TTF_RenderText_Solid(font,array[i],colors[0]);

	SDL_Rect pos[NUMMENU];
	for(int i=0;i<NUMMENU;i++)
	{
		pos[i].x=screen->clip_rect.w/2-menu[i]->clip_rect.w/2;
		pos[i].y=screen->clip_rect.h/2+i*(menu[i]->clip_rect.h);
	}
	SDL_Event menuevent;

	SDL_Surface* alpha=SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_SRCALPHA,screen->w,screen->h,32,screen->format->Rmask,screen->format->Gmask,screen->format->Bmask,screen->format->Amask);
	SDL_FillRect(alpha,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));
	SDL_SetAlpha(alpha,SDL_SRCALPHA,129);
	SDL_BlitSurface(alpha,NULL,screen,NULL);
	SDL_FreeSurface(alpha);
	while(run)
	{
		SDL_WaitEvent(&menuevent);
			switch(menuevent.type)
			{
				case SDL_QUIT:
					for(int i=0;i<NUMMENU;i++)
						SDL_FreeSurface(menu[i]);
					return 2;
				case SDL_MOUSEMOTION:
					x=menuevent.motion.x;
					y=menuevent.motion.y;
					for(int i=0;i<NUMMENU;i++)
					{
						if(x>=pos[i].x && x <= (pos[i].x + menu[i]->clip_rect.w) && y>=pos[i].y && y <= (pos[i].y + menu[i]->clip_rect.h))
						{
							if(!selected[i])
							{
								SDL_FreeSurface(menu[i]);
								menu[i]=TTF_RenderText_Solid(font,array[i],colors[1]);
								selected[i]=1;
							}
						}else{
							if(selected[i])
							{
								SDL_FreeSurface(menu[i]);
								menu[i]=TTF_RenderText_Solid(font,array[i],colors[0]);
								selected[i]=0;
							}
						}
				}
				break;
				case SDL_MOUSEBUTTONDOWN:
					x=menuevent.button.x;
					y=menuevent.button.y;
					for(int i=0;i<NUMMENU;i++)
					{
						if(x>=pos[i].x && x <= (pos[i].x + menu[i]->clip_rect.w) && y>=pos[i].y && y <= (pos[i].y + menu[i]->clip_rect.h))
						{
							for(int j=0;j<NUMMENU;j++)
								SDL_FreeSurface(menu[j]);
							return i;
						}
					}
					break;
				case SDL_KEYDOWN:
					if(menuevent.key.keysym.sym==SDLK_ESCAPE)
					{
						for(int i=0;i<NUMMENU;i++)
							SDL_FreeSurface(menu[i]);
						return 0;
					}
					break;
			}
		for(int i=0;i<NUMMENU;i++)
			SDL_BlitSurface(menu[i],NULL,screen,&pos[i]);
		SDL_Flip(screen);
	}
}





game::game()
{
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_SWSURFACE);
	blocks=load_image("blocks.bmp");
	background=load_image("endless.bmp");
	baseclass::coord.x=camera.x=0;
	baseclass::coord.y=camera.y=0;
	baseclass::coord.w=camera.w=SCREEN_WIDTH;
	baseclass::coord.h=camera.h=SCREEN_HEIGHT;
	TTF_Init();
	running=1;
	direction[0]=0;
	direction[1]=0;
	player1=new player(load_image("player.bmp"));
	font=TTF_OpenFont("air.ttf",20);
	finish.x=0;
	finish.y=0;
	finish.w=TILE_SIZE;
	finish.h=TILE_SIZE;
	
}

game::~game()
{
	SDL_FreeSurface(blocks);
	SDL_FreeSurface(background);
	SDL_Quit();
	delete player1;
	for(int i=0;i<bullets.size();i++)
		delete bullets[i];
}

SDL_Surface* game::load_image(const char* c)
{
	SDL_Surface* tmp=SDL_LoadBMP(c);
	SDL_Surface* tmp2=SDL_DisplayFormat(tmp);
	SDL_FreeSurface(tmp);
	SDL_SetColorKey(tmp2,SDL_SRCCOLORKEY,SDL_MapRGB(screen->format,0x00,0xff,0xff));
	return tmp2;
}

void game::loadmap(const char* c)
{
	std::ifstream in(c);
	if(!in.is_open())
	{
		in.open("map.map");
	}
	int width;
	int height;
	in >> width;
	in >> height;
	int current;
	for(int i=0;i<height;i++)
	{
		std::vector<int> vec;
		for(int j=0;j<width;j++)
		{
			if(in.eof())
				return;
			in >> current;
			if(current>=-1 && current<=8)
			{
				if(current==-1){
						enemies.push_back(new enemy(load_image("enemy.bmp"),j*TILE_SIZE,i*TILE_SIZE-5,1,0));
						vec.push_back(0);
						continue;
				}else if(current==3){
					finish.x=j*TILE_SIZE;
					finish.y=i*TILE_SIZE;
					vec.push_back(current);
				}else{
				vec.push_back(current);
				}
			}else{
				vec.push_back(0);
			}
		}
		map.push_back(vec);
	}
	in.close();
	if(finish.x==0 && finish.y==0)
	{
		finish.x=width*TILE_SIZE-TILE_SIZE;
	}
}

void game::showmap()
{
	int start=(baseclass::coord.x-(baseclass::coord.x%TILE_SIZE))/TILE_SIZE;
	int end=(baseclass::coord.x+baseclass::coord.w+(TILE_SIZE-(baseclass::coord.x+baseclass::coord.w)%TILE_SIZE))/TILE_SIZE;
	if(end>map[0].size())
		end=map[0].size();
	if(start<0)
		start=0;
	for(int i=0;i<map.size();i++)
		for(int j=start;j<end;j++)
			if(map[i][j]!=0)
			{
				if(map[i][j]==-1)
				{
						continue;
				}
				SDL_Rect blockrect = {(map[i][j]-1)*TILE_SIZE,0,TILE_SIZE,TILE_SIZE};
				SDL_Rect destrect= {j*TILE_SIZE-baseclass::coord.x,i*TILE_SIZE};
					SDL_BlitSurface(blocks,&blockrect,screen,&destrect);
			}
}

void game::handleEvent()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				running=false;
				return;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						direction[0]=1;
						player1->setMoving(1);
						break;
					case SDLK_RIGHT:
						direction[1]=1;
						player1->setMoving(1);
						break;
					case SDLK_SPACE:
						player1->setJump();
						break;
					case SDLK_f:
						if(player1->getDirection()=='r')
							bullets.push_back(new bullet(load_image("bullet.bmp"),player1->getRect()->x+player1->getRect()->w,player1->getRect()->y+13,5,0));
						else
							bullets.push_back(new bullet(load_image("bullet.bmp"),player1->getRect()->x,player1->getRect()->y+13,-5,0));		
						break;
					case SDLK_ESCAPE:
						int g=showmenu(screen);
						if(g==1)
						{
//							mapcreator mc;
//							mc.start();
							showMessage("Not implemented");
							SDL_Delay(1000);
						}else 
						if(g==2)
							running=false;
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						direction[0]=0;
						player1->setMoving(0);
						break;
					case SDLK_RIGHT:
						player1->setMoving(0);
						direction[1]=0;
						break;
				}
				break;
		}
	}
}

void game::start()
{
	std::ifstream in("game.dat");	//open the files with the maps
	char c[20][30];
	int nummaps=0;
	int currentmap=0;
	while(!in.eof() && nummaps<20)
	{
		in.getline(c[nummaps],30);	//load at max 20 maps (use vector for more) std::vector<std::string>  moremaps
		nummaps++;	//number of maps
	}
	nummaps--;	//we go through with one map
	in.close();
	Uint32 start;
	loadmap(c[currentmap]);	//load the current map (start with 0)
	while(running)
	{
		start=SDL_GetTicks();
		if(direction[0])
		{
			player1->setDirection('l');
			if(player1->getX()>0)
				player1->setXvel(-1);
			else{
				player1->setXvel(0);
				camera.x--;
				baseclass::coord.x--;
			}
			if(camera.x<0)
				camera.x=2000-SCREEN_WIDTH;
		}else if(direction[1])
		{
			player1->setDirection('r');
			if(player1->getX()<80)
				player1->setXvel(1);
			else{
				player1->setXvel(0);
				camera.x++;
				baseclass::coord.x++;
			}
			if(camera.x>=2000-SCREEN_WIDTH)
				camera.x=0;
		}else{
			player1->setXvel(0);
		}
		player1->move(map);

		SDL_BlitSurface(background,&camera,screen,NULL);
		showmap();
		player1->show(screen);
		for(int i=0;i<enemies.size();i++)
		{
			if(collision(&baseclass::coord,enemies[i]->getRect()))
			{
	//			std::cout << "coll" << std::endl;
				SDL_Rect tmprect = {enemies[i]->getRect()->x-baseclass::coord.x,enemies[i]->getRect()->y,enemies[i]->getRect()->w,enemies[i]->getRect()->h};
				if(collision(&tmprect,player1->getRect()))
				{
		//			std::cout << "collision" << std::endl;
					if(player1->getRect()->y+player1->getRect()->h>=enemies[i]->getRect()->y && player1->getRect()->y+player1->getRect()->h<=enemies[i]->getRect()->y+10) //we jumped to an enemy
					{
						delete enemies[i];
						enemies.erase(enemies.begin()+i);
						continue;
					}else{
						player1->setHealth(player1->getHealth()-1);
					}
				}
				enemies[i]->move(map);
				enemies[i]->show(screen);
			}
		}



		//hadle the bullets!
		for(int i=0;i<bullets.size();i++)
			if(bullets[i]->getRect()->x > SDL_GetVideoSurface()->clip_rect.w || bullets[i]->getRect()->x <0)
			{
				delete bullets[i];
				bullets.erase(bullets.begin()+i);			
			}

		for(int i=0;i<bullets.size();i++)
		{
			bullets[i]->show(screen);
			bullets[i]->move();
		}

	int str=(baseclass::coord.x-(baseclass::coord.x%TILE_SIZE))/TILE_SIZE;
	int end=(baseclass::coord.x+baseclass::coord.w+(TILE_SIZE-(baseclass::coord.x+baseclass::coord.w)%TILE_SIZE))/TILE_SIZE;
	bool nc=0;
	if(end>map[0].size())
		end=map[0].size();
	if(start<0)
		start=0;
	for(int i=0;i<map.size();i++)
		for(int j=str;j<end;j++)
		{
			if(map[i][j]==0)
				continue;
			SDL_Rect destrect= {j*TILE_SIZE-baseclass::coord.x,i*TILE_SIZE,TILE_SIZE,TILE_SIZE};
			for(int g=0;g<bullets.size();g++)
				if(collision(&destrect,bullets[g]->getRect()))
				{
					delete bullets[g];
					bullets.erase(bullets.begin()+g);
				}
		}

		for(int i=0;i<enemies.size();i++)
			for(int j=0;j<bullets.size();j++)
			{
				SDL_Rect tmprec={enemies[i]->getRect()->x-baseclass::coord.x,enemies[i]->getRect()->y,40,40};
				if(collision(&tmprec,bullets[j]->getRect()))
				{
					delete enemies[i];
					delete bullets[j];
					enemies.erase(enemies.begin()+i);
					bullets.erase(bullets.begin()+j);
				}
		}






		handleEvent();
		SDL_Flip(screen);


		if(player1->getHealth()==0 || player1->getRect()->y > screen->h)
		{
			showMessage("Game over");
			running=false;
			SDL_Delay(3000);
		}
		SDL_Rect tmp={baseclass::coord.x+player1->getRect()->x,player1->getRect()->y,TILE_SIZE,TILE_SIZE};
		if((baseclass::coord.x+player1->getRect()->x >= finish.x && finish.y==0) || collision(&tmp,&finish))
		{
			currentmap++;
			if(currentmap<nummaps)	//if there are other maps
			{
				showMessage("You win, loading next map...");	//show a message on the screen
				SDL_Delay(3000);	//wait 3 seconds, so you can see
				map.clear();						//load the new map and set back every variable to their initialize state;
				finish.x=finish.y=0;	//set back the finish coordinate to default
				loadmap(c[currentmap]);	//load the map

				for(int i=0;i<enemies.size();i++)
				{
					delete enemies[i];								//delete reserved memory
					enemies.erase(enemies.begin()+i);	//and delete it from the vector too
				}
				for(int i=0;i<bullets.size();i++)
				{
					delete bullets[i];
					bullets.erase(bullets.begin()+i);
				}
				coord.x=0;	//set all parameter back
				coord.y=0;
				camera.x=0;
				camera.y=0;
				delete player1;
				player1=new player(load_image("player.bmp"));	//if you need another picture for the player
				direction[0]=0;	//we are not moving
				direction[1]=0;
			}else
			{
				showMessage("You win, exiting...");
				SDL_Delay(3000);
				running=false;
				break;
			}
		}
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
}
