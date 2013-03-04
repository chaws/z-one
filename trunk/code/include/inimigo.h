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
	
	TipoInimigo tipo;
	PontoTile tileAtual;
	PontoTile tileAnterior;
	Mapa * mapaAtual;

	int deltaX;
	int deltaY;
	int velocidade;
	int pixelsAndados;
	bool recemCriado;	

	
	int setarProximaPosicao();
	bool ehCaminho(int posicao);
	void tremer();
	
public:
	Inimigo(int tipo, Mapa * mapaAtual);
	~Inimigo();

	bool estaMorto;
	int pontosVida;  			// DEPOIS VER ISSO :D
	int pontosExperiencia;

	int desenhar();
	int fazerLogica();
	int detectarColisao();	
	void subtrairVida(int dano);
};

#endif
