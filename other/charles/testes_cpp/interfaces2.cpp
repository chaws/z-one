#include <iostream>

class Desenhavel
{
public:
	int x;
	int y;
	virtual void desenhar();
};

class Movimentavel : public Desenhavel
{
public:
	int xvel;
	int yvel;
	virtual void movimentar() = 0;
};

class Escutavel : public Desenhavel
{
public:
	virtual void detectarEvento() = 0;
};

class Botao : Movimentavel, Escutavel
{
public:
	void desenhar()
	{
		std::cout << "funfou!!!" << std::endl;
	}

	void detectarEvento()
	{

	}

	void movimentar()
	{

	}
};

int main()
{
	Botao b;
	b.desenhar();
	return 0;
}
