#include "mapa.h"

mapa::mapa(int tipo){



	fstream reader;

	if(!reader.is_open()){
		switch(tipo){
			case 1:
				reader.open("mapa/mapa.map");
				n_pode_por_torre=carregaImagem("tile/acid.png");
				caminho=carregaImagem("tile/wood.png");
				inicio=carregaImagem("tile/carpet.png");
				fim=carregaImagem("tile/carpet.png");
				pode_por_torre=carregaImagem("tile/bricks.png");
			break;
		}
		if(!reader){
			cerr << "Falhou em abrir: " << reader << endl;
		}
	}

	//instanciando os tiles do mapa
	char aux;
	for(int i = 0;i<300;i++){
		aux = reader.get();
		if(aux==32 || aux==10){
			i--;
		}
			
		else{
			switch(aux){
				case 0: //n pode colocar torre
					tiles.push_back(new tile(&n_pode_por_torre));
				case 1: //caminho
					tiles.push_back(new tile(&n_pode_por_torre));
				case 2: //pode colocar torre
					tiles.push_back(new tile(&n_pode_por_torre));
				case 3: //inicio
					tiles.push_back(new tile(&n_pode_por_torre));
				case 4: //fim
					tiles.push_back(new tile(&n_pode_por_torre));
			}
			m.tiles[i].code = aux;
		}
	}
	reader.close();	
}

mapa::~mapa(){
	//desalocar todos os tiles
	SDL_FreeSurface(caminho);
	SDL_FreeSurface(inicio);
	SDL_FreeSurface(fim);
	SDL_FreeSurface(pode_por_torre);
	SDL_FreeSurface(n_pode_por_torre);
}

void mapa::show(){
	//TODO
}

void mapa::update(){

}