#include <iostream>
#include <vector>
#include <util.h>
#include <jogo.h>
#include <hud.h>
#include <mapa.h>
#include <tela.h>
#include <torre.h>
#include <inimigo.h>

using namespace std;

int Jogo::estadoJogandoPausado()
{	 
	while(SDL_PollEvent(&Escutavel::evento))
	{
		detectarSaidaAplicativo();
		Hud::botaoPausa->detectarEvento();
		if (Hud::botaoPausa->foiClicado())
			Util::trocarEstadoInterno(Util::ultimoEstadoInterno);
	}

	// Tem que arrumar isso aqui
	SDL_Surface * transparecerTela = SDL_CreateRGBSurface(0, Tela::WIDTH, Tela::HEIGHT, Tela::BPP, 0, 0, 0, 0);
	SDL_Rect rectTransparecerTela = {0, 0, Tela::WIDTH, Tela::HEIGHT};
	SDL_FillRect(transparecerTela,&rectTransparecerTela, SDL_MapRGB(transparecerTela->format,33,83,112));
	SDL_SetAlpha(transparecerTela, SDL_SRCALPHA, 1);
	SDL_BlitSurface(transparecerTela, NULL, SDL_GetVideoSurface(), &rectTransparecerTela);
	
	SDL_FreeSurface(transparecerTela);
	
	Hud::botaoPausa->desenhar();
				
	return 0;	
}

