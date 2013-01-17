/**
 *@file event.hpp
 *@date 12/01/2013
 *@author Charles Oliveira
 *@brief Arquivo com as declarações das funções de captura de evento, a classe Game é responsável por trata-los
 **/

#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL/SDL.h>
#include <commonTypes.hpp>
#include <queue>

using namespace std;

/**
 * @def Define o número máximo de eventos por captura, 
 * do contrário poderia travar o jogo só com captura de eventos
 */
#define MAX_POLL_EVENT 15

/**
 *@class Event
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Classe responsável por captura de eventos
 * Ocorre a captura e os eventos são enfileirados em q
 */
class Event
{
private:
	/**
	 *	Fila de eventos capturados
	 */
	queue<Evt *> * q;	

	/**
	 *	Evento nativo do SDL
	 */
	SDL_Event event;

	/**
	 *	Captura eventos de janela
	 */
	void getWindowEvent();

	/**
	 *	Captura eventos do mouse
	 */
	void getMouseEvent();

	/**
	 *	Captura eventos do teclado
	 */
	void getKeyboardEvent();

	/**
	 *	Adiciona um novo evt na fila
	 */
	void addEvt(EvtType e, int x = -1, int y = -1, int dx = 0, int dy = 0, SDLKey k = SDLK_FIRST);

	/**
	 *	Adiciona um novo evt na fila
	 */
	void addEvt(Evt * e);

public:
	/**
	 *	Inicia a fila de eventos
	 */
	int init();

	/**
	 *	Captura todos os inputs
	 */
	void getInput();



	/**
	 *	Retorna cada um dos elementos da fila, que são eventos capturados
	 */
	Evt * next();
};

#endif
