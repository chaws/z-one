#include <hud.h>
#include <ambiente.h>
#include <mapa.h>
#include <tela.h>
#include <botao.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

// const int Hud::HEIGHT_PARTE_CIMA 	= Tela::HEIGHT * 0.1;
//const int Hud::HEIGHT_PARTE_BAIXO 	= Tela::HEIGHT * 0.1; -> assim fica pouco mais indepentene
const int Hud::HEIGHT_PARTE_CIMA 	= Mapa::TILE_HEIGHT;
const int Hud::WIDTH_PARTE_CIMA 	= Tela::WIDTH;
const int Hud::HEIGHT_PARTE_BAIXO 	= Mapa::TILE_HEIGHT;
const int Hud::WIDTH_PARTE_BAIXO 	= Tela::WIDTH;
int Hud::pontosXP = 0;
int Hud::pontosHP = 0;
int Hud::numeradorWave = 0;
int Hud::denominadorWave = 0;

Hud::Hud()
{
	// Evitando lixo
	Hud::resetarPontos();
	// Iniciando botoes de cima
	this->botaoPausa = new Botao("Pausa");
	this->botaoProximaWave = new Botao("Prox");

	// Iniciando os botoes de baixo
	this->botaoNinjaKatana 	 = new Botao(Ambiente::carregarImagem("botao_ninja_katana.png"));
	this->botaoNinjaNunchaku = new Botao(Ambiente::carregarImagem("botao_ninja_nunchaku.png"));
	this->botaoNinjaMariki 	 = new Botao(Ambiente::carregarImagem("botao_ninja_mariki.png"));
	this->botaoNinjaShuriken = new Botao(Ambiente::carregarImagem("botao_ninja_shuriken.png"));
	this->botaoNinjaKunai 	 = new Botao(Ambiente::carregarImagem("botao_ninja_kunai.png"));
	this->botaoNinjaBomba 	 = new Botao(Ambiente::carregarImagem("botao_ninja_bomba.png"));

	// Arruma a bagaca toda
	this->rect = new SDL_Rect;
	this->rect->x = 0;
	this->rect->y = 0;
	this->configurarHud();
}

Hud::~Hud()
{
	if(this->barra) 				delete this->barra;
	if(this->botaoNinjaNunchaku)	delete this->botaoNinjaNunchaku;
	if(this->botaoNinjaMariki)		delete this->botaoNinjaMariki;
	if(this->botaoNinjaShuriken)	delete this->botaoNinjaShuriken;
	if(this->botaoNinjaKunai)		delete this->botaoNinjaKunai;
	if(this->botaoNinjaBomba)		delete this->botaoNinjaBomba;
}

int Hud::configurarHud()
{
    this->imagem = SDL_CreateRGBSurface(0, Tela::WIDTH, Tela::HEIGHT, Tela::BPP, 0, 0, 0, 0);

	// Insere as duas barras
	this->barra = Ambiente::carregarImagem("gui.png");
	
	// Coloca os botoes em baixo
	int bordaDireita = 10;
	this->botaoNinjaKatana->rect->y = Tela::HEIGHT - Hud::HEIGHT_PARTE_BAIXO;
	this->botaoNinjaKatana->rect->x = bordaDireita;

	this->botaoNinjaNunchaku->rect->x = this->botaoNinjaKatana->rect->x + this->botaoNinjaKatana->rect->w + bordaDireita;
	this->botaoNinjaNunchaku->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaMariki->rect->x = this->botaoNinjaNunchaku->rect->x + this->botaoNinjaNunchaku->rect->w + bordaDireita;
	this->botaoNinjaMariki->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaShuriken->rect->x = this->botaoNinjaMariki->rect->x + this->botaoNinjaMariki->rect->w + bordaDireita;
	this->botaoNinjaShuriken->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaKunai->rect->x = this->botaoNinjaShuriken->rect->x + this->botaoNinjaShuriken->rect->w + bordaDireita;
	this->botaoNinjaKunai->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaBomba->rect->x = this->botaoNinjaKunai->rect->x + this->botaoNinjaKunai->rect->w + bordaDireita;
	this->botaoNinjaBomba->rect->y = this->botaoNinjaKatana->rect->y;

	// Coloca a colorkey para mostrar o mapa, que fica atras do hud
	Uint32 colorkey = SDL_MapRGB(this->imagem->format, 0, 0, 0);
	SDL_SetColorKey(this->imagem, SDL_SRCCOLORKEY, colorkey); 

	return 0;
}

void Hud::atualizarInformacoes()
{
	// Formata os numeros dentro de uma soh string
	sprintf(informacoesTopo, "XP %09i   HP %02i   WV %02i/%02i", 
		Hud::pontosXP, Hud::pontosHP, Hud::numeradorWave, Hud::denominadorWave);
	//cout << informacoesTopo << endl;
	SDL_Surface * textoHUD = Ambiente::carregarTexto(string(informacoesTopo));
	SDL_Rect retangulo = {10, 5, 0, 0};

	SDL_BlitSurface(textoHUD, NULL, SDL_GetVideoSurface(), &retangulo);
	
	SDL_FreeSurface(textoHUD);
}

int Hud::desenhar()
{
	SDL_Rect parteCima = {0, 0, Hud::WIDTH_PARTE_CIMA, Hud::HEIGHT_PARTE_CIMA};
	SDL_Rect parteBaixo = {0, Tela::HEIGHT - Hud::HEIGHT_PARTE_BAIXO, 
								Hud::WIDTH_PARTE_BAIXO, Hud::HEIGHT_PARTE_BAIXO};

	SDL_BlitSurface(this->barra, NULL, this->imagem, &parteCima);
	SDL_BlitSurface(this->barra, NULL, this->imagem, &parteBaixo);
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
	
	this->atualizarInformacoes();
	this->botaoNinjaKatana->desenhar();
	this->botaoNinjaKunai->desenhar();
	this->botaoNinjaShuriken->desenhar();
	this->botaoNinjaMariki->desenhar();
	this->botaoNinjaNunchaku->desenhar();
	this->botaoNinjaBomba->desenhar();
	return 0;
}

int Hud::detectarEvento()
{
	this->botaoNinjaKatana->detectarEvento();
	this->botaoNinjaKunai->detectarEvento();
	this->botaoNinjaShuriken->detectarEvento();
	this->botaoNinjaMariki->detectarEvento();
	this->botaoNinjaNunchaku->detectarEvento();
	this->botaoNinjaBomba->detectarEvento();
	return 0;
}

void Hud::somarXP(int xp)
{
	Hud::pontosXP += xp;
}

void Hud::atualizarHP(int pontosVidaMestre)
{
	Hud::pontosHP = pontosVidaMestre;
}

void Hud::setarQuantidadeWaves(int denominador)
{
	Hud::denominadorWave = denominador;
}

void Hud::somarWave()
{
	Hud::numeradorWave++;
}

void Hud::resetarPontos()
{
	Hud::pontosXP = 0;
	Hud::pontosHP = 10;
	Hud::numeradorWave = 0;
	Hud::denominadorWave = 0;
}
