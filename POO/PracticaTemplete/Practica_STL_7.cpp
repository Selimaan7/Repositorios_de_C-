#include <iostream>
#include <algorithm> // Para std::find_if
#include <map>
#include <cstdlib> // Para std::rand y std::srand
#include <string> // Para std::string
#include <numeric> // Para std::accumulate

using namespace std;

void cargar_bien(map<int, int>& mapa, int codigo, int valor) {
    mapa.insert(make_pair(codigo, valor));
}

int valor_bien(const map<int, int>& mapa, int codigo) {
    map<int, int>::const_iterator actual = mapa.find(codigo);
    if (actual != mapa.end()) {
        return actual->second;
    } else {
        cout << "No se encontro un bien con ese codigo." << endl;
        return -1; // Si no se encuentra el cÃ³digo, se devuelve -1
    }
}

float valor_total_bienes(const map<int, int>& mapa) {
   return accumulate(mapa.begin(), mapa.end(), 0.0f,
        [](float acumulado, const pair<int, int>& par) {
            return acumulado + par.second;
        });
}