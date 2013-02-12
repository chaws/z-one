#include <jogo.h>
#include <iostream>
#include <escutavel.h>
#include <ambiente.h>

using namespace std;

Jogo::Jogo()
{
	this->estadoJogo = JOGANDO;
	this->tela = new Tela;
	this->tempo = new Tempo;
	this->vetorDesenhaveis =  new vector<Desenhavel *>;
	this->vetorEscutaveis =  new vector<Escutavel *>;
	this->vetorMutaveis =  new vector<Mutavel *>;
}

Jogo::~Jogo()
{
	if(this->tela) delete this->tela;
	if(this->tempo) delete this->tempo;
	if(this->vetorDesenhaveis) delete this->vetorDesenhaveis;
	if(this->vetorEscutaveis) delete this->vetorEscutaveis;
	if(this->vetorMutaveis) delete this->vetorMutaveis;
}

int Jogo::rodar()
{
	do 
	{
		switch(estadoJogo)
		{
			case ENTRADA_JOGO:
				this->estadoEntradaJogo();
				break;
			
			case MENU_PRINCIPAL:
				this->estadoMenuJogo();
				break;
			
			case JOGANDO:
				this->estadoJogando();
				break;
			
			case FIM_JOGO:
				this->estadoFimJogo();
				break;
				
			case SAIDA_APLICATIVO:
				this->estadoFimJogo();
				break;
		}
	} while(estadoJogo != SAIDA_APLICATIVO);
	
	this->estadoSairAplicativo();
	return 0;	
}
