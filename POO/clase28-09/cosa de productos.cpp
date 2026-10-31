#include <iostream>
#include <vector>
#include <string>

using namespace std;

class empresa{
    private:
};


struct{
    int codigo;
    char nombre[50];
    char marca[50];
    double precio;
};
class producto {
private:
    int codigo;         //todos los gettter y setters
    string nombre;      //todos los gettter y setters
    string marca;       //todos los gettter y setters
    double precio;      //todos los gettter y setters3
public:
    producto(int codigo);

};


class inter : public producto{
private:
    double DolarAnt;
    double DolarAct;
public:
    inter(int  codigo) : producto (codigo){}
    void CambiarPrecio(){
        auto precio = THIS->precio * this->-      
    }
};