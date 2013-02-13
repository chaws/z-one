#include <iostream>
#include <vector>
#include <util.h>
#include <jogo.h>
#include <mapa.h>
#include <inimigo.h>

using namespace std;

int Jogo::estadoJogando()
{
	this->vetorDesenhaveis =  new vector<Desenhavel *>;
	this->vetorEscutaveis =  new vector<Escutavel *>;
	this->vetorMutaveis =  new vector<Mutavel *>;
	
	this->mapa = new Mapa(SALA_TREINAMENTO);
	this->vetorDesenhaveis->push_back(this->mapa);
	
	this->mestre = new Mestre(this->mapa);
	this->vetorDesenhaveis->push_back(this->mestre);
	this->vetorMutaveis->push_back(this->mestre);
	
	this->wave = new Wave(NORMAL, this->vetorDesenhaveis, this->vetorMutaveis, this->mapa, this->mestre);

	while(Util::estadoJogo == JOGANDO)
	{
		this->tempo->iniciarTempo();
		this->detectarTodosEventos();
		this->fazerTodaLogica();
		this->desenharTudo();
		this->tela->renderizar();
		this->tempo->atrasarTempo();
	}
	return 0;	
}

	/*
		Inimigo * inimigos[15];
	for(int i = 0; i < 15; i++)
		inimigos[i] = new Inimigo(CAPITAO, this->mapa);;
	
	if (espera % 15 == 0 && i < 15)
		{			
			this->vetorDesenhaveis->push_back(inimigos[i]);
			this->vetorMutaveis->push_back(inimigos[i++]);	
		}
		
		
		
	// Responsaveis por trocar a referencia dos desenhaveis do jogo
	static vector<Desenhavel *> * desenhaveis; 
	vector<Desenhavel *> * tempDesenhavel;

	// Responsaveis por trocar a referencia dos escutaveis do jogo
	static vector<Escutavel *> * escutaveis;
	vector<Escutavel *> * tempEscutavel;

	// Registrar elementos que serao desenhados
	if(desenhaveis)
	{
		tempDesenhavel = this->vetorDesenhaveis;
		this->vetorDesenhaveis = desenhaveis;
	}*/
	

	//vector<Torre *> * vetorTorres;
	//vector<Movimentavel *> * vetorMovimentaveis;
	//vector<Wave *> * vetorMovimentaveis;

