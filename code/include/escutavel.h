#ifndef ESCUTAVEL_H
#define ESCUTAVEL_H

#include <desenhavel.h>
#include <SDL/SDL.h>

class Escutavel : Desenhavel
{
public:
	virtual int detectarEvento() = 0;
	static SDL_Event evento;
};

#endif
