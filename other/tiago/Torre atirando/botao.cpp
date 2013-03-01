#include "botao.h"

#include <iostream>

using namespace std;

botao::botao(int tipo, int x, int y){
	box.x = x;
	box.y = y;
	box.w = 40;
	box.h = 40;

	switch(tipo){
		case SHURIKEN:
			image = carregaImagem("img/botao_ninja_shuriken.png");
			break;
		case BOMBA:
			image = carregaImagem("img/botao_ninja_bomba.png");
			break;
		case REFRESH:
			image = carregaImagem("img/botao_config.png");
			break;
	}

	type = tipo;

}

botao::~botao(){
	SDL_FreeSurface(image);
}

void botao::onClick(){
	cout << "clicou em um botao!" << endl;
}

bool botao::clicked(int x, int y){
	if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h))
		return true;
	return false;
}

void botao::handleEvents(SDL_Event* event){
	if(event->type == SDL_MOUSEBUTTONDOWN){
		if(event->button.button == SDL_BUTTON_LEFT){
			int x = event->button.x;
			int y = event->button.y;

			if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){
				onClick();
			}
		}
	}
}

void botao::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}