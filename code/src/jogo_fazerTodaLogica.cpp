#include <jogo.h>
#include <hud.h>
#include <iostream>
#include <util.h>

int Jogo::fazerTodaLogica()
{	
	for(unsigned int i = 0; i < this->vetorMutaveis->size(); i++) 
		this->vetorMutaveis->at(i)->fazerLogica();
		
	if(this->wave) 
		this->wave->fazerLogica();
		
	if(this->wave->waveTerminou)
	{
		delete this->wave;
		
		if (Hud::numeradorWave == 10)
		{
			// ACABOU O MAPA, AQUI TEM QUE DAR UM JEITO DE TROCAR (mudar estado)
		} else
		{
			Hud::numeradorWave++;
			this->wave = new Wave(Hud::numeradorWave, this->vetorDesenhaveis, this->vetorMutaveis, this->mapa, this->mestre);
		}
	}
	
	return 0;
}
