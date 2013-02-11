#include <jogo.h>
#include <SDL/SDL.h>

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
