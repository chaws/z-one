#include <jogo.h>
#include <ambiente.h>
#include <logofading.h>
#include <SDL/SDL.h>

/*int Jogo::estadoEntradaJogo()
{
	SDL_Surface * logo = Ambiente::carregarImagem("z_one_logo_800_600.png");
	SDL_Rect offset = {0, 0, Tela::WIDTH, Tela::HEIGHT};
	
	int alpha = SDL_ALPHA_TRANSPARENT;
	const int DELAY_FRAMES_INCREMENTO_ALFA = 3;
	const int DELAY_FRAMES_INICIAR_INCREMENTO_ALFA = 15;
	int incremento = 0;

	while(this->estadoJogo == ENTRADA_JOGO)
	{
		this->tempo->iniciarTempo();
		
		this->detectarTodosEventos();

		// INIÍCIO - Parte de desenhar tudo
			if ( (incremento > DELAY_FRAMES_INICIAR_INCREMENTO_ALFA) && (incremento % DELAY_FRAMES_INCREMENTO_ALFA == 0))
			{
				SDL_SetAlpha(logo, SDL_SRCALPHA, alpha);
				alpha++;
				SDL_BlitSurface(logo, NULL, SDL_GetVideoSurface(), &offset);
			} 		
		// FIM - Parte de desenhar tudo
		
		this->tela->renderizar();

		this->tempo->atrasarTempo();
		
		incremento++;
		
		if(incremento == 180)
			this->estadoJogo = JOGANDO;
	}

	SDL_FreeSurface(logo);
	
	return 0;
}*/

int Jogo::estadoEntradaJogo()
{
	LogoFading * logoFading = new LogoFading();

	while(this->estadoJogo == ENTRADA_JOGO)
	{
		this->tempo->iniciarTempo();
		
		this->detectarTodosEventos();
		
		this->tela->renderizar();

		this->tempo->atrasarTempo();
		
		if(logoFading->terminouFading())
		{
			this->estadoJogo = JOGANDO;
			delete logoFading;
		}
	}
	
	return 0;
}
