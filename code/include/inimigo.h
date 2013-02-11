#ifndef INIMIGO_H
#define INIMIGO_H

#include <movimentavel.h>

enum TipoInimigo
{
	PIRATA,
	SAMURAI
};

class Inimigo : public Movimentavel
{
private:
	int pontosVida;
	int pontosExperiencia;
	TipoInimigo tipo;
public:
	void subtrairVida(int dano);
};

#endif
