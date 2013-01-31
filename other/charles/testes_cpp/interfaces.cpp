#include <iostream>

using namespace std;

class Interface
{
	public:
		Interface ()
		{
			cout << "Instanciando interface" << endl;
		}
};

class Pai
{
	public:
		Pai()
		{
			cout << "Instanciando pai" << endl;
		}
};

/*
*	Pelos testes, primeiro é executado o construtor da classe mais a esquerda, indo depois pra direita
*/
class Normal: Interface, Pai
{
	public:
		Normal()
		{
			cout << "Instanciando normal" << endl;
		}
	
		void teste()
		{
			cout << "Chamando teste" << endl;
		}
};

int main(int argc, char ** argv)
{

	Normal * n = new Normal();
	n->teste();
	
	return 0;
}

