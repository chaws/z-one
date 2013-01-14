/**
 *@file event.cpp
 *@date 12/01/2013
 *@author Charles Oliveira
 *@brief Arquivo com as implementações das funções de captura de evento, a classe Game é responsável por trata-los
 **/

#include <SDL/SDL.h>
#include <commonTypes.hpp>
#include <environment.hpp>
#include <event.hpp>
#include <queue>

using namespace std;

/**
 *
 */
void Event::getWindowEvent()
{

}

/**
 *
 */
void Event::getMouseEvent()
{
	
}

/**
 *
 */
void Event::getKeyboardEvent()
{
	
}

/**
 *	Adiciona um novo evt na fila
 */
void Event::addEvt(EvtType e, int x, int y, int dx, int dy)
{
	Evt * ev;
	ev = (Evt *)malloc(sizeof(Evt));
	ev->x = x;
	ev->y = y;
	ev->dx = dx;
	ev->dy = dy;
	ev->type = e;
	this->q->push(ev);
}

/**
 *
 */
int Event::init()
{
	this->q = new queue<Evt *>;
	return NOT_IMPLEMENTED;
}

/**
 *	Chama os outros inputs
 */
void Event::getInput()
{
	int i = MAX_POLL_EVENT; // Certifica-se que não vai descontrolar com os eventos

	while(SDL_PollEvent(&this->event) && i--)
	{	
		// Verifica qual evento, tipo pra verificar evento de mouse
		switch(event.type)
		{
			// Eventos de teclado
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				this->getKeyboardEvent();
				break;

			// Eventos de mouse
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				this->getMouseEvent();
				break;

			// Eventos de janela
			case SDL_ACTIVEEVENT:
				this->getWindowEvent();
				break;
				
			// Botão x
			case SDL_QUIT:
				// Botão fechar
				this->addEvt(QUIT);
		}
	}
}

/**
 *	Vai esvaziando a fila e retornando o primeiro elemento a cada chamada de next
 */
Evt * Event::next()
{
	if(this->q->empty())
		return NULL;

	Evt * e = this->q->front();
    this->q->pop();
    return e;
}
