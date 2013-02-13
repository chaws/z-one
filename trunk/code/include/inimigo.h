#ifndef INIMIGO_H
#define INIMIGO_H

#include <mutavel.h>
#include <mapa.h>

enum TipoInimigo
{
	CAPITAO,
	SAQUEADOR,
	CORSARIO,
	PERNA_DE_PAU
};


class Mapa;

class Inimigo : public Mutavel
{
private:
	
	int pontosExperiencia;
	TipoInimigo tipo;
	int deltaX;
	int deltaY;
	PontoTile tileAtual;
	PontoTile tileAnterior;
	int velocidade;
	Mapa * mapaAtual;
	bool recemCriado;	
	int pixelsAndados;

	
	int setarProximaPosicao();
	void tremer();
	bool ehCaminho(int posicao);
	
public:
	bool estaMorto;
	int pontosVida;  			// DEPOIS VER ISSO :D
	void subtrairVida(int dano);
	Inimigo(int tipo, Mapa * mapaAtual);
	~Inimigo();
	int desenhar();
	int fazerLogica();
	int detectarColisao();	
};

#endif
