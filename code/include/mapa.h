#ifndef MAPA_H
#define MAPA_H

#include <desenhavel.h>
#include <vector>

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

class Mapa : public Desenhavel
{	
private:
	TipoMapa tipo;
	void configurarMapa();
	void carregarCodigosTiles(vector <Tile> * vetorCodigosTiles);
	void gerarSuperficieEmBranco();

public:
	Tile tiles[300];
	
	Mapa(TipoMapa tipo);
	~Mapa();
	int desenhar();	

};

#endif
