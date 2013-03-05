#include "ninja.h"

ninja::ninja(){
	imagem = 
}

ninja::~ninja(){

}

void ninja::update(){

}

void ninja::show(){
	SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}