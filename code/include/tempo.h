#ifndef TEMPO_H
#define TEMPO_H

class Tempo
{	
private:
	int tempoInicio;
	int tempoPause;

public:
	bool estaPausado;
	bool estaIniciado;
	
	Tempo();
	~Tempo();
	void pausarTempo();
	void despausarTempo();
	int pegarTempo();	
};

#endif
