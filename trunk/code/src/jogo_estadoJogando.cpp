#include <iostream>
#include <vector>

#include <jogo.h>
#include <mapa.h>
#include <inimigo.h>

using namespace std;

int Jogo::estadoJogando()
{
	/*
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
	this->vetorDesenhaveis = new vector <Desenhavel *>;
	Inimigo * inimigoTeste = new Inimigo(SAQUEADOR, 0, 160);
	this->mapa = new Mapa(JARDIM_EXTERNO);
	this->vetorDesenhaveis->push_back(this->mapa);
	this->vetorDesenhaveis->push_back(inimigoTeste);
	// Registrar os elementos que terao eventos detectados
	while(this->estadoJogo == JOGANDO)
	{
		this->tempo->iniciarTempo();
		
		this->detectarTodosEventos();

		this->desenharTudo();
		
		this->tela->renderizar();

		this->tempo->atrasarTempo();
		
		
	}

	//vector<Torre *> * vetorTorres;
	//vector<Movimentavel *> * vetorMovimentaveis;
	//vector<Wave *> * vetorMovimentaveis;

	return 0;	
}
