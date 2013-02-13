#include <util.h>
#include <vector>

using namespace std;

EstadoJogo Util::estadoJogo = ENTRADA_JOGO;

int Util::removerElementoVetorDesenhaveis(vector <Desenhavel *> *  vetor , Desenhavel * elemento)
{
	for (unsigned int i = 0; i < vetor->size(); i++)
		if (vetor->at(i) == elemento)
		{
			vetor->erase(vetor->begin()+i);
			break;
		}

	return 0;
}
	
int Util::removerElementoVetorMutaveis(vector <Mutavel *> *  vetor , Desenhavel * elemento)
{
	for (unsigned int i = 0; i < vetor->size(); i++)
		if (vetor->at(i) == elemento)
		{
			vetor->erase(vetor->begin()+i);
			break;
		}

	return 0;
}

template <class V>
int Util::removerElementoVetor(V vetor, Desenhavel * desenhavel)
{
	for(unsigned int i = 0; i < vetor->size(); i++)
		if(vetor->at(i) == desenhavel)
			vetor->erase(vetor->begin() + i);
}
	

