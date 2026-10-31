#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    vector<int> lista_enteros;

    srand(time(0));
    
    cout << "Lista Original:\n";
    for (int i = 0; i < 200; ++i) {
        int num = rand() % 1000;
        lista_enteros.push_back(num);
        cout << num << " ";
    }
    cout << "\n\n";

    // Las posiciones 11 a 150 se representan con los indices 10 a 149.
    // El segundo iterador marca el limite y no se incluye.
    sort(lista_enteros.begin() + 10, lista_enteros.end() - 50);

    cout << "Ordenada sin modificar los primeros 10 ni los ultimos 50:\n";
    for (int numero : lista_enteros) {
        cout << numero << " ";
    }
    cout << "\n\n";

    sort(lista_enteros.begin(), lista_enteros.end(), 
        [](int a, int b) {
            return a > b;
        });

    cout << "Lista completa en orden descendente:\n";
    for (int numero : lista_enteros) {
        cout << numero << " ";
    }
    cout << "\n";
}