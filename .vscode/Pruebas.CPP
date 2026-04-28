#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "hola, ppor favor ingrese el monto a convertir" << endl;
    int monto;
    float dolar, euro, libra;
    cin >> monto;
    dolar = monto / 1500;
    euro = monto / 1200;
    libra = monto / 1000;
    cout << "el monto en dolares es: " << dolar << endl;
    cout << "el monto en euros es: " << euro << endl;
    cout << "el monto en libras es: " << libra << endl;
    return 0; 
}