#ifndef UTIL_H
#define UTIL_H

#include <mutavel.h>
#include <desenhavel.h>
#include <escutavel.h>
#include <vector>

using namespace std;

enum EstadoJogo
{
	ENTRADA_JOGO,
	MENU_PRINCIPAL,
	JOGANDO,
	FIM_JOGO,
	SAIDA_APLICATIVO
};

class Util
{
public:
	static EstadoJogo estadoJogo;
	//static int removerElementoVetorDesenhaveis(vector <Desenhavel *> *  vetor , Desenhavel * elemento);
	//static int removerElementoVetorMutaveis(vector <Mutavel *> *  vetor , Desenhavel * elemento);
	
	template <class C>
	static void removerElementoVetor(vector<C *> * vetor, Desenhavel * desenhavel)
	{
		for(unsigned int i = 0; i < vetor->size(); i++)
			if(vetor->at(i) == desenhavel)
				vetor->erase(vetor->begin() + i);
	}
};

#endif
