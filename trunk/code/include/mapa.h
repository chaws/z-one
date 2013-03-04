#ifndef MAPA_H
#define MAPA_H

#include <escutavel.h>
#include <vector>

struct PontoTile
{
	int x;
	int y;
};

#include <inimigo.h>
#include <mestre.h>

using namespace std;

enum Tile
{
	NAO_UTILIZAVEL,
	CAMINHO,
	UTILIZAVEL,
	ENTRADA,
	SAIDA
};

enum TipoMapa
{
	JARDIM_EXTERNO,
	SALA_BANHO,
	SALA_TREINAMENTO
};

class Mapa : public Escutavel
{	
private:
	TipoMapa tipo;
	PontoTile tileEntrada;
	PontoTile tileSaida;
	void configurarMapa();
	void gerarSuperficieEmBranco();
	void gerarSuperficieMapa();
	static const int NUMERO_TOTAL_TILES;
	vector<Tile> * tiles;

public:
	static const int TILE_WIDTH;
	static const int TILE_HEIGHT;
	static const int TILES_POR_LINHA;

	Mapa(TipoMapa tipo);
	~Mapa();
	int desenhar();	
	int detectarEvento();
	
	friend class Inimigo;
	friend class Mestre;
};

#endif
