#include <torre.h>
#include <ataque.h>
#include <ambiente.h>
#include <vector>

using namespace std;

int Torre::WIDTH = 40;
int Torre::HEIGHT = 40;

int Torre::desenharAtaque()
{
	void * temp;
	for(unsigned int i = 0; i < this->ataques->size(); i++)
	{
		temp = this->ataques->at(i);
		((Movimentavel *)temp)->movimentar();
		((Movimentavel *)temp)->detectarColisao();
		((Desenhavel *)temp)->desenhar();
	}
	return 0;
}

void configurarTorre()
{
	switch(this->tipo)
	{
		case NINJA:
			this->imagem = Ambiente::carregarImagem();
			this->alcance = 1;
			this->dano = 70;
			this->ataquePorSegundo = 2;
			break;
	}
}

Torre::Torre(TipoTorre tipo, int x, int y)
{
	this->ataques = new vector<Ataque *>;
	this->tipo = tipo;
	this->rect = {x, y, Torre::WIDTH, Torre::HEIGHT};
	this->configurarTorre();
}

Torre::~Torre()
{
	if(ataques) delete ataques;
}

int Torre::realizarUpgrade()
{
	return 0;
}

int Torre::detectarEvento()
{
	return 0;
}

int Torre::desenhar();
{
	SDL_Surface * canvas = SDL_GetVideoSurface();
	if(!canvas)
		return -1;

	// Implementa a sua funcao de desenhar na surface

	// Chama o desenho dos ataques
	this->desenharAtaque();

	return 0;
}