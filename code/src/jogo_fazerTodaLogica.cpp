#include <jogo.h>
#include <hud.h>
#include <iostream>
#include <util.h>

int Jogo::fazerTodaLogica()
{	
	for(unsigned int i = 0; i < this->vetorMutaveis->size(); i++) 
		this->vetorMutaveis->at(i)->fazerLogica();
		
	if( Util::estadoInterno != TRANSICAO_WAVE && this->wave) 
		this->wave->fazerLogica();
		
	if(this->hud)
		this->hud->fazerLogica();
		
	if(this->wave->waveTerminou)
	{
		delete this->wave;
		
		if (Hud::numeradorWave == 10) // 
		{
			// ACABOU O MAPA, AQUI TEM QUE DAR UM JEITO DE TROCAR (mudar estado)
			delete this->vetorDesenhaveis;
			delete this->vetorMutaveis;
			delete this->vetorEscutaveis;
			delete this->mestre;
			delete this->mapa;
			Util::mapaAtual = (TipoMapa) (Util::mapaAtual + 1);
			this->estadoJogando();
		} else
		{
			Util::estadoInterno = TRANSICAO_WAVE;
			Hud::numeradorWave++;
			this->wave = new Wave(Hud::numeradorWave, this->vetorDesenhaveis, this->vetorMutaveis, this->mapa, this->mestre);
		}
	}
	
	return 0;
}
