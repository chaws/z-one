#ifndef TEMPO_H
#define TEMPO_H

class Tempo
{	
private:
	long int tempoInicio;
	long int pegarTempoCorrido();

public:
	
	Tempo();
	~Tempo();
	void iniciarTempo();
	void atrasarTempo();
};

#endif
