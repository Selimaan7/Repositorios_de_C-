#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int main() {
    vector<int> mm;
    mm.reserve(200);
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < 200; ++i) {
        mm.push_back(rand());
    }

    // Usar algoritmo: ordenar
    sort(mm.begin(), mm.end());

    // Mostrar (10 por línea)
    for (size_t i = 0; i < mm.size(); ++i) {
        cout << mm[i];
        if ((i + 1) % 10 == 0) cout << '\n';
        else cout << ' ';
    }

    return 0;
}