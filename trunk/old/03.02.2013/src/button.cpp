/**
 *@file button.cpp
 *@date 14/01/2013
 *@author Charles Oliveira
 *@brief Arquivo com as implementações da classe representativa de um botão
 **/

#include <SDL/SDL.h>
#include <button.hpp>
#include <uielement.hpp>
#include <screen.hpp>

/**
 *	Retorna uma superfície desenhável na tela
 */
void Button::draw(SDL_Surface * base)
{
	SDL_Rect btn = {this->x, this->y, this->w, this->h};
	SDL_FillRect(base, &btn, 
		SDL_MapRGB(base->format, this->color->r, this->color->g, this->color->b));

	// Coloca o rotulo em cima do botão
	if(label)
	    SDL_BlitSurface(label, NULL, base, &btn);
}

/**
 *	Inicia um botão
 *@alert Se for usar label, tem que implementar o destrutor da classe
 */
Button::Button(int x, int y, int w, int h, SDL_Color * color, SDL_Surface * label)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->color = color;
	this->label = label;
}

Button::~Button()
{
	if(label)
		SDL_FreeSurface(label);

}
