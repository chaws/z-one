#include <jogo.h>
#include <ambiente.h>
#include <logofading.h>
#include <SDL/SDL.h>

int Jogo::estadoEntradaJogo()
{
	LogoFading * logoFading = new LogoFading();
	
	this->vetorDesenhaveis->push_back(logoFading);

	while(this->estadoJogo == ENTRADA_JOGO)
	{
		this->tempo->iniciarTempo();
		
		this->detectarTodosEventos();
		
		this->desenharTudo();
		
		this->tela->renderizar();

		this->tempo->atrasarTempo();
		
		if(logoFading->terminouFading())
		{
			this->estadoJogo = JOGANDO;
			delete logoFading;
		}
	}
	
	this->vetorDesenhaveis->pop_back();
	
	return 0;
}
