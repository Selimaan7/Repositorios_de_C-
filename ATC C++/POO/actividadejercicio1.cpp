#include <iostream>
#include <string>

using namespace std;

class Rectangulo {
    //atributos
    private:
        int largo;
        int ancho;
    //metodos
    public:
        Rectangulo (int, int);
        float area();
        float perimetro();
};

Rectangulo::Rectangulo (int _largo,int _ancho){
    largo = _largo;
    ancho = _ancho;
}

float Rectangulo::perimetro (){
    return 2*(ancho + largo);
}

float Rectangulo::area(){
    return ancho * largo;
}

int main (){
    Rectangulo p1(5,7);
    cout << "el area del rectangulo es de "<< p1.area() << endl;
    cout << "el perimetro del rectangulo es de " << p1.perimetro() << endl;
    return 0;
}