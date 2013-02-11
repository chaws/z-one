#ifndef AMBIENTE_H
#define AMBIENTE_H

#include <SDL/SDL.h>
#include <string>
#include <vector>

using namespace std;

class Ambiente
{
private:
	static string CAMINHO_IMG;
	static string CAMINHO_MAPAS;
	static string CAMINHO_AUDIO;
	static string CAMINHO_FONT;

public:
	static SDL_Surface * carregarImagem(string caminho);
	static vector<int> * carregarMapa(string caminho);
};

#endif
