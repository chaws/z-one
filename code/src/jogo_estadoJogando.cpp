#include <iostream>
#include <vector>

#include <jogo.h>
#include <mapa.h>
#include <inimigo.h>

using namespace std;

int Jogo::estadoJogando()
{
	this->mapa = new Mapa(JARDIM_EXTERNO);
	this->vetorDesenhaveis->push_back(this->mapa);
	
	Mestre * mestreTeste = new Mestre(this->mapa);
	this->vetorDesenhaveis->push_back(mestreTeste);
	this->vetorMutaveis->push_back(mestreTeste);
	
	this->wave = new Wave(NORMAL, this->vetorDesenhaveis, this->vetorMutaveis, this->mapa);

	while(this->estadoJogo == JOGANDO)
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

