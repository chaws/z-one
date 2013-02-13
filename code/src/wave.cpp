#include <wave.h>
#include <inimigo.h>
#include <desenhavel.h>
#include <mutavel.h>
#include <tela.h>
#include <util.h>
#include <mapa.h>
#include <vector>
#include <iostream>

using namespace std;

Wave::Wave(IDWave idWave, vector<Desenhavel *> * vetorDesenhaveis, vector<Mutavel *> * vetorMutaveis, Mapa * mapaAtual, Mestre *mestreAtual)
{
	this->idWave = idWave;
	this->mapaAtual = mapaAtual;
	this->mestreAtual = mestreAtual;
	this->vetorDesenhaveis = vetorDesenhaveis;
	this->vetorMutaveis = vetorMutaveis;
	
	this->configurarWave();
}

Wave::~Wave()
{
	delete this->vetorInimigos;
}

void Wave::configurarWave()
{
	switch(this->idWave)
	{
		case NORMAL:
			this->intervaloCriacaoInimigos = 0.5 * Tela::FPS;
			this->quantidadeInimigos = 100;
			break;
	}
	this->vetorInimigos = new vector<Inimigo *>;
	for(int i = 0; i < this->quantidadeInimigos; i++)
	{
		// Deixar criação de inimigos aleatória
		if (i % 2 == 0)
			this->vetorInimigos->push_back(new Inimigo(CORSARIO, this->mapaAtual));
		else
			this->vetorInimigos->push_back(new Inimigo(CAPITAO, this->mapaAtual));
	}
		
	
}

int Wave::lancarInimigos(int * atraso, int * indiceVetorInimigo)
{		
	if (*atraso % this->intervaloCriacaoInimigos == 0 && *indiceVetorInimigo < this->quantidadeInimigos)
	{
		this->vetorDesenhaveis->push_back(this->vetorInimigos->at(*indiceVetorInimigo));
		this->vetorMutaveis->push_back(this->vetorInimigos->at(*indiceVetorInimigo));
		(*indiceVetorInimigo)++;
		*atraso = 1;
	}
	return 0;
}

int Wave::removerInimigosMortos(int  * indiceVetorInimigo)
{
	for (unsigned int i = 0; i < this->vetorInimigos->size(); i++)
	{
		if(this->vetorInimigos->at(i)->estaMorto)
		{
			Inimigo * inimigoQueSeraDeletado = this->vetorInimigos->at(i);
			/*for (unsigned int j = 0; j < this->vetorDesenhaveis->size(); j++)
				if (this->vetorDesenhaveis->at(j) == inimigoQueSeraDeletado)
				{
					this->vetorDesenhaveis->erase(vetorDesenhaveis->begin()+j);
					break;
				}
				
			for (unsigned int j = 0; j < this->vetorMutaveis->size(); j++)
				if (this->vetorMutaveis->at(j) == inimigoQueSeraDeletado)
				{
					this->vetorMutaveis->erase(vetorMutaveis->begin()+j);
					break;
				} 
			*/
			
			Util::removerElementoVetorDesenhaveis(this->vetorDesenhaveis, inimigoQueSeraDeletado);
			Util::removerElementoVetorMutaveis(this->vetorMutaveis, inimigoQueSeraDeletado);
				
			this->vetorInimigos->erase(vetorInimigos->begin() + i);
			
			if (inimigoQueSeraDeletado->pontosVida > 0)
			{
				if (this->mestreAtual)
				{
					this->mestreAtual->pontosVida--;
					if (this->mestreAtual->pontosVida == 0)
					{
						Util::removerElementoVetorDesenhaveis(this->vetorDesenhaveis, this->mestreAtual);
						Util::removerElementoVetorMutaveis(this->vetorMutaveis, this->mestreAtual);
						delete this->mestreAtual;
						Util::estadoJogo = ENTRADA_JOGO;
					}
				}	
			}
			
			delete inimigoQueSeraDeletado;
			
			(*indiceVetorInimigo)--;
			this->quantidadeInimigos--;
			
			break;
		}
			
	}
	
	return 0;
}

int Wave::fazerLogica()
{
	static int atraso = 0;
	static int indiceVetorInimigo = 0;
	
	this->lancarInimigos(&atraso, &indiceVetorInimigo);
	this->removerInimigosMortos(&indiceVetorInimigo);
			
	atraso++;
	
	return 0;
}
