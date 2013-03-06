#ifndef TORRE_H
#define TORRE_H

#include <aliado.h>
#include <inimigo.h>
#include <ataque.h>
#include <wave.h>
#include <tempo.h>
#include <vector>

using namespace std;

enum TipoTorre
{
	SHURIKEN,
	KATANA,
	NUNCHAKU,
	MARIKI,
	KUNAI,
	BOMBA
};

enum EstadoTorre
{
	VIGIANDO,
	ATACANDO
};

class Torre : public Aliado
{
private:

	int ataquePorSegundo;
	TipoTorre tipo;
	SDL_Surface * ataque;
	static const int WIDTH;
	static const int HEIGHT;
	EstadoTorre estado;
	bool atirei;
	SDL_Rect alcance; //area de percepcao da torre

	float DPS; //tiros por segundo
	float velocidadeTiro; // velocidade do tiro

	Uint32 comecaAtacar;
	Inimigo *alvo;
	void configurarTorre(TipoTorre tipo);
	bool isInimigoProximo(Inimigo * inimigo);
	int removerAtaquesTerminados();
	bool estaMaisProximo(Inimigo * candidatoAlvo, Inimigo * alvoAtual);

public:

	vector<Ataque *> * vetorAtaques;
	vector<Inimigo *> * vetorInimigos;
	vector<Desenhavel *> * vetorDesenhaveis;
	vector<Mutavel *> * vetorMutaveis;

	Torre(TipoTorre tipo, int x, int y, Wave * waveAtual, vector<Desenhavel *> * vetorDesenhaveis, vector<Mutavel *> * vetorMutaveis);
	~Torre();

	int fazerLogica();
	int realizarUpgrade();
	int detectarEvento();
	int desenhar();
	int detectarColisao();
	
};

#endif
