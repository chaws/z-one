#include <jogo.h>
#include <ambiente.h>
#include <SDL/SDL.h>

int Jogo::estadoEntradaJogo()
{
	SDL_Surface * logo = Ambiente::carregarImagem("media/image/z_one_logo_800_600.png");
	int alpha = SDL_ALPHA_TRANSPARENT;
	const int ENTRY_FRAMES = 250;
	int incremento = 0;

	while(this->estadoJogo == ENTRADA_JOGO)
	{
		this->tempo->iniciarTempo();
		
		this->detectarTodosEventos();

	    SDL_SetAlpha(logo, SDL_SRCALPHA, alpha);
	    this->tela->aplicarSuperficie(logo);

	    if(incremento == 0)
	    	incremento = 1;
	    else
	    {
	    	incremento = 0;
	    	alpha++;
	    }

		this->tela->renderizar();

		this->tempo->atrasarTempo();
		
		if(alpha > ENTRY_FRAMES)
			this->estadoJogo = JOGANDO;
	}

	SDL_FreeSurface(logo);
	return 0;
}
