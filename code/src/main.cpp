#include <aliado.h>
#include <armadilha.h>
#include <ataque.h>
#include <botao.h>
#include <desenhavel.h>
#include <escutavel.h>
#include <inimigo.h>
#include <jogo.h>
#include <mapa.h>
#include <mutavel.h>
#include <tempo.h>
#include <torre.h>

int main()
{
	Jogo * jogo;
	jogo = new Jogo();
	jogo->rodar();
	
	return 0;
}
