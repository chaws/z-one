/**
 *@file agent.hpp
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Arquivo com a classe agente, abstração dos atores do jogo
 **/

#ifndef AGENT_HPP
#define AGENT_HPP

#include <commonTypes.hpp>

/**
 *@class Agent
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Classe responsável por representar os agentes do jogo de uma forma geral, 
 * um agente é uma torre, uma armadilha, um ninja etc
 */
class Agent
{
public:
	/**
	 *
	 */
	int x;

	/**
	 *
	 */
	int y;

	/**
	 *
	 */
	int w;

	/**
	 *
	 */
	int h;

	/**
	 *	De quantos pixels uma sprite está separada da outra
	 */
	int spriteStep;	

	/**
	 *
	 */
	AgentType type;

	/**
	 *	
	 */
	virtual Agent detectColision() = 0;
};

#endif
