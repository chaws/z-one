#ifndef WAVE_H
#define WAVE_H

#include <inimigo.h>
#include <desenhavel.h>
#include <mutavel.h>
#include <mapa.h>
#include <mestre.h>
#include <vector>

using namespace std;

enum IDWave
{
	NORMAL
};

class Wave
{
private:
	vector<Inimigo *> * vetorInimigos;
	vector<Desenhavel *> * vetorDesenhaveis;
	vector<Mutavel *> * vetorMutaveis;
	Mapa * mapaAtual;
	Mestre * mestreAtual;
	IDWave idWave;
	int quantidadeInimigos;
	int intervaloCriacaoInimigos;
	int indiceVetorInimigo;
	int atraso;
	void configurarWave();
	int removerInimigosMortos();
	int lancarInimigos();
	
public:
	Wave(IDWave idWave, vector<Desenhavel *> * vetorDesenhaveis, vector<Mutavel *> * vetorMutaveis, Mapa * mapaAtual, Mestre * mestreAtual);
	~Wave();
	
	int fazerLogica();
};

#endif
