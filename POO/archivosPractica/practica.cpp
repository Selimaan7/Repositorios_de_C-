#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class SeparadoraTxt{
    private:
        int cant_lineas;
        vector<string> lineas;

    public:
        SeparadoraTxt() : cant_lineas(0){}

        void CargarArchivo(string nomarch){
            ifstream arch (nomarch.c_str(), ios::in);
            if (arch.fail()){
                cout << "El archivo fallo al abrirse" << endl;
            } else{
                string linea;

                while (getline(arch, linea)){
                    lineas.push_back(linea);
                   
                }
                arch.close();
                cant_lineas = lineas.size();
            }
        }

        void separarArchivos(int num){
            if (num <= 0) {
                cout << "Sos re wachin para poner eso" << endl;
                return;
            }
            int cant_por_linea;
            int linea_actual = 0;


            cant_por_linea = cant_lineas / num;

            string arch;
            for (int i = 0; i< num; i++){
                cout << "Escriba el nombre del archivo "<< i << endl;
                cin >> arch;
                ofstream archivo (arch.c_str(), ios::out);
                if (archivo.fail()){
                    cout << "El archivo no se pudo crear correctamente" << endl;
                    return;
                }
                for (int j = 0; j < cant_por_linea; j++){
                    
                    archivo << lineas[linea_actual] << '\n';
                    linea_actual ++;

                }
                archivo.close();
            }

            if (cant_lineas % num != 0){
                ofstream archivo (arch.c_str(), ios::out | ios::app);
                if (archivo.fail()){
                    cout << "El archivo no se pudo crear correctamente" << endl;
                    return;
                }
                while (linea_actual < cant_lineas){
                    archivo << lineas[linea_actual] << '\n';
                    linea_actual ++;
                }
            }
        }

        

};