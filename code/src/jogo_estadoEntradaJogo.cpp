#include <jogo.h>
#include <util.h>
#include <ambiente.h>
#include <logofading.h>
#include <SDL/SDL.h>

int Jogo::estadoEntradaJogo()
{	
	this->vetorDesenhaveis =  new vector<Desenhavel *>;
	this->vetorEscutaveis =  new vector<Escutavel *>;
	this->vetorMutaveis =  new vector<Mutavel *>;

	LogoFading * logoFading = new LogoFading();	
		
	this->vetorDesenhaveis->push_back(logoFading);

	while(Util::estadoJogo == ENTRADA_JOGO)
	{
		this->tempo->iniciarTempo();
		
		this->detectarTodosEventos();
		
		this->desenharTudo();
		
		this->tela->renderizar();

		this->tempo->atrasarTempo();
		
		if(logoFading->terminouFading())
		{
			Util::estadoJogo = MENU_PRINCIPAL;
			delete logoFading;
		}
	}
	
	this->vetorDesenhaveis->pop_back();
	
	return 0;
}
