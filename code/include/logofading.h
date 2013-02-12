#ifndef LOGOFADING_H
#define LOGOFADING_H

#include <tela.h>
#include <desenhavel.h>

class LogoFading : public Desenhavel
{
private:
	static const int DELAY_FRAMES_INCREMENTO_ALFA;
	static const int DELAY_FRAMES_INICIAR_INCREMENTO_ALFA;
	static const int QUANTIDADE_FRAMES_TERMINAR_FADING;
	int alpha;
	int incremento;

public:	
	LogoFading();
	~LogoFading();
	int desenhar();
	bool terminouFading();
};

#endif
