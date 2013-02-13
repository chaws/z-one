#ifndef UTIL_H
#define UTIL_H

#include <desenhavel.h>
#include <mutavel.h>
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
	static int removerElementoVetorDesenhaveis(vector <Desenhavel *> *  vetor , Desenhavel * elemento);
	static int removerElementoVetorMutaveis(vector <Mutavel *> *  vetor , Desenhavel * elemento);
};

#endif
