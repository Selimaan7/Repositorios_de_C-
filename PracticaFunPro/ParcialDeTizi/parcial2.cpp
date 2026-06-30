// ... (lectura de archivos igual)

estudiante_fcyt estudiante;
int cantidad_estudiantes = 0;

while (true) {
	// ... (igual, pide DNI, nombre, fecha, código)
	// Guardar en estudiante y clasificar cuatrimestre (llamar a cantidad_por_semestre)
}

// ---- PUNTO a: tabla ----
cout << left << setw(10) << "Codigo"
	   << setw(25) << "Descripcion"
	   << setw(15) << "1er Cuat."
	   << setw(15) << "2do Cuat."
	   << setw(12) << "Reduccion" << endl;
for (int i = 0; i < catidad_colectivos; i++) {
	int pri = colectivo.cantidad_pri[i];
	int seg = colectivo.cantidad_segu[i];
	int reduccion = 0;
	if (pri > 0) reduccion = ((pri - seg) * 100) / pri;
	cout << left << setw(10) << colectivo.codigo_de_linea[i]
		<< setw(25) << colectivo.descripcion[i]
		<< setw(15) << pri
		<< setw(15) << seg
		<< setw(11) << reduccion << "%" << endl;
}

// ---- PUNTO b: porcentaje de abandonos ----
string dnis[9999];
bool primer[9999] = {false}, segundo[9999] = {false};
int cantDnis = 0;

for (int i = 0; i < cantidad_estudiantes; i++) {
	string dni = estudiante.DNI[i];
	int pos = -1;
	for (int j = 0; j < cantDnis; j++) {
		if (dnis[j] == dni) { pos = j; break; }
	}
	if (pos == -1) {
		pos = cantDnis;
		dnis[cantDnis] = dni;
		cantDnis++;
	}
	if (estudiante.primer_cuatri[i]) primer[pos] = true;
	if (estudiante.segundo_cuatri[i]) segundo[pos] = true;
}

int totalPrimer = 0, abandonos = 0;
for (int i = 0; i < cantDnis; i++) {
	if (primer[i]) {
		totalPrimer++;
		if (!segundo[i]) abandonos++;
	}
}
int porcentajeAbandono = (totalPrimer > 0) ? (abandonos * 100) / totalPrimer : 0;
cout << "\n=== PUNTO b ===\n";
cout << "Estudiantes que viajaron en 1er cuatrimestre: " << totalPrimer << endl;
cout << "Estudiantes que NO viajaron en 2do cuatrimestre: " << abandonos << endl;
cout << "Porcentaje de abandono: " << porcentajeAbandono << "%" << endl;

// ---- PUNTO c: top 5 ----
string dnisTop[9999];
int viajesTop[9999];
int cantTop = 0;

for (int i = 0; i < cantidad_estudiantes; i++) {
	string dni = estudiante.DNI[i];
	bool encontrado = false;
	for (int j = 0; j < cantTop; j++) {
		if (dnisTop[j] == dni) {
			viajesTop[j]++;
			encontrado = true;
			break;
		}
	}
	if (!encontrado) {
		dnisTop[cantTop] = dni;
		viajesTop[cantTop] = 1;
		cantTop++;
	}
}

// Ordenar descendente por viajes
for (int i = 0; i < cantTop - 1; i++) {
	for (int j = i + 1; j < cantTop; j++) {
		if (viajesTop[i] < viajesTop[j]) {
			swap(dnisTop[i], dnisTop[j]);
			swap(viajesTop[i], viajesTop[j]);
		}
	}
}

int top5 = (cantTop < 5) ? cantTop : 5;
cout << "\n=== PUNTO c) Top " << top5 << " estudiantes ===\n";
cout << left << setw(15) << "DNI"
	<< setw(30) << "Apellido y Nombres"
	<< "Cantidad de viajes" << endl;
for (int i = 0; i < top5; i++) {
	string nombre = "";
	for (int j = 0; j < cantidad_estudiantes; j++) {
		if (estudiante.DNI[j] == dnisTop[i]) {
			nombre = estudiante.nombre_apellido[j];
			break;
		}
	}
	cout << left << setw(15) << dnisTop[i]
		<< setw(30) << nombre
		<< viajesTop[i] << endl;
}

return 0;