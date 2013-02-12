#include <iostream>
#include <vector>

#include <jogo.h>
#include <mapa.h>
#include <inimigo.h>

using namespace std;

int Jogo::estadoJogando()
{
	this->vetorMutaveis =  new vector <Mutavel *>;
	this->vetorDesenhaveis = new vector <Desenhavel *>;
	
	this->mapa = new Mapa(SALA_TREINAMENTO);
	
	this->vetorDesenhaveis->push_back(this->mapa);
	
	Inimigo * inimigoTeste = new Inimigo(SAQUEADOR, this->mapa);
	Inimigo * inimigoTeste2 = new Inimigo(SAQUEADOR, this->mapa);
	
	this->vetorDesenhaveis->push_back(inimigoTeste);
	
	this->vetorMutaveis->push_back(inimigoTeste);
	
	int espera;
	while(this->estadoJogo == JOGANDO)
	{
		if (espera == 90 )
		{
			this->vetorDesenhaveis->push_back(inimigoTeste2);
			this->vetorMutaveis->push_back(inimigoTeste2);
		}
			
		this->tempo->iniciarTempo();
		
		this->detectarTodosEventos();
		
		this->fazerTodaLogica();

		this->desenharTudo();
		
		this->tela->renderizar();

		this->tempo->atrasarTempo();
		espera++;
	}

	return 0;	
}

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
	

	//vector<Torre *> * vetorTorres;
	//vector<Movimentavel *> * vetorMovimentaveis;
	//vector<Wave *> * vetorMovimentaveis;

