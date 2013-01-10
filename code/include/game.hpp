#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

using namespace std;

/**
 *@brief Classe principal do jogo. Cuida da entrada de inputs etc e talz
 */
class Game{
    /**
	 *
	 */
    static const int SCREEN_WIDTH = 800;    
    
    /**
	 *
	 */
	static const int SCREEN_HEIGHT = 600;
	
	/**
	 *
	 */
	static const int BPP = 32;
	
	/**
	 *
	 */
	static const int FPS = 30;
	
	/**
	 *
	 */
	static const Uint32 VIDEO_OPTIONS = SDL_HWSURFACE | SDL_DOUBLEBUF;
    
    /**
	 *
	 */
    SDL_Surface *screen;
    
    /**
	 *
	 */
	SDL_Surface* load_image(string img);
	
	/**
	 *
	 */
    void apply_surface(int x, int y, SDL_Surface * src, SDL_Surface * dest);
    
    /**
	 *
	 */
	void update_time();
	
	/**
	 *
	 */
    void get_input();
    
    /**
	 *
	 */
    void colision_detect();
    
    /**
	 *
	 */
    void render();
	
	public:	
	
		/**
		 *
		 */
		Game();
		
		/**
		 *
		 */
		~Game();
		
		/**
		 *
		 */
		void start();
		
		/**
		 *
		 */
		void delay(int usec);
};

#endif

