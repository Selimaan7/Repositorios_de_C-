#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void aniadirtexto();

int main(){
    aniadirtexto();
    return 0;
}

void aniadirtexto(){
    ofstream arch;
    string texto;
    arch.open("hola.txt", ios::app);
    if (arch.fail()){
        cout << "el archivo que se intento abrir no se ha logrado"<< endl;
        return;
    }
    cout << "ingrese el texto a añadir"<<endl;
    getline(cin,texto);
    arch << texto << endl;
    arch.close();
}