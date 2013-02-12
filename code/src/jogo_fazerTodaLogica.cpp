#include <jogo.h>
#include <iostream>

int Jogo::fazerTodaLogica()
{	
	for(unsigned int i = 0; i < this->vetorMutaveis->size(); i++) 
		this->vetorMutaveis->at(i)->fazerLogica();
	return 0;
}
