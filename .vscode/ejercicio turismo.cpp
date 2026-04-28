#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
float preciodesc;
string destino, nombre;
float descuento20 = 0.80, descuento5 = 0.95;
float precio, preciofinal, cantidadKM, cantidadKMtotal, aux, descuentoaplicado;
cout << "Bienvendio al sistema de vviajes de turismo por favor ingrese sus datos" << endl;
cout << "Ingrese su nombre: " << endl;
getline(cin, nombre);
cout << "Ingrese la cantidad de KM recorridos hasta el momento: " << endl;
cin >> cantidadKMtotal;
cout << "Ingrese el destino: " << endl;
cin >> destino;
cout << "Ingrese el precio del viaje: " << endl;
cin >> precio;
cout << "Ingrese la cantidad de kilometros que tiene el viaje " << endl;
cin >> cantidadKM;
aux = cantidadKMtotal + cantidadKM;
if (aux >= 3000) {
    preciofinal = precio * descuento20;
} else {
    preciofinal = precio * descuento5;
}
descuentoaplicado = precio - preciofinal;

cout << endl;
cout << "señor: " << nombre << setw(10) << "lleva un total de kilomtros de: " << aux << endl;
cout << "datos del vaieje;"<< setw(20) << "Destino: " << destino << setw(10) << "KM: " << cantidadKM << setw(10) << "precio: " << precio << endl;
cout << "descuento: " << descuentoaplicado << setw(10) << "total a pagar: " << preciofinal << endl;

return 0;
}