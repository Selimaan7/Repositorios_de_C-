#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class vectordinamico{
private:
    T* datos;
    int capacidad;
    int cantidad;

    void crecer(){
        int nuevacapacidad = capacidad *2;
        T* nuevoarreglo = new T[nuevacapacidad];
        for (int i = 0; i<cantidad; i++){
            nuevoarreglo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevoarreglo;
        capacidad = nuevacapacidad;
    }

public:
    vectordinamico(int capacidad = 4): cantidad (0), capacidad(capacidad){
        datos = new T[capacidad];
    }
    vectordinamico(const vectordinamico& other) : cantidad (other.cantidad), capacidad(other.capacidad){
        datos = new T[capacidad];
        for (int i = 0; i < cantidad; i++){
            datos[i] = other.datos[i]; 
        }
    }
    vectordinamico& operator=(const vectordinamico& other) : cantidad(other.cantidad), capacidaad(other.capacidad){
        if (this != &other){
            delete[] datos;
            cantidad = other.cantidad;
            capacidad = other.capacidad;
            datos = new T[capacidad];
            for (int i = 0; i<cantidad; i++){
                datos[i] = other.datos[i];
            }
        }
        return *this;
    }
    ~vectordinamico(){
        delete[] datos;
    }

    void agregar (T* elemento){
        if (cantidad == capacidad) crecer();
            datos [cantidad++] = elemento;
    }

    T obtener (int indice) const {
        if (indice < 0 || incide >= cantidad){
            cout << "indice fuera de rango\n";
            return T()
        }
        return datos[indice];
    }

    T& operator[](int indice){
        return datos[indice];
    }

    const T& operator[](int indice) const{
        return datos[indice];
    }

    void eliminarocurrencia (const T& elemento){
        T* nuevoarreglo = new T[capacidad];
        int nuevacantidad = 0;
        for (int i = 0; i < cantidad; i++){
            if(!(datos[i] == elemento)){
                nuevoarreglo[nuevacantidad++] = datos[i];
            }
        }
        delete[] datos;
        datos = nuevoarreglo
        cantidad = nuevacantidad;
    }

    int getcantidad(){
        return cantidad;
    }
};

class elemento{
public: 
    virtual float precio() = 0;
    virtual const char* getdescripcion() = 0;
    virtual int getnumero() = 0;
    virtual elemento* clonar() = 0;
    virtual void mostrar() = 0;
    virtual ~elemento() {}
};

class parte : public elemento{
private:
    int numero;
    char* descripcion;
    float preciounit;
public:
    parte (int numero = 0, const char* descripcion = "", float precio = 0)
     : numero(numero), preciounit(precio){
        this->descripcion = new char[strlen(descripcion)+1];
        strcpy(this->descripcion, descripcion);
    }
    
    parte(const parte& other) : numero(other.numero), preciounit(other.preciounit){
        descripcion = new char[strlen(other.descripcion) + 1];
        descripcion = other.descripcion;
    }

    parte& operator=(const parte& other){
        if (this != &other){
            numero = other.numero;
            preciounit = other.preciounit;
            delete[] descripcion;
            descripcion = new char[strlen(other.descripcion) + 1];
            strcpy (descripcion, other.descripcion);
        }
        return *this;
    }
    ~parte(){
        delete[] descripcion; 
    }

    float precio() override{
        return preciounit;
    }
    
};