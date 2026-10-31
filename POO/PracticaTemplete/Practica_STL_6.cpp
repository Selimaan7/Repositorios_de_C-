#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <list>

using namespace std;

template <typename T>
class Lista_doblemente_enlazada {
    private:
        list<T> lista;
        typename list<T>::iterator actual;
    public:
        Lista_doblemente_enlazada() {
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
                if (actual == lista.end()-1) {
                    cout << "Se ha llegado al final de la lista." << endl;
                } else {
                    ++actual;
                }
            }
        }

        void retroceder() {
            if (!esta_vacia()) {
                if (actual == lista.begin()) {
                    cout << "Se ha llegado al inicio de la lista." << endl;
                } else {
                    --actual;
                }
            }
        }

        int cantidad_elementos() const {
            return lista.size();
        }
};