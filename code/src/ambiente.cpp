#include <ambiente.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string Ambiente::CAMINHO_IMG = "media/image/";
string Ambiente::CAMINHO_MAPAS = "media/maps/";
string Ambiente::CAMINHO_AUDIO = "media/audio/";
string Ambiente::CAMINHO_FONT = "media/font/";

SDL_Surface * Ambiente::carregarImagem(string caminho)
{
	caminho = Ambiente::CAMINHO_IMG + caminho;

	SDL_Surface * loadedImage = NULL;
	SDL_Surface * optimizedImage =  NULL;
	loadedImage = IMG_Load(caminho.c_str());

	if(!loadedImage)
	{
		cout << "Erro ao abrir: " << SDL_GetError() << endl;
		return NULL;
	}

    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    
    return optimizedImage;
}

vector<int> * Ambiente::carregarMapa(string caminho)
{
	caminho = Ambiente::CAMINHO_MAPAS + caminho;
	vector<int> * retorno = new vector<int>;
	string linha;
  	ifstream arquivo(caminho); // ifstream = padrão ios:in
	if (arquivo.is_open())
	{
		while (!arquivo.eof() ) //enquanto end of file for false continua
		{
			getline (arquivo, linha);
			for(unsigned int i = 0; i < linha.length(); i++)
				if(linha.at(i) != ' ')
					retorno.push_back(linha.at(i) - 30) // o 30 veio da tabela ASCII;
		}
		arquivo.close();
	}
}
