#include <iostream>
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
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
    }
    else {
        cout << "El archivo no se pudo abrir" << endl;
    }
    return 0;
} 
