#include <iostream>
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
    if (archivo.is_open()){
        cout << "el archivo se abrio correctamente" << endl;;
        while (archivo >> lista[i].codigo >> lista[i].nombre >> lista[i].capacidad >> lista[i].sede){
            cout << "codigo: " << lista[i].codigo << " nombre: " << lista[i].nombre << " capacidad: " << lista[i].capacidad << " sede: " << lista[i].sede << endl;
            i++;
        }
    }
    else {
        cout << "el archivo no se pudo abrir" << endl;
    }
    for (int j = 0; j < i; j++){
        cout << "codigo: " << lista[j].codigo << " nombre: " << lista[j].nombre << " capacidad: " << lista[j].capacidad << " sede: " << lista[j].sede << endl;
    }
    

return 0;
}