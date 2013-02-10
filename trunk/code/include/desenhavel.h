#ifndef DESENHAVEL_H
#define DESENHAVEL_H

#include <SDL/SDL.h>

class Desenhavel
{
protected:
	SDL_Rect * rect;
	SDL_Surface * imagem;
public:
	virtual int desenhar() = 0;
};


#endif