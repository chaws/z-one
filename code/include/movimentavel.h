#ifndef MOVIMENTAVEL_H
#define MOVIMENTAVEL_H

#include <desenhavel.h>

class Movimentavel : Desenhavel
{
protected:
	int deltaX;
	int deltaY;
public:
	virtual int movimentar() = 0;
	virtual int detectarColisao() = 0;
};

#endif