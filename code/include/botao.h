#ifndef BOTAO_H
#define BOTAO_H

#include <escutavel.h>
#include <SDL/SDL.h>

#include <string>

using namespace std;

class Botao : public Escutavel
{
private:
	string rotulo;
	bool clicado;

public:

	// Construtores sem coordenadas: O CRIADOR DO BOTAO SE VIRA PARA POSICIONA-LO
	Botao(string rotulo);
	Botao(SDL_Surface * imagem);

	// Construtores mais complexos, contemplando as coordenadas do botao
	Botao(int x, int y, int w, int h, string rotulo);
	Botao(int x, int y, int w, int h, SDL_Surface * imagem);

	~Botao();

	int desenhar();
	int detectarEvento();
	bool foiClicado();
};

#endif
