#include <jogo.h>

int Jogo::desenharTudo()
{	
	for(unsigned int i = 0; i < vetorDesenhaveis->size(); i++)
		vetorDesenhaveis->at(i)->desenhar();
	return 0;
}
