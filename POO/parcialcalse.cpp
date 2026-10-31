#include <iostream>

using namespace std;

class empresa{
    private: 
    cliente** clientes;
    int cant = 0;
    public:
    empresa ();
    void add (cliente c);
    void addpunto(int id, int puntos);
    char* mostrar(int id);
};


class cliente{
    private:
        int id;
        char* nombre;
        int puntaje;
    public:
        cliente(int ident, char* nom, int punt){
        }
        categoria *categoria = nullptr;
        void addpunto(int punto);
        void cambiocat();
};

class categoria{
    public: 
    virtual char*  beneficios() = 0;
};

class normal : public categoria{

};

class plata : public categoria{

};

class dorado : public categoria{

};
