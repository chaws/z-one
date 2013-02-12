#include <SDL/SDL.h>
#include <inimigo.h>
#include <mapa.h>
#include <iostream>
#include <ambiente.h>
#include <stdlib.h>

using namespace std;

Inimigo::Inimigo(int tipo,  Mapa * mapaAtual)
{
	this->mapaAtual = mapaAtual;
	this->rect = new SDL_Rect;
	this->rect->w = Mapa::TILE_WIDTH;			
	this->rect->h = Mapa::TILE_HEIGHT;
	this->tileAtual = this->tileAnterior = mapaAtual->tileEntrada;
	this->rect->x = this->tileAtual.x * (Mapa::TILE_WIDTH);
	this->rect->y = this->tileAtual.y * Mapa::TILE_HEIGHT;
	this->recemCriado = true;	
	this->pixelsAndados = Mapa::TILE_WIDTH;
	
	switch(tipo)
	{
		case CAPITAO:
			this->tipo = CAPITAO;
			this->imagem = Ambiente::carregarImagem("pirata_capitao_40_40.png");
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			this->velocidade = 2;
			break;

		case SAQUEADOR:
			this->tipo = SAQUEADOR;
			this->imagem = Ambiente::carregarImagem("pirata_saqueador_40_40.png");			
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			this->velocidade = 2;
			break;

		case CORSARIO:
			this->tipo = CORSARIO;
			this->imagem = Ambiente::carregarImagem("pirata_corsario_40_40.png");
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			this->velocidade = 2;
			break;

		case PERNA_DE_PAU:
			this->tipo = PERNA_DE_PAU;
			this->imagem = Ambiente::carregarImagem("pirata_pernadepau_40_40.png");
			this->pontosVida = 100;
			this->pontosExperiencia = 200;
			this->velocidade = 2;
			break;
	}
	
	
}

Inimigo::~Inimigo()
{
	delete this->imagem;
	delete this->rect;
}

int Inimigo::setarProximaPosicao()
{
	srand(SDL_GetTicks());
	
	bool caminhos[4];
	int proximaTile[4];
	int chavesEscolhidas[3];
	int caminhosPossiveis;
	int posicaoAnterior;
	int i;
	int chaveEscolhida;
	int novaTileX;
	int novaTileY;
	
	proximaTile[0] = ((this->tileAtual.y - 1) * Mapa::TILES_POR_LINHA) + this->tileAtual.x; 						// cima
	proximaTile[1] = ((this->tileAtual.y + 1) * Mapa::TILES_POR_LINHA) + this->tileAtual.x,							// abaixo
	proximaTile[2] = (this->tileAtual.y * Mapa::TILES_POR_LINHA) + (this->tileAtual.x - 1),							// esquerda
	proximaTile[3] = (this->tileAtual.y * Mapa::TILES_POR_LINHA) + (this->tileAtual.x + (!this->recemCriado ? 1 : 0));	// direita
	
	caminhos[0] = caminhos[1] = caminhos[2] = caminhos[3] = false;
	chavesEscolhidas[0] = chavesEscolhidas[1] = chavesEscolhidas[2] = -1;
	caminhosPossiveis = 0;
	posicaoAnterior = (this->tileAnterior.y * Mapa::TILES_POR_LINHA) + (this->tileAnterior.x);
	
	for(i = 0; i < 4; i++)
	{
		if(posicaoAnterior != proximaTile[i])
		{
			caminhos[i] = ehCaminho(proximaTile[i]);
		}

		if(caminhos[i])
			chavesEscolhidas[caminhosPossiveis++] = i;
	}
	
	chaveEscolhida = rand() % caminhosPossiveis;
	
	novaTileX = proximaTile[chavesEscolhidas[chaveEscolhida]] % Mapa::TILES_POR_LINHA;
	novaTileY = proximaTile[chavesEscolhidas[chaveEscolhida]] / Mapa::TILES_POR_LINHA;
	
	this->deltaX = (novaTileX - this->tileAtual.x) * this->velocidade; 
	this->deltaY = (novaTileY - this->tileAtual.y) * this->velocidade;
	
	this->tileAnterior = this->tileAtual;
	this->tileAtual.x = novaTileX;
	this->tileAtual.y = novaTileY;
	
	this->recemCriado = false;	
	
	return 0;
}

bool Inimigo::ehCaminho(int posicao)
{
	if (this->mapaAtual->tiles->at(posicao) == SAIDA)
		this->estaMorto = true;
	
	return this->mapaAtual->tiles->at(posicao) == CAMINHO;
}

int Inimigo::desenhar()
{
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
	return 0;
}

int Inimigo::fazerLogica()
{	
	cout << "endereco: " << this << "\t this->pixelsAndados: " << this->pixelsAndados << endl;
		
	if(this->pixelsAndados >= Mapa::TILE_WIDTH)
	{		
		this->setarProximaPosicao();
		this->pixelsAndados = 0;
	}
		
	this->rect->y += this->deltaY;
	this->rect->x += this->deltaX;
	
	this->pixelsAndados += this->velocidade;
	
	return 0;
}

void Inimigo::tremer()
{
	static bool sentido = true;
	sentido = !sentido;
		
	if(this->deltaX)
		this->deltaY = sentido ? 2 : -2;
	else
		this->deltaX = sentido ? 2 : -2;
}

int Inimigo::detectarColisao()
{
	return 0;
}
