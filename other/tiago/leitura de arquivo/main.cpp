#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(){

	char mapa[15*20];
	fstream leitor;
	leitor.open("map.map");
	int i = 0;
	char aux;
	
	for(i=0;i<(15*20);i++){
		aux = leitor.get();
		if(aux==32 || aux==10){
			i--;
		}
			
		else{
			mapa[i] = aux;
			cout << mapa[i];
		}

	}
	
	cout << "\n" << i <<"\n";
	
	return 0;
}