#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Funçãozinha básica pra desenhar um pixel na tela
// Loco!!! 
// Meu primeiro programa que o usuario desenha na tela usando o mouse!!!
void put_pixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	if(SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
	
    int offset = y * surface->w + x;
    Uint32 color = SDL_MapRGB(surface->format, r, g, b);

    if(surface->format->BytesPerPixel == 1)
        *( ((Uint8*)surface->pixels) + offset) = color;
    else if(surface->format->BytesPerPixel == 2)
        *( ((Uint16*)surface->pixels) + offset) = color;
    else
        *( ((Uint32*)surface->pixels) + offset) = color;
        
    SDL_UpdateRect(surface, x, y, 1, 1);
    
    if(SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
}

int main()
{
	SDL_Surface * screen;
	SDL_Event evt;

	// Inicia o modo de video do SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	// Adiciona a lista de finalização
	atexit(SDL_Quit);
	
	// Inicia uma janela 800x600
	screen = SDL_SetVideoMode(800, 600, 16, 0);
	if(!screen)
	{
		printf("Erro ao criar janela: %s\n", SDL_GetError());
		return 1;
	}
	
	// Verifica se o botão está pressionado, 0-não, 1-sim
	char pressionado = 0;
	
	// Le os eventos até o usuario apertar o mouse ou gerar erro
	while(SDL_WaitEvent(&evt) != 0)
	{
		// Quando passar, evt vai estar preenchido com alguma coisa
		switch(evt.type)
		{
			case SDL_MOUSEMOTION:
				if(!pressionado)
					break;
				printf("Mouse motion. ");
				printf("Nova posicao eh (%i, %i). ", 
					evt.motion.x, evt.motion.y);
				printf("Nova posicao relativa (%i, %i). \n",
					evt.motion.xrel, evt.motion.yrel);
					
				// Desenha um pixel vermelho one o mouse está pressionado
				// Loooooooooooooooooco demais!!!!!
				/*
				
				Move o mouse para a posição indicada
				void SDL_WarpMouse(Uint16 x, Uint16 y);
				
				// Faz o cursor aparecer ou desaparecer
				Se passar SDL_DISABLE, some
				Se passar SDL_ENABLE, aparece
				Se passar SDL_QUERY, retorna SDL_ENABLE ou SDL_DISABLE
				int SDL_ShowCursor(int toggle);
				*/
				put_pixel(screen, evt.motion.x, evt.motion.y, 255, 0, 0);
				break; 
				
			case SDL_MOUSEBUTTONDOWN:
				pressionado = 1;
				printf("Mouse button pressed. ");
				printf("Botao %i na em (%i, %i), state %i\n",
					evt.button.button,
					evt.button.x,
					evt.button.y,
					evt.button.state);
				break;
				
			case SDL_MOUSEBUTTONUP:
				pressionado = 0;
				printf("Mouse button released. ");
				printf("Botao %i na em (%i, %i), state %i\n",
					evt.button.button,
					evt.button.x,
					evt.button.y,
					evt.button.state);
				break;
			
			// Serve para caputrar quando o usuario muda o foco da janela
			// Praticamente pra saber quando pausar o jogo
			/**
			*	When the mouse leaves or enters the window area a
			 SDL_APPMOUSEFOCUS type activation event occurs, if the mouse
			 entered the window then gain will be 1, otherwise gain will
			 be 0. A SDL_APPINPUTFOCUS type activation event occurs when
			 the application loses or gains keyboard focus. This usually
			 occurs when another application is made active. Finally, a
			 SDL_APPACTIVE type event occurs when the application is either
			 minimised/iconified (gain=0) or restored. A single event can
			 have multiple values set in state.
			*/
			case SDL_ACTIVEEVENT:
			
				if(evt.active.state == SDL_APPACTIVE)
				{
					if(evt.active.gain == 0)
						printf("Jogo minimizado, hora de pausar! \n");
					else 
						printf("Jogo restaurado, usuario despausa! \n");
				}
				
				if(evt.active.state == SDL_APPMOUSEFOCUS)
				{
					if(evt.active.gain == 0)
						printf("Clicou fora, hora de pausar! \n");
					else 
						printf("Clicou dentro, usuario despausa! \n");
				}
				
				if(evt.active.state == SDL_APPINPUTFOCUS)
				{
					if(evt.active.gain == 0)
						printf("Perdeu foco (alt+tab?),hora de pausar! \n");
					else 
						printf("Ganhou foco, usuario despausa! \n");
				}
				
				break;
					
			// Chamado quando o usuário clica no 'x' pra fechar janela
			case SDL_QUIT:
				printf("Saindo da parada\n");
				exit(0);
		}
	}
	
	// Mostra a tela por 3 segundos
	//SDL_UpdateRect(screen, 0, 0, 0, 0);
	
	// Delay
	//SDL_Delay(3000);
	
	// Libera

	printf("Fim!|\n");
	return 0;
}

