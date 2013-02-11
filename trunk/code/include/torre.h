#ifndef TORRE_H
#define TORRE_H

#include <aliado.h>
#include <ataque.h>

enum TipoTorre
{
	NINJA
};

class Torre : Aliado
{
private:

	int ataquePorSegundo;
	TipoTorre tipo;
	static const int WIDTH;
	static const int HEIGHT;

	int desenharAtaque();
	void configurarTorre(TipoTorre tipo);

public:

	vector<Ataque *> * ataques;

	Torre(TipoTorre tipo, int x, int y);
	~Torre();
	int realizarUpgrade();
	int detectarEvento();
	int desenhar();
};

#endif