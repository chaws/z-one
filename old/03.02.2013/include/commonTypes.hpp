/**
 *@file commonTypes.hpp
 *@date 12/01/2013
 *@author Charles Oliveira
 *@brief Contém declarações de tipos de dados comuns para toda aplicação
 **/

#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

/**
 * @enum ERROR
 * @brief Enumeração para os Tipos de Erros que aparecerão durante o desenvolvimento/execução
 *obs: os erros devem crescer negativamente: -1, -2, -3 etc
 **/
typedef enum 
{
	OK = 0,					/**< Tudo ok */
	NOT_IMPLEMENTED = -1,	/**< função ainda não implementada */
	OUT_OF_MEMORY = -2		/**< Incrivel, mas as vezes acontece a falta de memória */
} Error;

/**
 * @enum AgentType
 * @brief Enumeração para os Tipos de Eventos capturados pela classe Event
 **/
typedef enum 
{
// 3.1.1 - Samurais 
	ASHIGARU,		/**< Samurai de classe baixa equipado com um par de facas (Estilo: Normal). */
	BATOSAI, 		/**< Samurai com sede de sangue, extremamente veloz e fatal, ficando equipado com duas katanas (Estilo: Rápido). */
	DOJO_MASTER, 	/**< Mestre de dojo: Samurai experiente em batalhas equipado com um uma katana (Estilo:  Resistente e lento). */
	SAINT_SWORD, 	/**< espada-Santa: Samurai que possui técnicas supremas, secretas e sobre-humanas (Estilo:Boss). */
// 3.1.2 - Piratas
	HARRIER, 		/**< Saqueadores: Pirata comum equipado um mosquete (Estilo: Normal). */
	CORSAIR, 		/**< Corsários: Pirata saqueador de grandes embarcações, equipado com um sabre (Estilo: Rápido). */
	WOOD_LEG, 		/**< Perna de pau: Pirata experiente com deficiência em uma perna, equipado com um punhal (Estilo: Resistente e lento). */
	CAPITAIN,  		/**< Capitão: Pirata comandante, extremamente cruel e cauteloso, equipado com um gancho e um sabre (Estilo:Boss). */
	KATANA_NINJA, 	/**< Katana Ninja: Ninja equipado com uma Katana, espada de curto alcance, que ataca um alvo de cada vez. Ao evoluir ataca mais rápido e causa maior dano. Pode evoluir até duas vezes. */
	NUNCHAKU_NINJA, /**< Nunchaku Ninja: Ninja equipado com um nunchaku, arma de curto alcance que ataca todos os inimigos em uma pequena area em frente a ele. Ao evoluir causa maior dano e no último estágio diminui a velocidade dos inimigos que acerta. */
	MANRIKI_NINJA, 	/**< Manriki Ninja: Ninja equipado com o Manriki, corrente com pesos, que ataca em uma pequena area em volta dele. Ao evoluir aumenta o raio do seu ataque, o dano causado e a velocidade de ataque. */
// 3.2.2 - Longo alcance (ranged)
	KUNAI_NINJA, 	/**< Kunai Ninja: Ninja equipado com kunais, armas de furo e  longo alcance, que ataca um inimigo de cada vez. Ao evoluir aumenta a velocidade de ataque e o dano causado. */
	SHURIKEN_NINJA, /**< Shuriken Ninja:  Ninja equipado com shurikens, arma de longo alcance e de grande velociade de ataque, mas de dano reduzido, atacando um inimigo por vez. Ao evoluir aumenta sua velocidade de ataque, seu alcance e o dano causado. */
	BOMB_NINJA,	 	/**< Ninja que joga bombas: Ninja que joga explosivos, danificando os inimigos em uma área. Ao evoluir aumenta o dano causado, a area do dano e o alcance. */
	KNIFE_NINJA, 	/**< Facas de lançamento: Ninja equipado com facas de lançamento, armas de corte e longo alcance. Ao evoluir aumenta o alcance e o dano causado. */
// 3.2.3 - Armadilhas (traps)
	BEAR_TRAP, 		/**< Armadilha de urso: Prende um inimigo próximo a uma torre. A torre fica então encumbida de destruir o inimigo preso na armadilha. */
	WALL_THORN 		/**< Parede com espinhos: Uma parede colocada estratégicamente que machuca os inimigos que passam por perto. */
} AgentType;

/**
 * @enum EvtType
 * @brief Enumeração para os Tipos de Eventos capturados pela classe Event
 **/
typedef enum 
{
	MOUSE_RCLICKED,		/**< Clique com botão direito do mouse, para pegar as coordenadas, veja a classe Event */
	MOUSE_MCLICKED,		/**< Clique com botão esquerdo do mouse, para pegar as coordenadas, veja a classe Event */
	MOUSE_LCLICKED,		/**< Clique com botão do meio do mouse, para pegar as coordenadas, veja a classe Event */
	MOUSE_RRELEASED,	/**< Liberação do botão direito do mouse, para pegar as coordenadas, veja a classe Event */
	MOUSE_MRELEASED,	/**< Liberação do botão esquerdo do mouse, para pegar as coordenadas, veja a classe Event */
	MOUSE_LRELEASED,	/**< Liberação do botão do meio do mouse, para pegar as coordenadas, veja a classe Event */
	MOUSE_MOVED,		/**< Movimento do mouse, para pegar as coordenadas, veja a classe Event */
	KEY_PRESSED,		/**< Algum botão do teclado foi pressionado, para saber qual foi , veja a classe Event */
	KEY_RELEASED,		/**< Algum botão do teclado foi liberado, para saber qual foi , veja a classe Event */
	WINDOW_LOSTFOCUS,	/**< A perdeu o foco, digamos, alerta do skype */
	WINDOW_GAINEDFOCUS,	/**< A janela ganhou o foco, digamos alt+tab */
	QUIT				/**< O usuário clicou no X, ou o SO requereu o fechamento, digamos um killall */
} EvtType;

/**
 * @struct Evt
 * @brief Estrutura para especificar um evento, contendo seu tipo e suas coordenadas, quando necessário
 **/
typedef struct 
{
	EvtType type;	/**< O tipo do evento capturado, veja EvtType */
	int x;			/**< Posição X, caso for evento de mouse */
	int y;			/**< Posição Y, caso for evento de mouse */
	int dx;			/**< Variação dx em relação a ultima posição x, caso for evento movimentação de mouse */
	int dy;			/**< Variação dy em relação a ultima posição y, caso for evento movimentação de mouse */
	SDLKey key;		/**< Tecla pressionada, para saber a correspondencia completa veja o man */
} Evt;

/**
 * @enum GameState
 * @brief Enumeração para os estados possiveis do jogo
 **/
typedef enum 
{
	STARTING,		/**< O jogo está sendo inicializado, o usuario acabou de abri-lo */
	SETTING,		/**< O jogo está sendo configurado, é a hora que o usuario ve o jogo aberto e decide o que vai fazer */
	PLAYING,		/**< O jogo está sendo jogado */
	CHANGING,		/**< O jogo está passando para o próximo nível */
	GAME_OVER,		/**< O jogador acaba de perder o jogo */
	COMPLETED,		/**< O jogador acaba de ganhar o jogo */
	PAUSED,			/**< O jogo está pausado */
	ENDING			/**< O jogo está sendo finalizado */
} GameState;

#endif
