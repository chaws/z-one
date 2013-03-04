#include <jogo.h>
#include <tela.h>
#include <tempo.h>
#include <hud.h>
#include <iostream>
#include <escutavel.h>
#include <ambiente.h>
#include <util.h>

using namespace std;

Jogo::Jogo()
{
	this->tela =  new Tela;
	this->tempo = new Tempo;
	this->hud =   new Hud;
}

Jogo::~Jogo()
{
	if(this->tela) delete this->tela;
	if(this->tempo) delete this->tempo;
	if(this->hud) delete this->hud;
	if(this->vetorDesenhaveis) delete this->vetorDesenhaveis;
	if(this->vetorEscutaveis) delete this->vetorEscutaveis;
	if(this->vetorMutaveis) delete this->vetorMutaveis;
}

int Jogo::rodar()
{
	do 
	{
		switch(Util::estadoJogo)
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
	} while(Util::estadoJogo != SAIDA_APLICATIVO);
	
	this->estadoSairAplicativo();
	return 0;	
}
