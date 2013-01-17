/**
 *@file screen.cpp
 *@date 11/01/2013
 *@author Charles Oliveira
 *@brief Arquivo com a implementação das funções de tela
 **/
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <string>
#include <math.h>
#include <iostream>
#include <screen.hpp>
#include <commonTypes.hpp>
#include <environment.hpp>

using namespace std;

/**
*@brief Inicia os módulos necessários da SDL para a execução do jogo
*<hr>
* <ul>
* 	<li> Tarefas realizadas pela função.
* 		<ol>
* 			<li> Inicia a SDL com a FLAG para iniciar tudo
* 			<li> Inicia a tela principal com as dimensões 800x600 e 32 bits por pixel
* 			<li> Seta o título da janela
* 		</ol>
* </ul>
* @param[in] f Tripa de bytes a ser convertida para uma <i>struct</i> de
* PDU.
* @return Uma referência para uma <i>struct</i> de PDU é retornada ou 
* um valor NULL é passado.
* @attention Lembrar de chamar <i>destroy</i> ao encerrar o jogo
* @see Screen
*/
int Screen::init()
{
	// Inicializa todos os componentes do SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
    // Define a tela do jogo 
	this->canvas = SDL_SetVideoMode(this->WIDTH, this->HEIGHT, this->BPP, this->VIDEO_OPTIONS);
	
	// Define o título da tela do jogo
	SDL_WM_SetCaption("Ninja Siege", "Ninja Siege");
	SDL_WM_SetIcon(Env::loadImage("media/image/z_one_logo_32_32.png"), NULL);
	cout << "Ninja Siege, by Z-One Team." << endl;

    // Inicia a ferramenta pra trabalhar com fontes
    TTF_Init();

	return OK;
}

void Screen::destroy()
{
	// Libera a estrutura da tela do jogo
    SDL_FreeSurface(this->canvas);

    // Libera a fonte
    TTF_Quit();
    
    // Libera todas as alocações do SDL (desliga)
    SDL_Quit();
}

void Screen::render()
{
	// Tenho uma ideia de colocar todos os offsets de applySurface dentro de uma fila pra depois
	// Ir atualizando os retangulos aos poucos, ao inves de dar flip
	SDL_Flip(this->canvas);
}

/**
 * A ser chamado antes da montagem do frame
 */
void Screen::controlBFPS()
{
    fpsControl = SDL_GetTicks();
}

/**
 * A ser chamado depois da montagem do frame
 */
void Screen::controlAFPS()
{
    // Ve se precisa de um atraso
    if((1000 / this->FPS) > (SDL_GetTicks() - fpsControl))
        SDL_Delay((1000 / this->FPS) - (SDL_GetTicks() - fpsControl));
}

/**
 * @brief Desenha uma linha entre dois pontos utilizando o algoritmo de Bresenham
 * @author Edson Alves
 * @param[in] x1 Posição x do primeiro ponto
 * @param[in] y1 Posição y do primeiro ponto
 * @param[in] x2 Posição x do segundo ponto
 * @param[in] y2 Posição y do segundo ponto
 * @param[in] color Cor no formato SDL da linha
 */
void Screen::drawLine(int x1, int y1, int x2, int y2, SDL_Color color)
{
    Uint32 pixelColor = SDL_MapRGB(this->canvas->format, color.r, color.g, color.b);

    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x = (int)x1; x < maxX; x++)
    {
        if(steep)
            this->putPixel(y, x, pixelColor);
        else
            this->putPixel(x, y, pixelColor);

        error -= dy;

        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

void Screen::drawRectangle(int x, int y, int w, int h, SDL_Color color)
{
	// Apenas usei as variaveis para não gerar warnings
	SDL_Rect rect = {x, y, w, h};
	SDL_FillRect(this->canvas, &rect, SDL_MapRGB(this->canvas->format, color.r, color.g, color.b));
}


void Screen::drawCircle(int radius, int x, int y, SDL_Color color)
{
    Uint32 pixelColor = SDL_MapRGB(this->canvas->format, color.r, color.g, color.b);

    // Algoritmo de Bresenham para círculos
    int error = 3 - (radius << 1);
    int i = 0, j = radius;

    do
    {
        this->fillPoints(x, y, i, j, pixelColor);

        if (error < 0)
        {
            error += (i << 2) + 6;
        } 
        else
        {
            error += ((i - j) << 2) + 10;
            j--;
        }

        i++;
    } while (i <= j);
}

void Screen::fillPoints(int cx, int cy, int x, int y, Uint32 color)
{
    for (int j = x; j <= y; j++)
    {
        this->putPixel(cx + x, cy + j, color);
        this->putPixel(cx + x, cy - j, color);
        this->putPixel(cx - x, cy + j, color);
        this->putPixel(cx - x, cy - j, color);
        this->putPixel(cx + j, cy + x, color);
        this->putPixel(cx + j, cy - x, color);
        this->putPixel(cx - j, cy + x, color);
        this->putPixel(cx - j, cy - x, color);
    }
}

void Screen::putPixel(int x, int y, Uint32 pixel)
{
    int Bpp = this->canvas->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)this->canvas->pixels + (y * this->canvas->pitch) + (x * Bpp);

    switch(Bpp) 
    {
	    case 1:
	        *p = pixel;
	        break;

	    case 2:
	        *(Uint16 *)p = pixel;
	        break;

	    case 3:
	        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
	        {
	            p[0] = (pixel >> 16) & 0xff;
	            p[1] = (pixel >> 8) & 0xff;
	            p[2] = pixel & 0xff;
	        } else {
	            p[0] = pixel & 0xff;
	            p[1] = (pixel >> 8) & 0xff;
	            p[2] = (pixel >> 16) & 0xff;
	        }
	        break;

	    case 4:
	        *(Uint32 *)p = pixel;
	        break;
    }
}


void Screen::applySurface(int x, int y, SDL_Surface * src) 
{
    // Estrutura que ira conter as coordenadas indicado aonde será aplicada 
    // a superfície 'src' dentro da superície 'dest'
    SDL_Rect offset;
    
    // Definindo as coordenadas
    offset.x = x;
    offset.y = y;
    
    // Coloca src em cima do canvas atual
    SDL_BlitSurface(src, NULL, this->canvas, &offset);

    // É melhor só uma pequena atualização de retangulo para ecnonmizar performance
	//SDL_UpdateRect(screen, 0, 0, 0, 0);
}

/**
 *  Menu principal do jogo
 */
void Screen::mainMenu()
{
    int x, y;
    // Inicializando a fonte
	TTF_Font *loadedFont = NULL;

    // Vamos montar a primeira janela do jogo haha
    // 1o, carregar o fundo "wood.jpg" e replicá-lo por toda janela
    SDL_Surface * fundo = Env::loadImage("media/image/wood.jpg");
    for(y = 0; y < this->HEIGHT; y += fundo->h)
        for(x = 0; x < this->WIDTH; x += fundo->w)
            this->applySurface(x, y, fundo);
    SDL_FreeSurface(fundo);            
    
    // Agora coloca a torre 
    fundo = Env::loadImage("media/image/tower.jpg");
    this->applySurface(40, 40, fundo);
    SDL_FreeSurface(fundo);

    // Agora monta o título do jogo, o botão fechar, o novo jogo, o continue, o config, ajuda e creditos
    this->drawRectangle(60, 60, 300, 150, {255, 50, 20});

    
    
    
    // Carregando a fonte	
	loadedFont = TTF_OpenFont("media/font/UbuntuMono-B.ttf", 47);
	if(!loadedFont) {
		cout << "Erro ao abrir fonte: " << SDL_GetError() << endl; 
		//return NULL; 
	}
	cout << "Fonte aberta com sucesso!" << endl;
    
    // Escreve o texto
    this->writeText(loadedFont, "Ninja Siege", 80, 110, {84, 184, 234});
    TTF_CloseFont(loadedFont);
}

void Screen::writeText(TTF_Font *font, string text, int x, int y, SDL_Color color)
{
    
    SDL_Surface * textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        cout << "Erro ao escrever na superfície: " << SDL_GetError() << endl; 
		//return NULL; 
    }
    
    this->applySurface(x, y, textSurface);

    SDL_FreeSurface(textSurface);
}


void drawMap(Map *map){
    //pega os tiles e desenha na tela
    SDL_Surface * tela = NULL;
    for(y = 0; y < this->HEIGHT; y += fundo->h)
        for(x = 0; x < this->WIDTH; x += fundo->w)
            this->applySurface(x, y, fundo);
    SDL_FreeSurface(fundo); 
}

