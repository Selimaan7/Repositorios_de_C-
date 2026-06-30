#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ingresar_texto(string palabra);
void Agregar_Texto (string palabra);
void leerarchivo (string nombrearch);

int main (){
    string palabra, nombrearch;

    cout << "nombre de la palabra a ingresar"<< endl;
    getline(cin, palabra);

    cout << "nombre del archivo a leer"<< endl;
    getline (cin, nombrearch);

    //Agregar_Texto (palabra);

    //ingresar_texto(palabra);
    leerarchivo (nombrearch);
}
void Agregar_Texto (string palabra){
    ofstream arch;

    arch.open("arch.txt", ios::app);

    if (!arch.fail())cout << "se abrio correctamente";

    arch << palabra;
    arch.close();

}

void ingresar_texto(string palabra){
    
    ofstream arch;

    arch.open("arch.txt", ios::out);
    
    if (arch.fail()) cout << "el archivo no se abrio correctamente";
    arch << palabra;
    arch.close();
}

void leerarchivo (string nombrearch){
    ifstream arch;
    string palabra;

    arch.open(nombrearch.c_str(), ios::in);
    if (arch.fail()) cout << "el archivo no se udo abrir correctamente";

    getline (arch,palabra);

    while (!arch.eof()){
        cout << palabra << "\n";
        getline (arch,palabra);
    }
}