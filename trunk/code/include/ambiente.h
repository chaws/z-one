#ifndef AMBIENTE_H
#define AMBIENTE_H

#include <mapa.h>
#include <SDL/SDL.h>
#include <string>
#include <vector>

using namespace std;

class Ambiente
{
private:
	static const string CAMINHO_IMG;
	static const string CAMINHO_MAPAS;
	static const string CAMINHO_AUDIO;
	static const string CAMINHO_FONT;

public:
	static SDL_Surface * carregarImagem(string caminho);
	static vector<Tile> * carregarConfiguracaoMapa(string caminho);
};

#endif
