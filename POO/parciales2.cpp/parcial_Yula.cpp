#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

struct Producto {
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
        Electrodomestico() : codigo(0), precio(0.0) {
            nombre[0] = '\0';
            marca[0] = '\0';
        }

        Electrodomestico(int c, const char* n, const char* m, double p) : codigo(c), precio(p) {
            strncpy(nombre, n, sizeof(nombre));
            nombre[sizeof(nombre)-1] = '\0';
            strncpy(marca, m, sizeof(marca));
            marca[sizeof(marca)-1] = '\0';
        }

        ~Electrodomestico() {}

        void set_codigo(int c) { codigo = c; }
        void set_nombre(const char* n) { strncpy(nombre, n, sizeof(nombre)); nombre[sizeof(nombre)-1] = '\0'; }
        void set_marca(const char* m) { strncpy(marca, m, sizeof(marca)); marca[sizeof(marca)-1] = '\0'; }
        void set_precio(double p) { precio = p; }

        int get_codigo() const { return codigo; }
        const char* get_nombre() const { return nombre; }
        const char* get_marca() const { return marca; }
        double get_precio() const { return precio; }

        void mostrar_electrodomestico() const {
            cout << "Codigo: " << codigo << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Marca: " << marca << endl;
            cout << "Precio: $" << precio << endl;
        }

        virtual char get_tipo() const = 0; // Método virtual puro para obtener el tipo de electrodoméstico
        virtual void actualizar_precio() = 0; // Método virtual puro para actualizar el precio
};

class Nacional : public Electrodomestico {
    public:
        Nacional() : Electrodomestico() {}

        Nacional(int c, const char* n, const char* m, double p) : Electrodomestico(c, n, m, p) {}

        void mostrar_nacional() const {
            cout << "Producto Nacional:" << endl;
            mostrar_electrodomestico();
        }

        void actualizar_precio() {
            double precio_actual = get_precio();
            double nuevo_precio = precio_actual * 1.02; // Incremento del 2% mensual
            set_precio(nuevo_precio);
        }

        char get_tipo() const override {
            return 'N';
        }
};

class Importado : public Electrodomestico {
    public:
        Importado() : Electrodomestico() {}

        Importado(int c, const char* n, const char* m, double p) : Electrodomestico(c, n, m, p) {}

        void mostrar_importado() const {
            cout << "Producto Importado:" << endl;
            mostrar_electrodomestico();
        }

        void actualizar_precio() {
            double incremento_dolar;
            cin >> incremento_dolar; // Se ingresa el incremento del dolar en porcentaje
            double precio_actual = get_precio();
            double nuevo_precio = precio_actual * (incremento_dolar/100.0 + 1.0); // Depende del incremento del dolar
            set_precio(nuevo_precio);
        }

        char get_tipo() const override {
            return 'I';
        }
};

class Jardin : public Electrodomestico {
    public:
        Jardin() : Electrodomestico() {}

        Jardin(int c, const char* n, const char* m, double p) : Electrodomestico(c, n, m, p) {}

        void mostrar_jardin() const {
            cout << "Producto de Jardin:" << endl;
            mostrar_electrodomestico();
        }

        void actualizar_precio() {
            double precio_actual = get_precio();
            double nuevo_precio = precio_actual * 1.0083; // Incremento del 0.83% mensual
            set_precio(nuevo_precio);
        }

        char get_tipo() const override {
            return 'J';
        }
};

class GestorElectrodomesticos {
    private:
        vector<Electrodomestico*> productos;
    public:
        GestorElectrodomesticos() {}

        ~GestorElectrodomesticos() {
            while (!productos.empty()) {
                productos.pop_back();
            }
        }

        void agregar_producto(Electrodomestico* producto) {
            productos.push_back(producto);
        }

        void mostrar_productos() const {
            for (const auto& producto : productos) {
                producto->mostrar_electrodomestico();
                cout << endl;
            }
        }

        void actualizar_precios() {
            for (auto& producto : productos) {
                producto->actualizar_precio();
            }
        }

        void actualizar_precios_archivo_b() {
            ifstream archivo("productos.dat", ios::in | ios::binary);
            if (!archivo) {
                cout << "No se pudo abrir el archivo para leer." << endl;
                return;
            }

            Producto prod;
            while (archivo.read((char*)&prod, sizeof(Producto))) {
                if (prod.tipo == 'N') {
                    Nacional* nacional = new Nacional(prod.codigo, prod.nombre, prod.marca, prod.precio);
                    nacional->actualizar_precio();
                    agregar_producto(nacional);
                } else if (prod.tipo == 'I') {
                    Importado* importado = new Importado(prod.codigo, prod.nombre, prod.marca, prod.precio);
                    importado->actualizar_precio();
                    agregar_producto(importado);
                } else if (prod.tipo == 'J') {
                    Jardin* jardin = new Jardin(prod.codigo, prod.nombre, prod.marca, prod.precio);
                    jardin->actualizar_precio();
                    agregar_producto(jardin);
                }
            }
            archivo.close();

            ofstream nuevo_archivo("productos_actualizados.dat", ios::out | ios::binary);
            if (!nuevo_archivo) {
                cout << "No se pudo abrir el archivo para escribir." << endl;
                return;
            }

            Producto p_actualizado;
            for (const auto& producto : productos) {
                p_actualizado.codigo = producto->get_codigo();
                strcpy(p_actualizado.nombre, producto->get_nombre());
                strcpy(p_actualizado.marca, producto->get_marca());
                p_actualizado.precio = producto->get_precio();
                p_actualizado.tipo = producto->get_tipo();

                nuevo_archivo.write((char*)&p_actualizado, sizeof(Producto));
            }

            nuevo_archivo.close();
        }

        void generar_archivo_ordenado() {
            ifstream archivo("productos.dat", ios::in | ios::binary);
            if (!archivo) {
                cout << "No se pudo abrir el archivo para leer." << endl;
                return;
            }

            vector<Producto> productos_vector;
            Producto prod;
            while (archivo.read((char*)&prod, sizeof(Producto))) {
                productos_vector.push_back(prod);
            }
            archivo.close();

            sort(productos_vector.begin(), productos_vector.end(), 
                [](const Producto& a, const Producto& b) {
                return a.nombre[0] < b.nombre[0]; // ordenar por orden alfabético del nombre del producto
            });

            ofstream archivo_ordenado("productos_ordenados.txt", ios::out);
            if (!archivo_ordenado) {
                cout << "No se pudo abrir el archivo para escribir." << endl;
                return;
            }

            for (const auto& p : productos_vector) {
                archivo_ordenado << "Nombre: " << p.nombre << ", Marca: " << p.marca << " ....$ " << p.precio << endl;
            }
            archivo_ordenado.close();
        }

        void mostrar_cantidad_xmarca() {
            map<string, int> cantidad_por_marca;

            for (const auto& producto : productos) {
                cantidad_por_marca[producto->get_marca()]++;
            }

            cout << "Cantidad de productos por marca:" << endl;
            for (const auto& par : cantidad_por_marca) {
                cout << "Marca: " << par.first << ", Cantidad: " << par.second << endl;
            }
        }

        void producto_caro() {
            if(productos.empty()) {
                cout << "No hay productos disponibles." << endl;
                return;
            }

            vector<Electrodomestico*> productos_caro = productos;
            sort(productos_caro.begin(), productos_caro.end(), 
                [](Electrodomestico* a, Electrodomestico* b) {
                    return a->get_precio() > b->get_precio();
                });

            cout << "Producto más caro:" << productos_caro.front()->get_nombre() << " - $" << productos_caro.front()->get_precio() << endl;
        }

        void producto_barato() {
            if(productos.empty()) {
                cout << "No hay productos disponibles." << endl;
                return;
            }

            vector<Electrodomestico*> productos_barato = productos;
            sort(productos_barato.begin(), productos_barato.end(), 
                [](Electrodomestico* a, Electrodomestico* b) {
                    return a->get_precio() < b->get_precio();
                });

            cout << "Producto más barato:" << productos_barato.front()->get_nombre() << " - $" << productos_barato.front()->get_precio() << endl;
        }
};