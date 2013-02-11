#ifndef JOGO_H
#define JOGO_H

#include <desenhavel.h>
#include <movimentavel.h>
#include <escutavel.h>
#include <tempo.h>
#include <tela.h>
#include <mapa.h>
#include <vector>

using namespace std;

enum EstadoJogo
{
	ENTRADA_JOGO,
	MENU_PRINCIPAL,
	JOGANDO,
	FIM_JOGO,
	SAIDA_APLICATIVO
};

class Jogo
{
private:
	EstadoJogo estadoJogo;
	vector<Desenhavel *> * vetorDesenhaveis;
	vector<Escutavel *> * vetorEscutaveis;
	Tempo * tempo;
	Mapa * mapa;
	Tela * tela;
	
	int estadoEntradaJogo();
	int estadoMenuJogo();
	int estadoJogando();
	int estadoFimJogo();
	int estadoSairAplicativo();
	int detectarSaidaAplicativo();
	int detectarTodosEventos();
	int desenharTudo();

public:
	Jogo();
	~Jogo();
	int rodar();
};

#endif
