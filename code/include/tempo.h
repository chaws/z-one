#ifndef TEMPO_H
#define TEMPO_H

class Tempo
{	
private:
	long int tempoInicio;
	long int pegarTempoCorrido();
	//int tempoPause;

public:
	//bool estaPausado;
	//bool estaIniciado;
	
	Tempo();
	~Tempo();
	//void pausarTempo();
	//void despausarTempo();
	void iniciarTempo();
	void atrasarTempo();
};

#endif
