#include <torre.h>
#include <ataque.h>
#include <tela.h>
#include <mapa.h>
#include <util.h>
#include <ambiente.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

const int Torre::WIDTH = 40;
const int Torre::HEIGHT = 40;

Torre::Torre(TipoTorre tipo, int x, int y, Wave * waveAtual, vector<Desenhavel *> * vetorDesenhaveis, vector<Mutavel *> * vetorMutaveis)
{
	this->rect =  new SDL_Rect;
	this->rect->x=x;
	this->rect->y=y;
	this->rect->w=Torre::WIDTH;
	this->rect->h=Torre::HEIGHT;
	this->vetorAtaques =  new vector<Ataque *>;
	this->vetorInimigos = waveAtual->pegarVetorInimigos();
	this->alvo = NULL;
	this->estado = VIGIANDO;
	this->atirei=false;
	this->tipo = tipo;
	this->vetorDesenhaveis = vetorDesenhaveis;
	this->vetorMutaveis = vetorMutaveis;
	//Inicializando os dados de cada tipo de torre
	switch(this->tipo){
		case KATANA:
			this->imagem=Ambiente::carregarImagem("ninja_katana.png");
			this->ataque=Ambiente::carregarImagem("katana.png");
			this->alcance.x = x-(Torre::WIDTH/2);
			this->alcance.y = y-(Torre::HEIGHT/2);
			this->alcance.w = Torre::WIDTH*2;
			this->alcance.h = Torre::HEIGHT*2;
			this->DPS = 2;
			this->dano = 20;
			break;

		case BOMBA:
			this->imagem=Ambiente::carregarImagem("ninja_bomba.png");
			this->ataque=Ambiente::carregarImagem("bomba.png");
			this->alcance.x = x-Torre::WIDTH;
			this->alcance.y = y-Torre::HEIGHT;
			this->alcance.w = Torre::WIDTH*10;
			this->alcance.h = Torre::HEIGHT*10;
			this->DPS = 0.5;
			this->dano = 30;
			break;

		case SHURIKEN:
			this->imagem=Ambiente::carregarImagem("ninja_shuriken.png");
			this->ataque=Ambiente::carregarImagem("shuriken.png");
			this->alcance.x = x-Torre::WIDTH;
			this->alcance.y = y-Torre::HEIGHT;
			this->alcance.w = Torre::WIDTH*5;
			this->alcance.h = Torre::HEIGHT*5;
			this->DPS = 5;
			this->dano = 12;
			break;
		
		case KUNAI:
			this->imagem=Ambiente::carregarImagem("ninja_kunai.png");
			this->ataque=Ambiente::carregarImagem("kunai.png");
			this->alcance.x = x-Torre::WIDTH;
			this->alcance.y = y-Torre::HEIGHT;
			this->alcance.w = Torre::WIDTH*5;
			this->alcance.h = Torre::HEIGHT*5;
			this->DPS = 3;
			this->dano = 15;
			break;
		
		case NUNCHAKU:
			this->imagem=Ambiente::carregarImagem("ninja_nunchaku.png");
			this->ataque=Ambiente::carregarImagem("katana.png");
			this->alcance.x = x-(Torre::WIDTH/2);
			this->alcance.y = y-(Torre::HEIGHT/2);
			this->alcance.w = Torre::WIDTH*2;
			this->alcance.h = Torre::HEIGHT*2;
			this->DPS = 2;
			this->dano = 20;
			break;

		case MARIKI:
			this->imagem=Ambiente::carregarImagem("ninja_mariki.png");
			this->ataque=Ambiente::carregarImagem("katana.png");
			this->alcance.x = x-(Torre::WIDTH/2);
			this->alcance.y = y-(Torre::HEIGHT/2);
			this->alcance.w = Torre::WIDTH*2;
			this->alcance.h = Torre::HEIGHT*2;
			this->DPS = 3;
			this->dano = 15;
			break;
	}
	
	this->comecaAtacar= Tela::FPS / this->DPS;
	
}

Torre::~Torre()
{
	SDL_FreeSurface(this->imagem);
	SDL_FreeSurface(this->ataque);
}

int Torre::desenhar()
{
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
	return 0;
}

int Torre::detectarColisao()
{
	return 0;
}

int Torre::detectarEvento()
{
	return 0;
}


int Torre::realizarUpgrade()
{
	return 0;
}

bool Torre::estaMaisProximo(Inimigo * candidatoAlvo, Inimigo * alvoAtual)
{
	if (!alvoAtual)	
		return true;
	
	int distanciaCadidatoAlvo = pow(pow(Mapa::tileSaida.x - candidatoAlvo->rect->x-20, 2) +  pow(Mapa::tileSaida.y - candidatoAlvo->rect->y-20, 2), 0.5);
	int distanciaAlvoAtual = pow(pow(Mapa::tileSaida.x - alvoAtual->rect->x-20, 2) +  pow(Mapa::tileSaida.y - alvoAtual->rect->y-20, 2), 0.5);
	
	if (distanciaCadidatoAlvo < distanciaAlvoAtual)
		return true;
	else
		return false;
}

int Torre::fazerLogica()
{
	Inimigo * candidatoAlvo;
	
	if(this->estado == VIGIANDO)
	{
		for(unsigned int j = 0; j < vetorInimigos->size(); j++)
		{
			if(isInimigoProximo(vetorInimigos->at(j))){
				this->estado = ATACANDO;
				candidatoAlvo = vetorInimigos->at(j);
				
				if (estaMaisProximo(candidatoAlvo, this->alvo))
					this->alvo = vetorInimigos->at(j);
			}			
		}		
	} 
	if (this->estado == ATACANDO) 
	{ //arrumar essa criação de balas, tah alocando uma imagem pra cada bala
 		if ((comecaAtacar == Tela::FPS / this->DPS) )
 		{ 		
			Ataque * novoAtaque = new Ataque(this->ataque, this->rect->x+20, this->rect->y+20, this->alvo);
			this->vetorAtaques->push_back(novoAtaque);
			this->vetorDesenhaveis->push_back(novoAtaque);
			this->vetorMutaveis->push_back(novoAtaque); 
			this->alvo->pontosVida -= this->dano;
			comecaAtacar=0;
		}
		comecaAtacar++;
		//confere se o inimigo ainda esta proximo
		if(!this->alvo || this->alvo->estaMorto || !isInimigoProximo(this->alvo)){
			//se não estiver, para de atacar e perde o alvo
			this->estado = VIGIANDO;
			this->alvo = NULL;
			this->comecaAtacar = 0;
		}
		
	} 
	
	this->removerAtaquesTerminados();
		
	return 0;
}

int Torre::removerAtaquesTerminados()
{
	for(unsigned int i = 0; i < this->vetorAtaques->size(); i++) 
	{
		if (this->vetorAtaques->at(i)->cheguei)
		{
			
			Ataque * ataqueQueSeraDeletado = this->vetorAtaques->at(i);
			Util::removerElementoVetor(this->vetorDesenhaveis, ataqueQueSeraDeletado);
			Util::removerElementoVetor(this->vetorMutaveis, ataqueQueSeraDeletado);
			this->vetorAtaques->erase(this->vetorAtaques->begin() + i);
		}
	}
	
	return 0;
}


bool Torre::isInimigoProximo(Inimigo * inimigo)
{
	if(this->alcance.y >= inimigo->rect->y + inimigo->rect->h)
		return 0;
	if(this->alcance.x >= inimigo->rect->x + inimigo->rect->w)
		return 0;
	if(this->alcance.y + this->alcance.h <= inimigo->rect->y)
		return 0;
	if(this->alcance.x + this->alcance.w <= inimigo->rect->x)
		return 0;
		
	return 1;
}
