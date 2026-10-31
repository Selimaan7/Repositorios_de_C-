#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>


using namespace std;

struct Producto{
    int codigo;
    char nombre[50];
    char marca[20];
    double precio; 
    char tipo;
};

class Electrodomestico {
    private:
        int codigo;
        char nombre[50];
        char marca[20];
        double precio;

    public:
        Electrodomestico () : codigo (0), precio(0){
            marca[0] = '\n';
            nombre[0] = '\n';
        }

        Electrodomestico(int c, const char* n, const char* m, double p) : codigo(c), precio(p){
            strcpy (marca, n);
            strcpy (marca, m);
        }

        ~Electrodomestico() {}

        void set_codigo (int c) {
            codigo = c;  
        }
        void set_nombre(const char* n){
            strcpy (nombre, n);
        }
        void set_marca (const char* m){
            strcpy(marca, m);
        }
        void set_precio(double p){
            precio = p;
        }

        int get_codigo(){
            return codigo;
        }
        const char* get_nombre(){
            return nombre;
        }
        const char* get_marca(){
            return marca;
        }
        double get_precio(){
            return precio;
        }

        void mostrar_electrodomestico(){
           
            cout << "Codigo: " << codigo << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Marca: " << marca << endl;
            cout << "Precio: $" << precio << endl;
        }
        

        virtual char get_tipo() = 0;
        virtual void actualizar_precio() = 0;
};



class Nacional : public Electrodomestico{
    private:

    public:
        Nacional() : Electrodomestico() {}

        Nacional(int c, const char* n, const char* m, double p) : Electrodomestico(c,n,m,p){}

        void mostrar_nacional(){
            cout << "Producto Nacional: " << endl;
            mostrar_electrodomestico();
        }

        void actualizar_precio(){
            double precio_actual = get_precio();
            double nuevo_precio = precio_actual * 1.02;
            set_precio(nuevo_precio);
        }

        char get_tipo(){
            return 'N';
        }
};

class Importado : public Electrodomestico{
    private: 

    public:
        Importado() : Electrodomestico(){}

        Importado(int c, char*n, const char*m, double p) : Electrodomestico(c,n,m,p){}

        void mostrar_importado(){
            cout << "Producto Importado: " << endl;
            mostrar_electrodomestico();
        }

        void actualizar_precio(){
            double incremento_dolar;
            cin >> incremento_dolar;
            double precio_actual = get_precio();
            double nuevo_precio = precio_actual * (incremento_dolar/100 + 1.0);
            set_precio(nuevo_precio);
        }

        char get_tipo() override{
            return 'I';
        }
};  

class Jardin : public Electrodomestico{
    private:

    public:
        Jardin() : Electrodomestico(){}
        
        Jardin(int c, char* n, char* m, double p) : Electrodomestico(c,n,m,p){}

        void mostrar_jardin(){
            cout << "Producto de Jardin: " << endl;
            mostrar_electrodomestico();
        }


        void actualizar_precio(){
            double precio_actual = get_precio();
            double nuevo_precio = precio_actual * 1.0083;
            set_precio (nuevo_precio);
        }

        char get_tipo() override{
            return 'J'; 
        }
};

class GestorElectrodomesticos{
    private:
        vector<Electrodomestico*> productos;
    public:
        GestorElectrodomesticos(){}

        ~GestorElectrodomesticos(){
            while(productos.empty()){
                productos.pop_back();
            }
        }

        void agregar_productos(Electrodomestico* producto){
            productos.push_back(producto);
        }

        void mostrar_productos() const{
            for (const auto& pord : productos){
                pord->mostrar_electrodomestico();
                cout << endl;
            }
        }

        void actualizar_precios(){
            for(auto& prod : productos){
                prod->actualizar_precio();
            }
        }


        void actualizar_precios_archivo_b(){
            ifstream archivo("productos.txt", ios::in | ios::binary);
            if(!archivo.good()){
                cout << "No se puedo abrir el archivo para leer." << endl;
                return;
            }
            Producto p;
            while (archivo.read((char*)&p, sizeof(Producto))){
                if (p.tipo == 'N'){
                    Nacional* nacional = new Nacional(p.codigo, p.nombre, p.marca, p.precio);
                    nacional->actualizar_precio();
                    agregar_productos(nacional);
                }   else if (p.tipo = 'I'){
                        Importado* importado = new Importado(p.codigo, p.nombre, p.marca, p.precio);
                        importado->actualizar_precio();
                        agregar_productos(importado);
                    }   else if(p.tipo == 'J'){
                            Jardin* jardin = new Jardin (p.codigo, p.nombre, p.marca, p.precio);
                            jardin->actualizar_precio();
                            agregar_productos(jardin);
                        }   
                
            }
            archivo.close();

            ofstream nuevo_archivo("productos_actualizados.dat", ios::out | ios::binary);
            if (!nuevo_archivo.good()) {
                cout << "No se pudo abrir el archivo para escribir." << endl;
                return;
            }

            Producto p_actu;

            for (const auto& prod : productos){
                p_actu.codigo = prod->get_codigo();
                strcpy(p_actu.nombre, prod->get_nombre());
                strcpy(p_actu.marca, prod->get_marca());
                p_actu.precio = prod->get_precio();
                p_actu.tipo = prod->get_tipo();

                nuevo_archivo.write((char*)&p_actu, sizeof(Producto));
            }

            nuevo_archivo.close();

        }

        void generar_archivo_ordenado(){
            ifstream arch("productos.txt", ios::in | ios::binary);
            if (!arch) {
                cout << "No se pudo abrir el archivo para leer." << endl;
                return;
            }

            vector <Producto> prods;
            Producto prod;
            while (arch.read((char*)&prod, sizeof(Producto))){
                prods.push_back(prod);
            }
            arch.close();

            sort(prods.begin(), prods.end(), 
                [](const Producto& prods1, const Producto& prods2){
                    return prods1.nombre < prods2.nombre;
                });

            ofstream arch_act("Productos_ordenados.txt", ios::out);
            if (!arch_act) {
                cout << "No se pudo abrir el archivo para escribir." << endl;
                return;
            }

            for (const auto& p : prods){
                arch_act << "Nombre : " << p.nombre << " Marca: " << p.marca << "---------------------$" << p.precio << endl;
            }
            arch_act.close();
        }

        void mostrar_cantidad_xmarca(){
            map <string, int> cantidades;

            for (auto& prod : productos){
                cantidades[prod->get_marca()] ++;
            }

            for (const auto& par : cantidades){
                cout << "Marca: " << par.first << ", Cantidades" << par.second << endl;
            }
        }

        void producto_caro(){
            if (productos.empty()){
                cout << "No hay ningun producto cargado" << endl;
                return;
            }

            vector <Electrodomestico*> producto_caro= productos;
            sort (producto_caro.begin(), producto_caro.end(), [](Electrodomestico* a, Electrodomestico* b){
                return a->get_precio() > b->get_precio();
            });

            cout << "El producto mas caro es: " << producto_caro.front()->get_nombre() << "-- $" << producto_caro.back()->get_precio() << endl;
        }

        void producto_barato(){
            if (productos.empty()){
                cout << "No hay ningun producto cargado" << endl;
                return;
            }

            vector <Electrodomestico*> producto_barato = productos;
            sort (producto_barato.begin(), producto_barato.end(), [](Electrodomestico* a, Electrodomestico* b){
                return a->get_precio() < b->get_precio();
            });
            cout << "Nombre: " << producto_barato.front()->get_nombre() << "Precio: " << producto_barato.front()->get_precio() << endl;
        }
};