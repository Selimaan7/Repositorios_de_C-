#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

void contar_letras(const string& texto, map<char, int>& conteo) {
    for (char letra : texto) {
        if (isalpha(letra)) {
            ++conteo[tolower(letra)];
        }
    }

    cout << "Veces que se repiten: " << endl;
    int cantidad_letras = 0;
    for (const auto& par : conteo) {
        cantidad_letras += par.second;
        cout << par.first << ": " << par.second << endl;
    }
    cout << "Cantidad de letras: " << cantidad_letras << endl;
}