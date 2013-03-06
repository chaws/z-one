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
const int Hud::BORDA_DIREITA 		= 10;
int Hud::pontosXP = 0;
int Hud::pontosHP = 10;
int Hud::numeradorWave = 0;
int Hud::denominadorWave = 0;
Botao * Hud::botaoPausa;


Hud::Hud()
{
	// Iniciando botoes de cima
	Hud::botaoPausa = new Botao(Ambiente::carregarImagem("botao_pause2.png"), BOTAO_PAUSE);
	//this->botaoProximaWave = new Botao(Ambiente::carregarImagem("botao_musica.png"));

	// Iniciando os botoes de baixo
	this->botaoNinjaKatana 	 = new Botao(Ambiente::carregarImagem("botao_ninja_katana.png"),BOTAO_KATANA);
	this->botaoNinjaNunchaku = new Botao(Ambiente::carregarImagem("botao_ninja_nunchaku.png"),BOTAO_NUNCHAKU);
	this->botaoNinjaMariki 	 = new Botao(Ambiente::carregarImagem("botao_ninja_mariki.png"),BOTAO_MARIKI);
	this->botaoNinjaShuriken = new Botao(Ambiente::carregarImagem("botao_ninja_shuriken.png"),BOTAO_SHURIKEN);
	this->botaoNinjaKunai 	 = new Botao(Ambiente::carregarImagem("botao_ninja_kunai.png"),BOTAO_KUNAI);
	this->botaoNinjaBomba 	 = new Botao(Ambiente::carregarImagem("botao_ninja_bomba.png"),BOTAO_BOMBA);

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
	SDL_Rect retanguloParaTransparencia = {0, 0, Tela::WIDTH, Tela::HEIGHT};
	SDL_FillRect(this->imagem, &retanguloParaTransparencia, SDL_MapRGB(this->imagem->format, 0xFF, 0, 0xFF));
	
	// Insere as duas barras
	this->barra = Ambiente::carregarImagem("menu.png");
	
	//this->botaoProximaWave->rect->x = 600;
	//this->botaoProximaWave->rect->y = 0;
	Hud::botaoPausa->rect->x = 750;
	Hud::botaoPausa->rect->y = 0;
	
	// Coloca os botoes em baixo
	this->botaoNinjaKatana->rect->y = Tela::HEIGHT - Hud::HEIGHT_PARTE_BAIXO;
	this->botaoNinjaKatana->rect->x = Hud::BORDA_DIREITA;

	this->botaoNinjaNunchaku->rect->x = this->botaoNinjaKatana->rect->x + this->botaoNinjaKatana->rect->w + Hud::BORDA_DIREITA;
	this->botaoNinjaNunchaku->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaMariki->rect->x = this->botaoNinjaNunchaku->rect->x + this->botaoNinjaNunchaku->rect->w + Hud::BORDA_DIREITA;
	this->botaoNinjaMariki->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaShuriken->rect->x = this->botaoNinjaMariki->rect->x + this->botaoNinjaMariki->rect->w + Hud::BORDA_DIREITA;
	this->botaoNinjaShuriken->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaKunai->rect->x = this->botaoNinjaShuriken->rect->x + this->botaoNinjaShuriken->rect->w + Hud::BORDA_DIREITA;
	this->botaoNinjaKunai->rect->y = this->botaoNinjaKatana->rect->y;

	this->botaoNinjaBomba->rect->x = this->botaoNinjaKunai->rect->x + this->botaoNinjaKunai->rect->w + Hud::BORDA_DIREITA;
	this->botaoNinjaBomba->rect->y = this->botaoNinjaKatana->rect->y;

	// Coloca a colorkey para mostrar o mapa, que fica atras do hud
	Uint32 colorkey = SDL_MapRGB(this->imagem->format, 0xFF, 0, 0xFF);
	SDL_SetColorKey(this->imagem, SDL_SRCCOLORKEY, colorkey); 

	return 0;
}

void Hud::atualizarInformacoes()
{
	sprintf(informacoesTopo, "XP %08i", Hud::pontosXP);
	SDL_Surface * textoXP = Ambiente::carregarTexto(string(informacoesTopo));
	SDL_Rect retanguloXP = {10, 10, 0, 0};

	sprintf(informacoesTopo, "HP %02i", Hud::pontosHP);
	SDL_Surface * textoHP = Ambiente::carregarTexto(string(informacoesTopo));
	SDL_Rect retanguloHP = {245, 10, 0, 0};
	
	sprintf(informacoesTopo, "WAVE %02i/%02i", Hud::numeradorWave, Hud::denominadorWave);
	SDL_Surface * textoWV = Ambiente::carregarTexto(string(informacoesTopo));
	SDL_Rect retanguloWV = {350, 10, 0, 0};
	
	SDL_BlitSurface(textoXP, NULL, SDL_GetVideoSurface(), &retanguloXP);
	SDL_BlitSurface(textoHP, NULL, SDL_GetVideoSurface(), &retanguloHP);
	SDL_BlitSurface(textoWV, NULL, SDL_GetVideoSurface(), &retanguloWV);
	
	SDL_FreeSurface(textoXP);
	SDL_FreeSurface(textoHP);
	SDL_FreeSurface(textoWV);
}

int Hud::desenhar()
{
	SDL_Rect parteCima = {0, 0, Hud::WIDTH_PARTE_CIMA, Hud::HEIGHT_PARTE_CIMA};
	SDL_Rect parteBaixo = {0, Tela::HEIGHT - Hud::HEIGHT_PARTE_BAIXO, 
								Hud::WIDTH_PARTE_BAIXO, Hud::HEIGHT_PARTE_BAIXO};

	SDL_BlitSurface(this->barra, NULL, this->imagem, &parteCima);
	SDL_BlitSurface(this->barra, NULL, this->imagem, &parteBaixo);
	SDL_BlitSurface(this->imagem, NULL, SDL_GetVideoSurface(), this->rect);
	
	//this->botaoProximaWave->desenhar();
	Hud::botaoPausa->desenhar();
	
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
	Hud::botaoPausa->detectarEvento();
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

void Hud::desenharBotaoPause()
{
	Hud::botaoPausa->desenhar();
}

void Hud::detectarEventoBotaoPause()
{
	Hud::botaoPausa->detectarEvento();
}
