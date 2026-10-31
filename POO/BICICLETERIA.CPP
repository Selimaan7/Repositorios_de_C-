#include <iostream>
using namespace std;

class Producto {
public:
    virtual double getPrecio() = 0;
};

class Parte : public Producto {
private:
    double precio;

public:
    Parte(double p) : precio(p) {}

    double getPrecio() override {
        return precio;
    }
};

class Bicicleta : public Producto {
private:
    double precio;

public:
    Bicicleta(double p) : precio(p) {}

    double getPrecio() override {
        return precio;
    }
};

template <typename T>
class Gestora {
private:
    T elemento;

public:
    Gestora(T e) : elemento(e) {}

    T getElemento() {
        return elemento;
    }
};

int main() {
    Parte p(1500);
    Bicicleta b(3000);

    Gestora<Parte> g1(p);
    Gestora<Bicicleta> g2(b);

    cout << "Precio parte: " << g1.getElemento().getPrecio() << endl;
    cout << "Precio bicicleta: " << g2.getElemento().getPrecio() << endl;
}