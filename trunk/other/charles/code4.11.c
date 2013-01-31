#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

static int counter = 0;
SDL_mutex * counter_mutex;

// As threads vão executar até essa flag ser setada
static int exit_flag = 0;

int ThreadEntryPoint(void * data)
{
	char * threadname;
	
	// Qualquer coisa que seja passado em data será o nome da thread
	threadname = (char *)data;
	
	while(exit_flag == 0)
	{
		printf("this is %s! ", threadname);
		
		// Espera ate reservar o semaforo
		SDL_mutexP(counter_mutex);
		
		// agora da pra modificar o contador
		printf("The counter is currently %i\n", counter);
		counter++;
		
		// Libera o semaforo
		SDL_mutexV(counter_mutex);
		
		// Atraso baaasico
		SDL_Delay(rand() % 3000);
	}
	
	printf("%s esta saindo agora! \n", threadname);
	return 0;
}

int main()
{
	SDL_Thread * thread1, * thread2, * thread3;
	
	// Semaforo pra proteger o contador
	counter_mutex = SDL_CreateMutex();
	
	printf("Ctrl+C pra sair\n");
	
	// Cria as 3 threads e dá nome a cada uma
	thread1 = SDL_CreateThread(ThreadEntryPoint, "Thread 1");
	thread2 = SDL_CreateThread(ThreadEntryPoint, "Thread 2");
	thread3 = SDL_CreateThread(ThreadEntryPoint, "Thread 3");
	
	// Roda tudo até o contador chegar a 20
	while(counter < 20)
		SDL_Delay(1000);
		
	// Sinaliza pra sair da thread
	exit_flag = 1;
	printf("exit_flag foi setada\n");
	
	// Espera as outras threads
	SDL_Delay(3500);
	
	// Destroi o mutex
	SDL_DestroyMutex(counter_mutex);
	
	printf("\n*** Fim ***|\n");
	return 0;
}

