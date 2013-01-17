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
	if(this->event.active.state == SDL_APPACTIVE)
		this->addEvt(event.active.gain == 0 ? WINDOW_LOSTFOCUS : WINDOW_GAINEDFOCUS);
	
	if(this->event.active.state == SDL_APPINPUTFOCUS)
		this->addEvt(event.active.gain == 0 ? WINDOW_LOSTFOCUS : WINDOW_GAINEDFOCUS);
}

/**
 *	Se essa função foi chamada é pq foi disparado um evento de mouse
 */
void Event::getMouseEvent()
{
	Evt * ev;
	ev = (Evt *)malloc(sizeof(Evt));
	if(this->event.type == SDL_MOUSEMOTION)
	{
		ev->x = this->event.motion.x;
		ev->y = this->event.motion.y;
		ev->dx = this->event.motion.xrel;
		ev->dy = this->event.motion.yrel;
		ev->type = MOUSE_MOVED;
		addEvt(ev);
		return;
	}

	ev->x = this->event.button.x;
	ev->y = this->event.button.y;

	if(this->event.type == SDL_MOUSEBUTTONDOWN)
		ev->type = (event.button.button == SDL_BUTTON_LEFT ? MOUSE_LCLICKED : 
			(event.button.button == SDL_BUTTON_MIDDLE ? MOUSE_MCLICKED : MOUSE_RCLICKED));
	else
		ev->type = (event.button.button == SDL_BUTTON_LEFT ? MOUSE_LRELEASED : 
			(event.button.button == SDL_BUTTON_MIDDLE ? MOUSE_MRELEASED : MOUSE_RRELEASED));

	addEvt(ev);
}

/**
 *
 */
void Event::getKeyboardEvent()
{
	Evt * ev;
	ev = (Evt *)malloc(sizeof(Evt));

	ev->type = this->event.type == SDL_KEYDOWN ? KEY_PRESSED : KEY_RELEASED;
	ev->key = this->event.key.keysym.sym;

	this->q->push(ev);
}

/**
 *	Adiciona um novo evt na fila
 */
void Event::addEvt(EvtType e, int x, int y, int dx, int dy, SDLKey k)
{
	Evt * ev;
	ev = (Evt *)malloc(sizeof(Evt));
	ev->x = x;
	ev->y = y;
	ev->dx = dx;
	ev->dy = dy;
	ev->type = e;
	ev->key = k;
	this->q->push(ev);
}


/**
 *	Adiciona um novo evt na fila
 */
void Event::addEvt(Evt * e)
{
	this->q->push(e);
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
