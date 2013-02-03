/**
 *@file game_processInputs.cpp
 *@date 4/01/2013
 *@author Matheus Fonseca
 *@brief Arquivo com as a implementação do controle lógico do jogo
 **/

#include <SDL/SDL.h>
#include <iostream>
#include <game.hpp>
#include <commonTypes.hpp>
#include <environment.hpp>
#include <screen.hpp>
#include <event.hpp>
#include <sound.hpp>
#include <string>

/**
 *
 */
void Game::processInputs()
{
	// Processa os eventos/inputs
	Evt * e;
	while((e = this->event->next()))
	{
		switch(e->type)
		{

			case MOUSE_RCLICKED:		/**< Clique com botão direito do mouse, para pegar as coordenadas, veja a classe Event */
				cout << "Clique botão direito" << endl;
				break;

			case MOUSE_MCLICKED:		/**< Clique com botão esquerdo do mouse, para pegar as coordenadas, veja a classe Event */
				cout << "Clique botão do meio" << endl;
				break;

			case MOUSE_LCLICKED:		/**< Clique com botão do meio do mouse, para pegar as coordenadas, veja a classe Event */
				cout << "Clique botão esquerdo" << endl;

				// Implementação baiana de detectar clique no botão sair
				if(530 < e->x && e->x < 780 && 240 < e->y && e->y < 340)
					cout << "Clicou no botao de novo jogo!!!" << endl;					

				break;

			case MOUSE_RRELEASED:		/**< Liberação do botão direito do mouse, para pegar as coordenadas, veja a classe Event */
				cout << "Liberação botão direito" << endl;
				break;

			case MOUSE_MRELEASED:		/**< Liberação do botão esquerdo do mouse, para pegar as coordenadas, veja a classe Event */
				cout << "Liberação botão do meio" << endl;
				break;

			case MOUSE_LRELEASED:		/**< Liberação do botão do meio do mouse, para pegar as coordenadas, veja a classe Event */
				cout << "Liberação botão esquerdo" << endl;
				break;

			case MOUSE_MOVED:			/**< Movimento do mouse, para pegar as coordenadas, veja a classe Event */
				//cout << "O mouse se mexeu" << endl;
				break;

			case KEY_PRESSED:			/**< Algum botão do teclado foi pressionado, para saber qual foi , veja a classe Event */
				cout << "Tecla pressionada: ";
				printf("%c", e->key);
				cout << endl;
				break;

			case KEY_RELEASED:			/**< Algum botão do teclado foi liberado, para saber qual foi , veja a classe Event */
				cout << "Tecla liberada" << endl;
				printf("%c", e->key);
				cout << endl;
				break;

			case WINDOW_LOSTFOCUS:		/**< A perdeu o foco, digamos, alerta do skype */
				cout << "A janela perdeu o foco" << endl;
				break;

			case WINDOW_GAINEDFOCUS:	/**< A janela ganhou o foco, digamos alt+tab */
				cout << "A janela recebeu o foco" << endl;
				break;

			case QUIT:
				cout << "QUIT!!!" << endl;
				// Pergunta se deseja mesmo sair
				this->status = ENDING;
				break;

			default:
				cout << "Evento desconhecido" << endl;
		}

		// Libera a memória de evt
		free(e);
	}
}