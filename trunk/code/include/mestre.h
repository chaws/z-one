#ifndef MESTRE_H
#define MESTRE_H

#include <mutavel.h>
#include <mapa.h>

class Mapa;

class Mestre : public Mutavel
{
private:
	int alcance;
	int pontosVida;
public:
	int fazerLogica();
	int detectarColisao();
	int desenhar();
	Mestre(Mapa *mapaAtual);
	~Mestre();
};

#endif
