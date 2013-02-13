#include <jogo.h>
#include <iostream>
#include <util.h>

int Jogo::fazerTodaLogica()
{	
	for(unsigned int i = 0; i < this->vetorMutaveis->size(); i++) 
		this->vetorMutaveis->at(i)->fazerLogica();
		
	if(this->wave) 
		this->wave->fazerLogica();
	
	return 0;
}
