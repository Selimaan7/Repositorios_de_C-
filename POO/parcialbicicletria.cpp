#include <iostream>
#include <cstring>

using namespace std;

//////////////////////////////////////////////////////////////////////
// EJERCICIO (30): Vector dinamico con template
//
// Operadores que hay que sobrescribir para poder usar este vector:
//  - operator[]  -> para poder acceder/modificar un elemento dado su indice
//                   de forma comoda (ademas del metodo obtener()).
//  - operator==  -> tiene que estar definido para el tipo T que se guarde
//                   en el vector, porque eliminarocurrencias() necesita
//                   poder COMPARAR dos elementos T para saber cuales son
//                   "iguales" al que se quiere borrar. Con tipos basicos
//                   (int, float, char) ya viene definido; con clases
//                   propias hay que sobrecargarlo nosotros.
//////////////////////////////////////////////////////////////////////
template <typename T>
class vectordinamico{
private:
    T* datos;
    int cantidad;
    int capacidad;

    void crecer(){
        int nuevacapacidad = capacidad * 2;
        T* nuevoarreglo = new T[nuevacapacidad];
        for(int i = 0; i < cantidad; i++){
            nuevoarreglo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevoarreglo;
        capacidad = nuevacapacidad;
    }

public:
    vectordinamico(int capacidadinicial = 4): cantidad(0), capacidad(capacidadinicial){
        datos = new T[capacidad];
    }

    vectordinamico(const vectordinamico& other): cantidad(other.cantidad), capacidad(other.capacidad){
        datos = new T[capacidad];
        for(int i = 0; i < cantidad; i++){
            datos[i] = other.datos[i];
        }
    }

    vectordinamico& operator=(const vectordinamico& other){
        if(this != &other){
            delete[] datos;
            cantidad = other.cantidad;
            capacidad = other.capacidad;(
            datos = new T[capacidad];
            for(int i = 0; i < cantidad; i++){
                datos[i] = other.datos[i];
            }
        }
        return *this;
    }

    ~vectordinamico(){
        delete[] datos;
    }

    // Agregar un elemento
    void agregar(const T& elemento){
        if(cantidad == capacidad){
            crecer();
        }
        datos[cantidad++] = elemento;
    }

    // Obtener un elemento dado un indice
    T obtener(int indice) const{
        if(indice < 0 || indice >= cantidad){
            cout << "Indice fuera de rango\n";
            return T();
        }
        return datos[indice];)
    }

    // Acceso tipo arreglo (lectura/escritura)
    T& operator[](int indice){
        return datos[indice];
    }

    const T& operator[](int indice) const{
        return datos[indice];
    }

    // Eliminar todas las ocurrencias de un elemento determinado
    void eliminarocurrencias(const T& elemento){
        T* nuevoarreglo = new T[capacidad];
        int nuevacantidad = 0;
        for(int i = 0; i < cantidad; i++){
            if(!(datos[i] == elemento)){
                nuevoarreglo[nuevacantidad++] = datos[i];
            }
        }
        delete[] datos;
        datos = nuevoarreglo;
        cantidad = nuevacantidad;
    }

    int getcantidad() const{
        return cantidad;
    }
};

//////////////////////////////////////////////////////////////////////
// EJERCICIO (35): Diseno con polimorfismo
//
// Se puede (y conviene) usar polimorfismo: tanto "Parte" como "Bicicleta"
// son cosas que se pueden vender y tienen un precio, entonces las dos
// heredan de una clase abstracta comun "Elemento". Asi, "Oferta" guarda
// un vectordinamico<Elemento*> y no le importa si adentro hay partes o
// bicicletas: simplemente llama a elemento->precio() de forma polimorfica
// (patron "Composite").
//
// VENTAJA: Oferta queda generica y extensible. Si mañana aparece un nuevo
// tipo de producto (ej: "accesorio"), alcanza con crear una clase que
// herede de Elemento; no hay que tocar Oferta ni Bicicleta para nada.
// Se evita codigo repetido / switch de tipos.
//
// DESVENTAJA: Al trabajar con punteros a la clase base hay que manejar
// memoria dinamica a mano (new/delete, clonar() para hacer copias
// profundas), lo que agrega complejidad y riesgo de fugas de memoria si
// no se es prolijo con los destructores/constructores de copia. Ademas
// hay un pequeño costo en tiempo de ejecucion por el uso de funciones
// virtuales (vtable).
//////////////////////////////////////////////////////////////////////

class elemento{ 
public:
    virtual float precio() const = 0;
    virtual const char* getdescripcion() const = 0;
    virtual int getnumero() const = 0;
    virtual elemento* clonar() const = 0;
    virtual void mostrar() const = 0;
    virtual ~elemento() {}
};

class parte : public elemento{
private:
    int numero;
    char* descripcion;
    float preciounit;
public:
    parte(int numero = 0, const char* descripcion = "", float precio = 0)
        : numero(numero), preciounit(precio){
        this->descripcion = new char[strlen(descripcion) + 1];
        strcpy(this->descripcion, descripcion);
    }

    parte(const parte& other): numero(other.numero), preciounit(other.preciounit){
        descripcion = new char[strlen(other.descripcion) + 1];
        strcpy(descripcion, other.descripcion);
    }

    parte& operator=(const parte& other){
        if(this != &other){
            numero = other.numero;
            preciounit = other.preciounit;
            delete[] descripcion;
            descripcion = new char[strlen(other.descripcion) + 1];
            strcpy(descripcion, other.descripcion);
        }
        return *this;
    }

    ~parte(){
        delete[] descripcion;
    }

    float precio() const override{
        return preciounit;
    }

    const char* getdescripcion() const override{
        return descripcion;
    }

    int getnumero() const override{
        return numero;
    }

    elemento* clonar() const override{
        return new parte(*this);
    }

    void mostrar() const override{
        cout << "Parte #" << numero << " (" << descripcion << ") - $" << preciounit;
    }
};

class bicicleta : public elemento{
private:
    int numero;
    char* descripcion;
    vectordinamico<elemento*> partes;

    void liberarpartes(){
        for(int i = 0; i < partes.getcantidad(); i++){
            delete partes.obtener(i);
        }
    }

public:
    bicicleta(int numero = 0, const char* descripcion = "")
        : numero(numero){
        this->descripcion = new char[strlen(descripcion) + 1];
        strcpy(this->descripcion, descripcion);
    }

    bicicleta(const bicicleta& other): numero(other.numero){
        descripcion = new char[strlen(other.descripcion) + 1];
        strcpy(descripcion, other.descripcion);
        for(int i = 0; i < other.partes.getcantidad(); i++){
            partes.agregar(other.partes.obtener(i)->clonar());
        }
    }

    bicicleta& operator=(const bicicleta& other){
        if(this != &other){
            numero = other.numero;
            delete[] descripcion;
            descripcion = new char[strlen(other.descripcion) + 1];
            strcpy(descripcion, other.descripcion);

            liberarpartes();
            partes = vectordinamico<elemento*>();
            for(int i = 0; i < other.partes.getcantidad(); i++){
                partes.agregar(other.partes.obtener(i)->clonar());
            }
        }
        return *this;
    }

    ~bicicleta(){
        delete[] descripcion;
        liberarpartes();
    }

    // Dado un conjunto de partes se arma una bicicleta personalizada
    void agregarparte(elemento* p){
        partes.agregar(p->clonar());
    }

    float precio() const override{
        float total = 0;
        for(int i = 0; i < partes.getcantidad(); i++){
            total += partes.obtener(i)->precio();
        }
        return total;
    }

    const char* getdescripcion() const override{
        return descripcion;
    }

    int getnumero() const override{
        return numero;
    }

    elemento* clonar() const override{
        return new bicicleta(*this);
    }

    void mostrar() const override{
        cout << "Bicicleta #" << numero << " (" << descripcion << ") - $" << precio();
    }
};

class oferta{
private:
    int numero;
    vectordinamico<elemento*> elementos;

    void liberarelementos(){
        for(int i = 0; i < elementos.getcantidad(); i++){
            delete elementos.obtener(i);
        }
    }

public:
    oferta(int numero = 0): numero(numero){}

    oferta(const oferta& other): numero(other.numero){
        for(int i = 0; i < other.elementos.getcantidad(); i++){
            elementos.agregar(other.elementos.obtener(i)->clonar());
        }
    }

    oferta& operator=(const oferta& other){
        if(this != &other){
            numero = other.numero;
            liberarelementos();
            elementos = vectordinamico<elemento*>();
            for(int i = 0; i < other.elementos.getcantidad(); i++){
                elementos.agregar(other.elementos.obtener(i)->clonar());
            }
        }
        return *this;
    }

    ~oferta(){
        liberarelementos();
    }

    // La oferta es un conjunto de partes y/o bicicletas
    void agregarelemento(elemento* e){
        elementos.agregar(e->clonar());
    }

    // Precio = suma de los elementos que la componen, menos un 20%
    float precio() const{
        float total = 0;
        for(int i = 0; i < elementos.getcantidad(); i++){
            total += elementos.obtener(i)->precio();
        }
        return total * 0.8f;
    }

    int getnumero() const{
        return numero;
    }

    // EJERCICIO (20): imprimir elementos separados por coma y precio total
    friend ostream& operator<<(ostream& os, const oferta& of){
        os << "Oferta #" << of.numero << ": ";
        for(int i = 0; i < of.elementos.getcantidad(); i++){
            os << of.elementos.obtener(i)->getdescripcion();
            if(i < of.elementos.getcantidad() - 1){
                os << ", ";
            }
        }
        os << " - Precio total: $" << of.precio();
        return os;
    }
};

// Clase "administradora", analoga a tu "curso"
class bicicleteria{
private:
    vectordinamico<oferta*> ofertas;

public:
    ~bicicleteria(){
        for(int i = 0; i < ofertas.getcantidad(); i++){
            delete ofertas.obtener(i);
        }
    }

    void agregaroferta(const oferta& of){
        ofertas.agregar(new oferta(of));
    }

    void listarofertas() const{
        cout << "\n--- Listado de ofertas ---\n";
        for(int i = 0; i < ofertas.getcantidad(); i++){
            cout << *ofertas.obtener(i) << "\n";
        }
    }
};

int main(){

    cout << "--- Prueba del vector dinamico (ejercicio 30) ---\n";
    vectordinamico<int> numeros;
    numeros.agregar(10);
    numeros.agregar(20);
    numeros.agregar(30);
    numeros.agregar(20);
    numeros.agregar(40);

    cout << "obtener(2): " << numeros.obtener(2) << "\n";
    cout << "operator[](3): " << numeros[3] << "\n";

    numeros.eliminarocurrencias(20);
    cout << "Despues de eliminar todas las ocurrencias de 20: ";
    for(int i = 0; i < numeros.getcantidad(); i++){
        cout << numeros[i] << " ";
    }
    cout << "\n";

    cout << "\n--- Bicicleteria Oro Verde (ejercicios 35 y 20) ---\n";

    parte cuadro(1, "Cuadro aluminio", 15000);
    parte ruedas(2, "Par de ruedas", 8000);
    parte manubrio(3, "Manubrio", 2500);
    parte asiento(4, "Asiento", 1800);

    bicicleta bici1(101, "Bicicleta urbana");
    bici1.agregarparte(&cuadro);
    bici1.agregarparte(&ruedas);
    bici1.agregarparte(&manubrio);

    bicicleta bici2(102, "Bicicleta de montania");
    bici2.agregarparte(&cuadro);
    bici2.agregarparte(&ruedas);
    bici2.agregarparte(&asiento);

    oferta oferta1(1);
    oferta1.agregarelemento(&bici1);
    oferta1.agregarelemento(&asiento);

    oferta oferta2(2);
    oferta2.agregarelemento(&bici1);
    oferta2.agregarelemento(&bici2);
    oferta2.agregarelemento(&manubrio);

    bicicleteria oroverde;
    oroverde.agregaroferta(oferta1);
    oroverde.agregaroferta(oferta2);

    oroverde.listarofertas();

    return 0;
}