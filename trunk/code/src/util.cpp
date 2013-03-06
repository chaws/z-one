#include <util.h>
#include <ambiente.h>
#include <mutavel.h>
#include <desenhavel.h>
#include <escutavel.h>
#include <vector>
#include <jogo.h>

using namespace std;

EstadoJogo Util::estadoJogo = JOGANDO; // ENTRADA_JOGO
EstadoInterno Util::estadoInterno = OBSERVANDO;
TipoTorre Util::torreCompra;
ImagemCompra Util::imagemCompra;

int ImagemCompra::desenharImagemCompra()
{
	SDL_BlitSurface(Util::imagemCompra.imagem, NULL, SDL_GetVideoSurface(),Util::imagemCompra.rect);
	
	return 0;
}

int ImagemCompra::desenhar()
{	
	return 0;
}

ImagemCompra::~ImagemCompra()
{
	
}

ImagemCompra::ImagemCompra()
{
	Util::imagemCompra.rect = new SDL_Rect;
	Util::imagemCompra.rect->h = 40;
	Util::imagemCompra.rect->w = 40;
}

int ImagemCompra::configurarImagem(TipoTorre tipo)
{
	switch(tipo)
	{
		case KATANA:
			Util::imagemCompra.imagem = Ambiente::carregarImagem("ninja_katana.png");
			SDL_SetAlpha(Util::imagemCompra.imagem, SDL_SRCALPHA, 127);
			break;
		case SHURIKEN:
			Util::imagemCompra.imagem = Ambiente::carregarImagem("ninja_shuriken.png");
			SDL_SetAlpha(Util::imagemCompra.imagem, SDL_SRCALPHA, 127);
			break;
		case BOMBA:
			Util::imagemCompra.imagem = Ambiente::carregarImagem("ninja_bomba.png");
			SDL_SetAlpha(Util::imagemCompra.imagem, SDL_SRCALPHA, 127);
			break;
	}
	
	return 0;
}

