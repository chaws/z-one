#include <iostream>
#include <vector>
#include <util.h>
#include <jogo.h>
#include <mapa.h>
#include <torre.h>
#include <inimigo.h>

using namespace std;

int Jogo::estadoJogando()
{
	
	this->vetorDesenhaveis =  new vector<Desenhavel *>;
	this->vetorEscutaveis =  new vector<Escutavel *>;
	this->vetorMutaveis =  new vector<Mutavel *>;
	
	// Coloca o mapa na jogada
	this->mapa = new Mapa(JARDIM_EXTERNO);
	this->vetorDesenhaveis->push_back(this->mapa);
	this->vetorEscutaveis->push_back(this->mapa);
	
	
	// Coloca o mestre na jogada
	this->mestre = new Mestre(this->mapa);
	this->vetorDesenhaveis->push_back(this->mestre);
	this->vetorMutaveis->push_back(this->mestre);

	// Coloca o hud na jogada
	this->vetorDesenhaveis->push_back(this->hud);
	this->vetorEscutaveis->push_back(this->hud);
	
	this->wave = new Wave(NORMAL, this->vetorDesenhaveis, this->vetorMutaveis, this->mapa, this->mestre);
	
	Torre * torreteste = new Torre(KATANA, 600, 400, this->wave, this->vetorDesenhaveis, this->vetorMutaveis);
	this->vetorDesenhaveis->push_back(torreteste);
	this->vetorMutaveis->push_back(torreteste);	
	
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

