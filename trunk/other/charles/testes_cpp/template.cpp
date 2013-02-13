#include <iostream>
#include <vector>
using namespace std;


class Pai{
public:
int num;
};
class Filho : public Pai {
public:
	Filho(int n){this->num = n;}
};

class Teste
{
public:
	template <class C>
	void remover(C a, Pai * p)
	{
		
		for(unsigned int i = 0; i < a->size(); i++)
			if(a->at(i) == p)
				a->erase(a->begin() + i);
		//cout << a->at(i) << " e " << p << endl;
	}
};

int main()
{
	Teste t;
	vector<Pai *> * v = new vector<Pai *>;
	Filho * f1 = new Filho(2);
	Filho * f2 = new Filho(3);
	v->push_back(f1);
	v->push_back(f2);
	cout << "Size antes: " << v->size() << endl;
	t.remover(v, f2);
	cout << "Size depois: " << v->size() << endl;
	return 0;
}
