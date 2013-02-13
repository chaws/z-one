#ifndef JOGO_H
#define JOGO_H

#include <desenhavel.h>
#include <mutavel.h>
#include <escutavel.h>
#include <tempo.h>
#include <tela.h>
#include <mapa.h>
#include <mestre.h>
#include <wave.h>
#include <vector>

using namespace std;

class Jogo
{
private:
	vector<Desenhavel *> * vetorDesenhaveis;
	vector<Escutavel *> * vetorEscutaveis;
	vector<Mutavel *> * vetorMutaveis;
	Tempo * tempo;
	Mapa * mapa;
	Tela * tela;
	Wave * wave;
	Mestre * mestre;
	
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
