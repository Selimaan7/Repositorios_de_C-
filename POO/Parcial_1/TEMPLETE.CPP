#include <iostream>
using namespace std;

template <typename T>
class VectorDinamico {
private:
    T* datos;
    int capacidad;
    int cantidad;

    void redimensionar() {
        int nuevaCapacidad = capacidad * 2;
        T* nuevo = new T[nuevaCapacidad];

        for (int i = 0; i < cantidad; i++) {
            nuevo[i] = datos[i];
        }

        delete[] datos;
        datos = nuevo;
        capacidad = nuevaCapacidad;
    }

public:
    VectorDinamico(int capInicial = 10) : capacidad(capInicial), cantidad(0) {
        datos = new T[capacidad];
    }

    ~VectorDinamico() {
        delete[] datos;
    }

    void agregardato(const T& nuevodato) {
        if (cantidad == capacidad) {
            redimensionar();
        }

        datos[cantidad++] = nuevodato;
    }

    T& operator[](int indice) {
        return datos[indice];
    }

    int getCantidad() const {
        return cantidad;
    }
};

int main() {
    VectorDinamico<int> v;

    v.agregardato(10);
    v.agregardato(20);
    v.agregardato(30);

    cout << "Cantidad: " << v.getCantidad() << endl;
    cout << "Primer elemento: " << v[0] << endl;

    return 0;
}