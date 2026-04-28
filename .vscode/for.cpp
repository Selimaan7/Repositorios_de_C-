#include <iostream>
using namespace std;

int sumar (int b, int a){
    return a + b;
}
void ordenarporsaldo (int saldo[], int clientes){
    for (int i = 0; i < clientes; i++){
        for (int j = i + 1; j < clientes; j++){
            if (saldo[i] > saldo[j ]){
                int temp = saldo[i];
                saldo[i] = saldo[j];
                saldo[j] = temp;
            }
        }
    }





}
int main() {


    int saldo[] = {5,6,9,8,7,2,3,4,1};
    int clientes = 9;
    ordenarporsaldo(saldo, clientes);
    for (int i = 0; i < clientes; i++){
        cout << saldo[i] << " " << endl;
    }
    ordenarporsaldo(saldo, clientes);
    return 0;
}
