#ifndef AMBIENTE_H
#define AMBIENTE_H

#include <SDL/SDL.h>
#include <string>

using namespace std;

class Ambiente
{
public:
	static SDL_Surface * carregarImagem(string caminho);

};

#endif
