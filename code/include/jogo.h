#ifndef JOGO_H
#define JOGO_H

#include <desenhavel.h>
#include <mutavel.h>
#include <escutavel.h>
#include <tempo.h>
#include <tela.h>
#include <mapa.h>
#include <wave.h>
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
	vector<Mutavel *> * vetorMutaveis;
	Tempo * tempo;
	Mapa * mapa;
	Tela * tela;
	Wave * wave;
	
	int estadoEntradaJogo();
	int estadoMenuJogo();
	int estadoJogando();
	int estadoFimJogo();
	int estadoSairAplicativo();
	int detectarSaidaAplicativo();
	int detectarTodosEventos();
	int desenharTudo();
	int fazerTodaLogica();

public:
	Jogo();
	~Jogo();
	int rodar();
};

#endif
