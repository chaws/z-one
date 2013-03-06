#ifndef HUD_H
#define HUD_H

#include <escutavel.h>
#include <tela.h>
#include <botao.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class Hud : public Escutavel
{
private:
	// Dimensoes do retangulo superior
	static const int HEIGHT_PARTE_CIMA;
	static const int WIDTH_PARTE_CIMA;
	
	// Pontos
	static int pontosXP;
	static int pontosHP;

	// Serve para pegar os numeros e escrever na tela de forma formatada
	char informacoesTopo[256]; 

	// Esses dois abaixo servem para representar as waves que ja foram do total
	// Ex: 6/20, ja foram 6 de 20
	static int numeradorWave;
	static int denominadorWave;

	// Botoes de controle
	static Botao * botaoPausa;
	Botao * botaoProximaWave;

	// Botoes para adicionar torres
	Botao * botaoNinjaKatana;
	Botao * botaoNinjaNunchaku;
	Botao * botaoNinjaMariki;
	Botao * botaoNinjaShuriken;
	Botao * botaoNinjaKunai;
	Botao * botaoNinjaBomba;

	// Barra do hud
	SDL_Surface * barra;

	// Faz todas as configuracoes do Hud
	int configurarHud();
	void atualizarInformacoes();

public:
	Hud();
	~Hud();

	int desenhar();
	int detectarEvento();

	static void somarXP(int xp);
	static void atualizarHP(int pontosVidaMestre);
	static void setarQuantidadeWaves(int denominador);
	static void somarWave();
	static void resetarPontos();
	static void detectarEventoBotaoPause();
	static void desenharBotaoPause();
	
	// Dimensoes do retangulo inferior
	static const int HEIGHT_PARTE_BAIXO;
	static const int WIDTH_PARTE_BAIXO;
	static const int BORDA_DIREITA;
};

#endif
