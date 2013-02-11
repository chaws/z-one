#ifndef INIMIGO_H
#define INIMIGO_H

#include <movimentavel.h>

enum TipoInimigo
{
	CAPITAO,
	SAQUEADOR,
	CORSARIO,
	PERNA_DE_PAU
};

class Inimigo : public Desenhavel
{
private:
	int pontosVida;
	int pontosExperiencia;
	TipoInimigo tipo;
	int deltaX;
	int deltaY;
public:
	void subtrairVida(int dano);
	Inimigo(int tipo, int x, int y);
	~Inimigo();
	int desenhar();
//	int movimentar();
//	int detectarColisao();	
};

#endif
