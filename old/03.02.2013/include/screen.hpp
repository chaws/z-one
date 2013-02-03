/**
 *@file screen.hpp
 *@date 10/01/2013
 *@author Charles Oliveira
 *@brief Arquivo com as declarações das funções de tela
 **/

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <uielement.hpp>

/**
 *@class Game
 *@date 13/1/2013
 *@author Charles Oliveira
 *@brief Classe responsável por controlar as telas do jogo
 */

using namespace std;
 
class Screen
{
private:

	/**
	 *	Superfície principal da SDL, servirá como a principal superficie do jogo
	 */
	SDL_Surface * canvas;

	/**
	 *	controlBFPS e controlAFPS compartilham essa variavel para controlar o FPS
	 * @see Screen::controlBFPS
	 * @see Screen::controlAFPS
	 */
	Uint32 fpsControl;

	/**
	 *	Largura da janela do jogo
	 */
    static const int W = 800;    
    
    /**
	 *	Altura da janela do jogo
	 */
	static const int H = 600;
	
	/**
	 *	Bits por pixel. A escolha de 32 se deve ao fato de ter melhor performance do que 
	 *	o padrão 24, e possui muito mais cores que o padrão de 16 bits e paleta
	 */
	static const int BPP = 32;
	
	/**
	 *	Frames por Segundo
	 */
	static const int FPS = 30;
	
	/**
	 *	Flags necessárias para inicialização da SDL
	 *	Tenta usar a memória da placa de vídeo (SDL_HWSURFACE) e, caso consiga
	 *	utiliza o dobro de memória para fazer proveito do framebuffer
	 */
	static const Uint32 VIDEO_OPTIONS = SDL_HWSURFACE | SDL_DOUBLEBUF;

public:

	/**
	 *	Inicializa as variaveis e a SDL
	 *@return 0 se tudo ocorreu bem e < 0 se houve algum erro
	 */	
	int init();

	/**
	 *
	 */	
	void destroy();

	/**
	 *	Atualiza a tela
	 *TODO: perguntar pro Edson se compensa fazer uma fila com os retangulos desenhados
	 *afim de julgar se é melhor atualizar a tela toda ou apenas os retangulos
	 */	
	void render();

	/**
	 * A ser chamado antes da montagem do frame
	 */
	void controlBFPS();

	/**
	 * A ser chamado depois da montagem do frame
	 */
	void controlAFPS();

	/**
	 * @brief Desenha uma linha entre dois pontos utilizando o algoritmo de Bresenham
	 * @author Edson Alves
	 * @param[in] x1 Posição x do primeiro ponto
	 * @param[in] y1 Posição y do primeiro ponto
	 * @param[in] x2 Posição x do segundo ponto
	 * @param[in] y2 Posição y do segundo ponto
	 * @param[in] color Cor no formato SDL da linha
	 */
	void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);

	/**
	 *
	 */
	void drawRectangle(int x, int y, int w, int h, SDL_Color color);

	/**
	 *
	 */
	void drawCircle(int radius, int x, int y, SDL_Color color);

	/**
	 *
	 */
	void drawElement(UIElement * element);

	/**
	 *
	 */
	void fillPoints(int cx, int cy, int x, int y, Uint32 color);

	/**
	 *
	 */
	void putPixel(int x, int y, Uint32 pixel);

	/**
	 *
	 */
    void applySurface(int x, int y, SDL_Surface * src);

    /**
     *	Menu principal do jogo
     */
    void mainMenu();

	/**
	 *
	 */
    void writeText(TTF_Font * font, string text, int x, int y, SDL_Color color);
    /**
     *
     */
    //void drawMap(Map * map);
};

#endif
