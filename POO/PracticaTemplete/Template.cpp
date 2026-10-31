// Ejercicio 1: una clase template que representa un vector dinamico.

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class VectorDinamico {
private:
    T* elementos_;
    int cantidad_;
    int capacidad_;

    void reservar(int nueva_capacidad) {
        T* nuevos_elementos = new T[nueva_capacidad];

        for (int i = 0; i < cantidad_; ++i) {
            nuevos_elementos[i] = elementos_[i];
        }

        delete[] elementos_;
        elementos_ = nuevos_elementos;
        capacidad_ = nueva_capacidad;
    }

public:
    VectorDinamico()
        : elementos_(nullptr), cantidad_(0), capacidad_(0) {
    }

    ~VectorDinamico() {
        delete[] elementos_;
    }

    VectorDinamico(const VectorDinamico& otro)
        : elementos_(nullptr), cantidad_(0), capacidad_(0) {
        if (otro.capacidad_ > 0) {
            elementos_ = new T[otro.capacidad_];
            capacidad_ = otro.capacidad_;

            for (int i = 0; i < otro.cantidad_; ++i) {
                elementos_[i] = otro.elementos_[i];
            }

            cantidad_ = otro.cantidad_;
        }
    }

    VectorDinamico& operator=(const VectorDinamico& otro) {
        if (this != &otro) {
            VectorDinamico copia(otro);
            intercambiar(copia);
        }

        return *this;
    }

    void push_back(const T& elemento) {
        if (cantidad_ == capacidad_) {
            const int nueva_capacidad =
                capacidad_ == 0 ? 1 : capacidad_ * 2;
            reservar(nueva_capacidad);
        }

        elementos_[cantidad_] = elemento;
        ++cantidad_;
    }

    void pop_back() {
        if (empty()) {
            throw "No se puede quitar un elemento de un vector vacio";
        }

        --cantidad_;
    }

    T& operator[](int indice) {
        if (indice < 0 || indice >= cantidad_) {
            throw "Indice fuera de rango";
        }

        return elementos_[indice];
    }

    const T& operator[](int indice) const {
        if (indice < 0 || indice >= cantidad_) {
            throw "Indice fuera de rango";
        }

        return elementos_[indice];
    }

    int size() const {
        return cantidad_;
    }

    bool empty() const {
        return cantidad_ == 0;
    }

    void intercambiar(VectorDinamico& otro) {
        T* elementos_temporales = elementos_;
        elementos_ = otro.elementos_;
        otro.elementos_ = elementos_temporales;

        int cantidad_temporal = cantidad_;
        cantidad_ = otro.cantidad_;
        otro.cantidad_ = cantidad_temporal;

        int capacidad_temporal = capacidad_;
        capacidad_ = otro.capacidad_;
        otro.capacidad_ = capacidad_temporal;
    }
};

template <typename T>
class Lista {
    private:
        struct Nodo {
            T elemento;
            Nodo* siguiente;
        };
        Nodo* elementos;
        int cantidad;
    public:
        Lista() : elementos(nullptr), cantidad(0) {}
        ~Lista() {
            while (elementos) {
                Nodo* temp = elementos;
                elementos = elementos->siguiente;
                delete temp;
            }
        }

        void agregar(const T& elemento) {
            Nodo* nuevo_nodo = new Nodo{elemento, nullptr};
            if (!elementos) {
                elementos = nuevo_nodo;
            } else {
                Nodo* actual = elementos;
                while (actual->siguiente != nullptr) {
                    actual = actual->siguiente;
                }
                actual->siguiente = nuevo_nodo;
            }
            ++cantidad;
        }

        int size() const { return cantidad; }

        T& operator[](int indice) {
            if (indice < 0 || indice >= cantidad) {
                throw "Indice fuera de rango";
            }
            Nodo* actual = elementos;
            for (int i = 0; i < indice; ++i) {
                actual = actual->siguiente;
            }
            return actual->elemento;
        }
};

int main() {
    VectorDinamico<int> enteros;
    enteros.push_back(10);
    enteros.push_back(20);
    enteros.push_back(30);

    cout << "Vector de enteros: ";
    for (int i = 0; i < enteros.size(); ++i) {
        cout << enteros[i] << ' ';
    }
    cout << "\n";

    VectorDinamico<string> nombres;
    nombres.push_back("Ana");
    nombres.push_back("Bruno");

    cout << "Vector de strings: ";
    for (int i = 0; i < nombres.size(); ++i) {
        cout << nombres[i] << ' ';
    }
    cout << "\n";

    VectorDinamico<int> copia = enteros;
    copia[0] = 99;
    cout << "Original: " << enteros[0] << "\n";
    cout << "Copia modificada: " << copia[0] << "\n";

    return 0;
}