#include <jogo.h>
#include <iostream>
#include <escutavel.h>
#include <ambiente.h>

using namespace std;

Jogo::Jogo()
{
	this->estadoJogo = ENTRADA_JOGO;
	this->tela = new Tela();
	this->tempo = new Tempo();
	this->vetorDesenhaveis =  new vector<Desenhavel *>;
	this->vetorMovimentaveis =  new vector<Movimentavel *>;
	this->vetorEscutaveis =  new vector<Escutavel *>;
}

Jogo::~Jogo()
{
	delete tela;
}

int Jogo::rodar()
{
	
	do {
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

int Jogo::estadoEntradaJogo()
{
	SDL_Surface * logo = Ambiente::carregarImagem("media/image/z_one_logo_800_600.png");
	int alpha = SDL_ALPHA_TRANSPARENT;
	const int ENTRY_FRAMES = 250;
		
	while(this->estadoJogo == ENTRADA_JOGO)
	{
		this->tempo->iniciarTempo();
		
	    SDL_SetAlpha(logo, SDL_SRCALPHA, alpha);
	    this->tela->aplicarSuperficie(logo);
	    alpha++;
	
		this->detectarTodosEventos();
		this->tempo->atrasarTempo();
		
		if(alpha > ENTRY_FRAMES)
			this->estadoJogo = MENU_PRINCIPAL;
	}

	SDL_FreeSurface(logo);
	return 0;
}

int Jogo::detectarSaidaAplicativo()
{
	 if(Escutavel::evento.type == SDL_QUIT)
		this->estadoJogo = SAIDA_APLICATIVO;
	
	return 0;	
}

int Jogo::detectarTodosEventos()
{	
	while(SDL_PollEvent(&Escutavel::evento))	
	{
		for(unsigned int i = 0; i < vetorEscutaveis->size(); i++)
			vetorEscutaveis->at(i)->detectarEvento();

		detectarSaidaAplicativo();
	}
	return 0;
}

int Jogo::estadoJogando()
{
	return 0;	
}

int Jogo::estadoFimJogo()
{
	return 0;	
}

int Jogo::estadoMenuJogo()
{
	return 0;	
}

int Jogo::estadoSairAplicativo()
{
	return 0;	
}
