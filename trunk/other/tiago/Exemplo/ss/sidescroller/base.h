#ifndef BASE_H
#define BASE_H
#include <SDL/SDL.h>
class baseclass{
	protected:
		bool collision(SDL_Rect*,SDL_Rect*); 
	public:
		static SDL_Rect coord;
		static const int TILE_SIZE=50;
	//	static const int tile_size=50;
};
#endif
