#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>   
using namespace std;

struct Cliente_informacion {
	string DNI[9999];
	string nya[9999];
	int fecha_alta[9999];
};

struct movimientois_informacion{
	string DNI[9999];
	int tipo_de_paquete[9999];
	int fecha_de_movimiento[9999];
	string situacion[9999];
};

bool bene(Cliente_informacion cliente,int i);

int antiguedadMeses(int fechaAlta) {
	string f = to_string(fechaAlta);
	int anio = stoi(f.substr(0, 4));
	int mes  = stoi(f.substr(4, 2));
	// Meses desde el mes de alta hasta diciembre de 2025
	return (2025 - anio) * 12 + (12 - mes);
}

void ordenar_datos(string nombre[],string dni[],string situacion [],int fecha_mov[],int tipo_pac,int contador);

void matriz_resumen(int tipo[],int fecha_mov[],int auxiliar[][6],int i);



int main() {
	ifstream cliente_archivo;
	cliente_archivo.open("CLIENTES.txt", ios::in);
	
	if (cliente_archivo.fail()) {
		cout << "Error al abrir el archivo" << endl;
		return 0;
	}
	
	Cliente_informacion cliente;
	int cantidad_clientes = 0,cantidad_movimientos=0;
	string dni_archivo, nya_archivo, fecha_str;
	
	while (!cliente_archivo.eof()) {
		getline(cliente_archivo, dni_archivo);
		if (cliente_archivo.eof()) break;
		
		getline(cliente_archivo, nya_archivo);
		if (cliente_archivo.eof()) break;
		
		getline(cliente_archivo, fecha_str);
		if (cliente_archivo.eof()) break;
		
		cliente.DNI[cantidad_clientes] = dni_archivo;
		cliente.nya[cantidad_clientes] = nya_archivo;
		cliente.fecha_alta[cantidad_clientes] = stoi(fecha_str);
			
		cantidad_clientes++;
	}
	
	cliente_archivo.close();
	
	ifstream movimiento_archivo;
	
	movimiento_archivo.open("MOVIMIENTOS.txt",ios::in);
	
	if(movimiento_archivo.fail())
	{
		cout<<"error"<<endl;
		return 0;
	}
	string dni_movimiento,tipo_de_paq,fecha_movimiento;
	string situacion_archi;
	movimientois_informacion movimiento;
	while (!movimiento_archivo.eof())
	{
		getline(movimiento_archivo, dni_movimiento);
		if (movimiento_archivo.eof()) break;
		
		getline(movimiento_archivo, tipo_de_paq);
		if (movimiento_archivo.eof()) break;
		
		getline(movimiento_archivo, fecha_movimiento);
		if (movimiento_archivo.eof()) break;
		
		getline(movimiento_archivo, situacion_archi);
		if (movimiento_archivo.eof()) break;
		
		movimiento.DNI[cantidad_movimientos]=dni_movimiento;
		movimiento.tipo_de_paquete[cantidad_movimientos]=stoi(tipo_de_paq);
		movimiento.fecha_de_movimiento[cantidad_movimientos]=stoi(fecha_movimiento);
		movimiento.situacion[cantidad_movimientos]=situacion_archi;
		
		cantidad_movimientos++;
	}
	
	
	
	
	
	
	string nombre[999],dni[999];
	string situacion[999];
	int fehca_alta[999],fecha_mov[999],tipopac[999];
	bool beneficios[999]=false;
	int vector_auxiliar[6][6]={0};
	
	
	
	for (int i=0;i<cantidad_clientes;i++)
	{int contador=0;
	int fecha_max=0,fecha_actual;
	dni[i]=cliente.DNI[i];
	nombre[i]=cliente.nya[i];
	fehca_alta[i]=cliente.fecha_alta[i];
	
	while (contador!=cantidad_movimientos)
	{
		if (cliente.DNI[i]==movimiento.DNI[contador])
		{
			
			fecha_actual=movimiento.fecha_de_movimiento[contador];
			if (fecha_actual>fecha_max)
			{
				fecha_max=fecha_actual;
				situacion[i]=movimiento.situacion[contador];
				if (situacion[i]=="Alta")
				{
					beneficios[i]=bene(cliente,i);
				}
				tipopac[i]=movimiento.tipo_de_paquete[contador];
				fecha_mov[i]=fecha_actual;
			}
		}
		contador++;
	}
	fecha_mov[i]=fecha_max;
	if (beneficios[i]==true)
	{
		matriz_resumen(tipopac,fecha_mov,vector_auxiliar,i);
	}
	
	}
	
	
	ordenar_datos(nombre,dni,situacion,fecha_mov,tipopac,cantidad_clientes);
		
		
		for (int i=0;i<cantidad_clientes;i++)
	{
			cout<<"Cliente: "<<dni[i]<<" ,Nombre y apellido: "<<nombre[i]<<" y antiguedad: "<<fecha_mov[i]<<endl;
		}
			
		
		
		cout<<left<<setw(10)<<"Tipo de paquete "<<setw(10)<<"6-12"<<setw(10)<<"13-18"<<setw(10)<<"19-24"<<setw(10)<<"25-30"<<setw(10)<<"31-36"<<endl;
		cout<<left<<setw(10)<<"Nacional"<<setw(10)<<" "<<vector_auxiliar[0][0]<<setw(10)<<" "<<vector_auxiliar[0][1]<<setw(10)<<" "<<vector_auxiliar[0][2]<<setw(10)<<" "<<vector_auxiliar[0][3]<<setw(10)<<" "<<vector_auxiliar[0][4]<<endl;
		cout<<left<<setw(10)<<"Internacional"<<setw(10)<<" "<<vector_auxiliar[1][0]<<setw(10)<<" "<<vector_auxiliar[1][1]<<setw(10)<<" "<<vector_auxiliar[1][2]<<setw(10)<<" "<<vector_auxiliar[1][3]<<setw(10)<<" "<<vector_auxiliar[1][4]<<endl;
		cout<<left<<setw(10)<<"Crucero"<<setw(10)<<" "<<vector_auxiliar[2][0]<<setw(10)<<" "<<vector_auxiliar[2][1]<<setw(10)<<" "<<vector_auxiliar[2][2]<<setw(10)<<" "<<vector_auxiliar[2][3]<<setw(10)<<" "<<vector_auxiliar[2][4]<<endl;
		cout<<left<<setw(10)<<"Aventura"<<setw(10)<<" "<<vector_auxiliar[3][0]<<setw(10)<<" "<<vector_auxiliar[3][1]<<setw(10)<<" "<<vector_auxiliar[3][2]<<setw(10)<<" "<<vector_auxiliar[3][3]<<setw(10)<<" "<<vector_auxiliar[3][4]<<endl;
		cout<<left<<setw(10)<<"Todo incluido"<<setw(10)<<" "<<vector_auxiliar[4][0]<<setw(10)<<" "<<vector_auxiliar[4][1]<<setw(10)<<" "<<vector_auxiliar[4][2]<<setw(10)<<" "<<vector_auxiliar[4][3]<<setw(10)<<" "<<vector_auxiliar[4][4]<<endl;
		
		
		
	return 0;
}















bool bene(Cliente_informacion cliente,int i)
{
	return antiguedadMeses(cliente.fecha_alta[i]) >= 6;
	}


void ordenar_datos(string nombre[],string dni[],string situacion [],int fecha_alt[],int tipo_pac,int cant_clientes)
{
	string auxiliar_nombre,axuliar_dni,auxiliar_situacion;
	int auxiliar_fecha=0,auxiliar_paquete=0;
	
	
	for (int i=0;i<cant_clientes-1;i++)
	{
		for(int j=i+1;j<cant_clientes;j++)
		{
			if (fecha_alt[i]>fecha_alt[j])
			{
				auxiliar_fecha=fecha_alt[i];
				fecha_alt[i]=fecha_alt[j];
				fecha_alt[j]=auxiliar_fecha;
				
				auxiliar_nombre=nombre[i];
				nombre[i]=nombre[j];
				nombre[j]=auxiliar_nombre;
				
				axuliar_dni=dni[i];
				dni[i]=dni[j];
				dni[j]=axuliar_dni;
				
				auxiliar_situacion=situacion[i];
				situacion[i]=situacion[j];
				situacion[j]=auxiliar_situacion;
				
				auxiliar_paquete=tipo_pac[i];
				tipo_pac[i]=tipo_pac[j];
				tipo_pac[j]=auxiliar_paquete;
			}
		}
	}
}


void matriz_resumen(int tipo[],int fecha_mov[],int auxiliar[][6],int i)
{
	if(tipo[i]==1)
	{
		if (fecha_mov[i]>=6 && fecha_mov[i]<=12)
		{
			auxiliar[0][0]++;
		}
		if (fecha_mov[i]>=13 && fecha_mov[i]<=18)
		{
			auxiliar[0][1]++;
		}
		if (fecha_mov[i]>=19 && fecha_mov[i]<=24)
		{
			auxiliar[0][2]++;
		}
		if (fecha_mov[i]>=25 && fecha_mov[i]<=30)
		{
			auxiliar[0][3]++;
		}
		if (fecha_mov[i]>=31 && fecha_mov[i]<=36)
		{
			auxiliar[0][4]++;
		}
	}
	if(tipo[i]==2)
	{
		if (fecha_mov[i]>=6 && fecha_mov[i]<=12)
		{
			auxiliar[1][0]++;
		}
		if (fecha_mov[i]>=13 && fecha_mov[i]<=18)
		{
			auxiliar[1][1]++;
		}
		if (fecha_mov[i]>=19 && fecha_mov[i]<=24)
		{
			auxiliar[1][2]++;
		}
		if (fecha_mov[i]>=25 && fecha_mov[i]<=30)
		{
			auxiliar[1][3]++;
		}
		if (fecha_mov[i]>=31 && fecha_mov[i]<=36)
		{
			auxiliar[1][4]++;
		}
	}
	
	if(tipo[i]==3)
	{
		if (fecha_mov[i]>=6 && fecha_mov[i]<=12)
		{
			auxiliar[2][0]++;
		}
		if (fecha_mov[i]>=13 && fecha_mov[i]<=18)
		{
			auxiliar[2][1]++;
		}
		if (fecha_mov[i]>=19 && fecha_mov[i]<=24)
		{
			auxiliar[2][2]++;
		}
		if (fecha_mov[i]>=25 && fecha_mov[i]<=30)
		{
			auxiliar[2][3]++;
		}
		if (fecha_mov[i]>=31 && fecha_mov[i]<=36)
		{
			auxiliar[2][4]++;
		}
	}
	
	if(tipo[i]==4)
	{
		if (fecha_mov[i]>=6 && fecha_mov[i]<=12)
		{
			auxiliar[3][0]++;
		}
		if (fecha_mov[i]>=13 && fecha_mov[i]<=18)
		{
			auxiliar[3][1]++;
		}
		if (fecha_mov[i]>=19 && fecha_mov[i]<=24)
		{
			auxiliar[3][2]++;
		}
		if (fecha_mov[i]>=25 && fecha_mov[i]<=30)
		{
			auxiliar[3][3]++;
		}
		if (fecha_mov[i]>=31 && fecha_mov[i]<=36)
		{
			auxiliar[3][4]++;
		}
	}
	
	if(tipo[i]==5)
	{
		if (fecha_mov[i]>=6 && fecha_mov[i]<=12)
		{
			auxiliar[4][0]++;
		}
		if (fecha_mov[i]>=13 && fecha_mov[i]<=18)
		{
			auxiliar[4][1]++;
		}
		if (fecha_mov[i]>=19 && fecha_mov[i]<=24)
		{
			auxiliar[4][2]++;
		}
		if (fecha_mov[i]>=25 && fecha_mov[i]<=30)
		{
			auxiliar[4][3]++;
		}
		if (fecha_mov[i]>=31 && fecha_mov[i]<=36)
		{
			auxiliar[4][4]++;
		}
	}
}