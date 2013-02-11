#include <vector>

#include <mapa.h>
#include <ambiente.h>

using namespace std;

void Mapa::configurarMapa()
{
	vector<int> * tiles;
	switch(this->tipo)
	{
		case JARDIM_EXTERNO:
			tiles = Ambiente::carregarMapa("media/maps/externGarden.map");
			break;

		case SALA_TREINAMENTO:
			tiles = Ambiente::carregarMapa("media/maps/trainingRoom.map");
			break;

		case SALA_BANHO:
			tiles = Ambiente::carregarMapa("media/maps/showerRoom.map");
			break;
	}


}

int Mapa::desenhar()
{
	return 0;
}

Mapa::Mapa(TipoMapa tipo)
{
	// Carrega as configuracoes de cada tipo especifico de mapa
	this->tipo = 0;
	this->rect = {0, 0, Tela::WIDTH, Tela::HEIGHT};
}

Mapa::~Mapa()
{

}
