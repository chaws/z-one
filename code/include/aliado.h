#ifndef ALIADO_H
#define ALIADO_H

#include <escutavel.h>

class Aliado : public Escutavel
{
protected:
	int alcance;
	int dano;
public:
	virtual int realizarUpgrade() = 0;
};

#endif
