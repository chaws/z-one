#include <wave.h>
#include <inimigo.h>
#include <desenhavel.h>
#include <mutavel.h>
#include <tela.h>
#include <util.h>
#include <mapa.h>
#include <hud.h>
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
	this->atraso = 0;
	this->indiceVetorInimigo = 0;
	
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
			this->quantidadeInimigos = 20;
			break;
	}
	this->vetorInimigos = new vector<Inimigo *>;
	int resto;
	for(int i = 0; i < this->quantidadeInimigos; i++)
	{
		// Deixar criação de inimigos aleatória
		resto = (TipoInimigo) i % 4;
		this->vetorInimigos->push_back(new Inimigo(resto, this->mapaAtual));

	}
		
	
}

int Wave::lancarInimigos()
{		
	if (this->atraso % this->intervaloCriacaoInimigos == 0 && this->indiceVetorInimigo < this->quantidadeInimigos)
	{
		this->vetorDesenhaveis->push_back(this->vetorInimigos->at(this->indiceVetorInimigo));
		this->vetorMutaveis->push_back(this->vetorInimigos->at(this->indiceVetorInimigo));
		(this->indiceVetorInimigo)++;
		this->atraso = 1;
	}
	return 0;
}

int Wave::removerInimigosMortos()
{
	for (unsigned int i = 0; i < this->vetorInimigos->size(); i++)
	{
		if(this->vetorInimigos->at(i)->estaMorto)
		{
			Inimigo * inimigoQueSeraDeletado = this->vetorInimigos->at(i);
			Util::removerElementoVetor(this->vetorDesenhaveis, inimigoQueSeraDeletado);
			Util::removerElementoVetor(this->vetorMutaveis, inimigoQueSeraDeletado);
				
			this->vetorInimigos->erase(vetorInimigos->begin() + i);

			
			
			
			if(inimigoQueSeraDeletado->pontosVida > 0 && this->mestreAtual)
			{
				this->mestreAtual->pontosVida--;
				Hud::atualizarHP(this->mestreAtual->pontosVida);
				if (this->mestreAtual->pontosVida == 0)
				{
					Util::removerElementoVetor(this->vetorDesenhaveis, this->mestreAtual);
					Util::removerElementoVetor(this->vetorMutaveis, this->mestreAtual);
					delete this->mestreAtual;
					Hud::resetarPontos();
					Util::estadoJogo = ENTRADA_JOGO;
				}
			} else { // Aqui quer dizer que ele morreu pq alguma torre matou
				Hud::somarXP(inimigoQueSeraDeletado->pontosExperiencia);
			}
			
			delete inimigoQueSeraDeletado;
			
			this->indiceVetorInimigo--;
			this->quantidadeInimigos--;
			
			break;
		}
			
	}
	
	return 0;
}

int Wave::fazerLogica()
{	
	this->lancarInimigos();
	this->removerInimigosMortos();
			
	this->atraso++;
	
	return 0;
}
