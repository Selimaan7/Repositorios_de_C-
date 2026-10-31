#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void dividordearchivos (int n);

int main() {
    dividordearchivos(2);
}

void dividordearchivos (int n){
    ifstream file("archivo.txt");
    string pirulo; 
    int tizi = 0;

    
    while (getline(file, pirulo)){
        tizi ++;
    }

    int cant_arch = tizi / n;
    

    string palabra;
    for (int i = 0; i<n; i++){
        string nombre = "arch" + to_string(i) + ".txt";
        ofstream destino(nombre.c_str());        
        for (int j = 0; j<cant_arch; j++){
            getline(file,palabra);
            destino << pirulo;    
        }
        destino.close();
    }
    file.close();
}