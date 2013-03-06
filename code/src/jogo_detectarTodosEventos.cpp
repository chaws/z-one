#include <jogo.h>
#include <util.h>
#include <SDL/SDL.h>
#include <iostream>

using namespace std;

int Jogo::detectarTodosEventos()
{	
	
	switch(Util::estadoInterno){
		case OBSERVANDO:
			while(SDL_PollEvent(&Escutavel::evento)){
				for(unsigned int i = 0; i < vetorEscutaveis->size(); i++)
					vetorEscutaveis->at(i)->detectarEvento();
				detectarSaidaAplicativo();
			}
		break;
		
		case COMPRANDO:
			
			while(SDL_PollEvent(&Escutavel::evento))
			{
				
				switch(Escutavel::evento.type){
					case SDL_MOUSEMOTION:
						
						Util::imagemCompra.rect->x = Escutavel::evento.motion.x - 20;
						Util::imagemCompra.rect->y = Escutavel::evento.motion.y - 20;
						break;
					
					case SDL_MOUSEBUTTONDOWN:
						if(Escutavel::evento.button.button == SDL_BUTTON_LEFT){
							int x = Escutavel::evento.button.x / 40;
							x = x * 40;
							
							int y = Escutavel::evento.button.y / 40;
							y = y * 40;
							
							int tileX = x / 40;
							int tileY = y / 40;
							
							int indice = (tileY * 20) + tileX;
							
							if (this->mapa->tiles->at(indice) == UTILIZAVEL)
							{
								Torre * torre = new Torre(Util::torreCompra, x, y, this->wave,this->vetorDesenhaveis,this->vetorMutaveis);
								this->vetorDesenhaveis->push_back(torre);
								this->vetorMutaveis->push_back(torre);
								Util::estadoInterno = OBSERVANDO;
							}
							else
							{
								// verificar o que vamos fazer ainda...
							}							
							
						}
						if(Escutavel::evento.button.button == SDL_BUTTON_RIGHT){
							Util::estadoInterno = OBSERVANDO;
						}
				}
				detectarSaidaAplicativo();
			}
		break;
	}
	

	return 0;
}
