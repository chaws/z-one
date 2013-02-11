#include <jogo.h>

int Jogo::desenharTudo()
{	
	for(unsigned int i = 0; i < this->vetorDesenhaveis->size(); i++)
		this->vetorDesenhaveis->at(i)->desenhar();
	return 0;
}
