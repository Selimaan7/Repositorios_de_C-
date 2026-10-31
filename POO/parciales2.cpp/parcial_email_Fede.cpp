#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <numeric>

using namespace std;

class Cliente{

    private:
        
        int id;
        char nombre[200];
        vector<string> emails; //almacena los correos de cada cliente 

    public:
        Cliente();
        Cliente(int id,char nombre[200]);

        void agregarEmail(string email);
        void enviarCorreo();
        int getId();
        int cantidadEmail();
        string getNombre() const;
        vector<string> getEmail();
        bool sinEmails();
        
};
bool Cliente::sinEmails(){
    return emails.empty();
}

vector<string> Cliente::getEmail(){
    return emails;
}
string Cliente::getNombre()const{
    return string(nombre);
}
Cliente::Cliente(int id,char nombre[200]){
    this->id=id;
    strcpy(this->nombre,nombre);
}

int Cliente::getId(){
    return id;
}
void Cliente::enviarCorreo() {
    for (int i = 0;i<emails.size(); i++) {
        ofstream arch(emails[i]);

        if (arch.is_open()) {
            arch << "Hola " << nombre<< "! Bienvenido al sistema de notificaciones.";

            arch.close();
        }
    }
}
void Cliente::agregarEmail(string email){
    emails.push_back(email);
}
int Cliente::cantidadEmail(){
    return emails.size();
}


class Empresa{
    private:

        struct cliente{ //al no teenr guardado nada, utilizamos como aux el struct y para luego crear el objeto
            int id;
            char nombre[200];
        };
       
        struct Email{ //guardamos los registros del archivo
            int id_cliente;
            char email[200];
        };
        vector<Cliente>clientes; //almacena los objetos reales

    public:
        
        void leerClientes();
        void leerEmails();
        void enviarEmail();
        
        Cliente* buscarcliente(int id);
        vector<Cliente>clientesconmasemail();
        vector<string>obtenerEmailsRepetidos();
        vector<Cliente>obtenerClientesSinEmail();

        int totalEmailsAEnviar();

    
};
int Empresa::totalEmailsAEnviar(){
    
    vector<int>cantidades;
    //paso 1: obtener la cantidad de emails de cada cliente
    transform(clientes.begin(),clientes.end(),back_inserter(cantidades),[](Cliente c){ return c.cantidadEmail();});
    //Toma cada cliente y lo transforma en un número que representa cuántos emails tiene.

    //paso 2, sumar la cantidad de emails total
    return accumulate(cantidades.begin(),cantidades.end(),0);


}
vector<Cliente>Empresa::obtenerClientesSinEmail(){

    vector<Cliente> clientesSinEmails;
        
    for(int i=0;i<clientes.size();i++){
            if(clientes[i].sinEmails()){
                clientesSinEmails.push_back(clientes[i]);
            }
        }
    return clientesSinEmails;
}
Cliente* Empresa::buscarcliente(int id){
    
    for(int i=0;i<clientes.size();i++){
        if(clientes[i].getId()==id){//comparamos el id de cada cliente
            return &clientes[i];//devuelve la dirección del cliente encontrado.
        }
    }
    return nullptr;
}
//buscar el o los clientes con mas email
vector<Cliente>Empresa::clientesconmasemail(){
    vector<Cliente> vectorclientesconmasemails;

    if(clientes.empty()){
        return vectorclientesconmasemails;
    }
    //buscamos el cliente con mayor cantidad de emails.
    vector<Cliente>::iterator itMax=
    max_element(clientes.begin(),clientes.end(),[](Cliente a,Cliente b){return a.cantidadEmail()<b.cantidadEmail();});

    int maximo=itMax->cantidadEmail();

    //obtenemos todos los clientes que tengan la cant max
    for(int i=0;i<clientes.size();i++){

        cout << clientes[i].getNombre()
     << " - " << clientes[i].cantidadEmail() << endl;

        if(clientes[i].cantidadEmail()==maximo){
            vectorclientesconmasemails.push_back(clientes[i]);

        }
    }
    return vectorclientesconmasemails;
}
//buscamos emails repetidos
vector<string>Empresa::obtenerEmailsRepetidos(){
    map<string,int>cantidad;

    //contamos cuantas veces aparece cada email
    for(int i=0;i<clientes.size();i++){//revisamos cliente por cliente
        vector<string>emails=clientes[i].getEmail();//sacamos los correos de cada cliente
        for(int j=0;j<emails.size();j++){//recorremos los la lista de correos de ese cliente
            cantidad[emails[j]]++;//incrementa la cantidad
        }
    }
    //guardamos solo los repetidos;
    vector<string>repetidos;
    for(auto it=cantidad.begin();it != cantidad.end();++it){
        if(it->second > 1){//si ese email aparece mas de una vez
            repetidos.push_back(it->first); //lo guardamos en el vector de repetidos

        }
    }
}





void Empresa::leerClientes(){
    
    ifstream clie("clientes.bin",ios::binary);
    if(clie.fail()){
        cout<<"El archivo clientes fallo en abrirse"<<endl;
        return;
    }
    else{
    
        cliente aux;

        while(clie.read((char*)&aux,sizeof(aux))){
        
            Cliente C(aux.id,aux.nombre);//creamos el objeto cliente, con los atributos del struct donde lo guardamos
            clientes.push_back(C);//lo agregamos al vector de clientes

            cout << "Cliente cargado: "<< aux.id << " - " << aux.nombre << endl;
        }

    }

    clie.close();
    
    }


void Empresa::leerEmails(){

    ifstream mail;
    mail.open("emails.bin",ios::binary);
    if(mail.fail()){
        cout<<"el archivo emails fallo en abrirse"<<endl;
    }
    else{

        Email aux;
        while(mail.read((char*)&aux,sizeof(aux))){
            Cliente* c=buscarcliente(aux.id_cliente);
            
            if(c != nullptr){
                c->agregarEmail(string(aux.email));
            }
            
            cout << "Email para ID: "
            << aux.id_cliente << " - " << aux.email << endl;
        }
        mail.close();

    }


}
void Empresa::enviarEmail(){
    for(int i=0;i<clientes.size();i++){
        clientes[i].enviarCorreo();
    }
}



int main()
{
    Empresa e;
    
    e.leerClientes();
    e.leerEmails();
    e.enviarEmail();


    cout<<"Proceso finalizado"<<endl;

    vector<Cliente>mayores=e.clientesconmasemail();
    cout<<"Clientes con mas emails: "<<endl;
    for(int i=0;i<mayores.size();i++){
        cout<<mayores[i].getNombre()<<"--->"<<mayores[i].cantidadEmail()<<endl;
    }

    vector<string> emailsrepetidos= e.obtenerEmailsRepetidos();
    for(int i=0;i<emailsrepetidos.size();i++){
        cout<<emailsrepetidos[i] <<endl;
    }
    
    vector<Cliente>sinEmail=e.obtenerClientesSinEmail();
    for(int i=0;i<sinEmail.size();i++){
        cout<<sinEmail[i].getNombre()<<" No tiene email cargado "<<endl;
    }
    
    cout << "Total de emails a enviar: "
     << e.totalEmailsAEnviar() << endl;
    system("pause");
    
    return 0;
}

//TEORIA 
//1. ¿Cuándo utilizaría un archivo de texto y/o un archivo binario? Dé ejemplos.
//Archivo de texto: lo utilizaría cuando necesito almacenar información que pueda 
//leerse y modificarse fácilmente con un editor de texto. Los datos se representan 
//mediante caracteres y se pueden leer y escribir usando << y >>.
//Ejemplo: generar un archivo de texto por cada email de un cliente
//con un mensaje de bienvenida.
//Archivo binario: lo utilizaría cuando necesito almacenar datos en formato binario, 
//por ejemplo, registros con una estructura y un tamaño conocido. Permite leer y escribir los datos directamente en memoria mediante read() y write(), sin convertirlos primero a texto.
//Ejemplo: guardar los clientes de una empresa con su ID y nombre en un archivo clientes.bin.
//En resumen, utilizaría archivos de texto cuando me interese que los datos sean legibles para una persona 
//y archivos binarios cuando quiera almacenar y recuperar registros en formato binario
//2. ¿Qué ventajas da el uso de STL en C++?
//La STL (Standard Template Library) es una biblioteca estándar de C++ que proporciona contenedores, iteradores y algoritmos reutilizables.
//Sus principales ventajas son:
//- Reutilización de código: permite usar algoritmos ya implementados, sin tener que programarlos desde cero.
//- Menos errores: al escribir menos código propio, disminuye la posibilidad de introducir errores.
//- Flexibilidad: los algoritmos pueden trabajar con diferentes tipos de datos y contenedores.
//- Facilidad para administrar datos: ofrece estructuras como vector, list, map y set.
//- Algoritmos eficientes: incluye herramientas como sort, find, max_element, transform y accumulate.