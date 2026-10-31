#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <list>

using namespace std;

template <typename T>
class Lista_circular {
    private:
        list<T> lista;
        typename list<T>::iterator actual;
    public:
        Lista_circular() {
            actual = lista.end();
        }

        void agregar(const T& elemento) {
            lista.push_back(elemento);

            if (lista.size() == 1) {
                actual = lista.begin();
            }
        }

        bool esta_vacia() const {
            return lista.empty();
        }

        T& obtener_actual() const {
            return *actual;
        }

        void avanzar() {
            if (!esta_vacia()) {
                ++actual;
                if (actual == lista.end()) {
                    actual = lista.begin();
                }
            }
        }

        int cantidad_elementos() const {
            return lista.size();
        }
};