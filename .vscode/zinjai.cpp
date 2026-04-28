#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct servidor {
	int codigo, capacidad;
	string nombre, sede;
}
;
int main() {
	servidor lista[100];
	int i = 0;
	ifstream archivo;
	archivo.open("archivo.txt");
	if (archivo.is_open()) {
		cout << "El archivo se abrio correctamente" << endl;
		string linea;
		
	}
	else {
		cout << "El archivo no se pudo abrir" << endl;
	}
	while (archivo >> lista[i].codigo >> lista[i].nombre >> lista[i].capacidad >> lista[i].sede){
		cout << lista[i].codigo << "      " << lista[i].nombre << "      " << lista[i].capacidad << "      " << lista[i].sede << endl;
		i++;
	}
	return 0;
} 

