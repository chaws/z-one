#include <jogo.h>
#include <SDL/SDL.h>

int Jogo::detectarSaidaAplicativo()
{
	if(Escutavel::evento.type == SDL_QUIT)
		this->estadoJogo = SAIDA_APLICATIVO;
	return 0;	
}
