#ifndef ESCUTAVEL_H
#define ESCUTAVEL_H

#include <desenhavel.h>

class Escutavel : Desenavel
{
public:
	virtual int detectarEvento() = 0;
};

#endif