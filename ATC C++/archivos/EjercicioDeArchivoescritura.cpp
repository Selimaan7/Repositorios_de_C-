#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void escritura ();

int main(){

    escritura();

return 0;
}

void escritura (){
    int cant = 0;
    string nombredearchivo;
    
    ofstream arch;
    
    cout << "ingrese el nombre del archivo que desea abrir o crear: "<<endl;
    getline(cin,nombredearchivo);

    arch.open(nombredearchivo.c_str(),ios::out);
    
    if (arch.fail()){
        cout<< "no se a podido abrir";
    }else{
        cout << "Se a abirto correctamente"<< endl;
    }
    cout<< "cuantas frases va a querer ingresar?"<< endl;
    cin >> cant;
    cin.get();
    for (int i = 0; i<cant; i ++){
        string frase;
        getline (cin,frase);
        arch << frase << endl;
    }
    //arch<< "hola como estas";
}