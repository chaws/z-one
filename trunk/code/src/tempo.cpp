#include <SDL/SDL.h>
#include <tempo.h>
#include <tela.h>
#include <iostream>

Tempo::Tempo()
{

}

Tempo::~Tempo()
{

}

void Tempo::iniciarTempo()
{
    this->tempoInicio = SDL_GetTicks();
}

long int Tempo::pegarTempoCorrido()
{
    return SDL_GetTicks() - this->tempoInicio;
}

void Tempo::atrasarTempo()
{
    long int atraso = this->pegarTempoCorrido();
    
    if((1000 / Tela::FPS) > atraso)
        SDL_Delay((1000 / Tela::FPS) - atraso);
}
