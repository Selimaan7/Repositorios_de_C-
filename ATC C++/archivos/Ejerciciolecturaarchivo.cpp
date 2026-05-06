#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/*int main (){
    ifstream arch;
    string texton;

    arch.open("hola.txt", ios::in);

    if (arch.fail()){
        cout << "no se pudo abrir el archivo";
    }
    while (!arch.eof()){
        getline (arch,texton);
        cout << texton << endl;
    }
}*/

void lectura();

int main (){
    lectura();


    return 0;
}
void lectura (){
    ifstream arch;
    string archivo;
    string textito;
    
    cout << "indique el lugar o archivo a leer" << endl;
    cin >> archivo;
    
    

    arch.open(archivo.c_str(),ios::in);

    if (arch.fail()){
        cout  << "no se puedo abrir el archivo" << endl;
    }
    
    while (!arch.eof()){
        getline (arch,textito);
        cout << textito << endl;
    }
}