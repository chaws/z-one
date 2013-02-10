#ifndef JOGO_H
#define JOGO_H

#include <desenhavel.h>
#include <movimentavel.h>
#include <escutavel.h>
#include <tempo.h>
#include <mapa.h>
#include <vector>

enum
{
	ENTRADA_JOGO,
	MENU_PRINCIPAL,
	JOGANDO,
	FIM_JOGO
} EstadoJogo;

class Jogo
{
private:
	EstadoJogo estadoJogo;
	vector<Desenhavel> *vetorDesenhaveis;
	vector<Movimentavel> *vetorMovimentaveis;
	vector<Escutavel> *vetorEscutaveis;
	Tempo tempo;
	Mapa mapa;
	
	int estadoEntradaJogo();
	int estadoMenuJogo();
	int estadoJogando();
	int estadoFimJogo();
		
public:
	Jogo();
	~Jogo();
	int rodar();
};

#endif
