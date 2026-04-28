// MULTILISTA - Estructura de datos 2D con enlaces

#include <iostream>
using namespace std;

// ============================================================================
// ESTRUCTURA DEL NODO
// ============================================================================

struct multilista 
{
    int dato;                  // Valor almacenado en el nodo
    int fila;                  // Número de fila
    int columna;               // Número de columna
    
    multilista *siguiente;     // Siguiente nodo en la lista
    multilista *anterior;      // Anterior nodo en la lista
    
    multilista *sig_col;       // Siguiente en la columna
    multilista *ant_col;       // Anterior en la columna
};

// Puntero global a la lista principal
multilista *lista_global = NULL;

// ============================================================================
// DECLARACIÓN DE TODAS LAS FUNCIONES
// ============================================================================

multilista* buscar_nodo(int fila, int columna);
void agregar_en_posicion(int fila, int columna, int valor);
void agregar_al_inicio(int valor);
void agregar_al_final(int valor);
void agregar_ordenado(int valor);
void sacar_posicion(int fila, int columna);
void mostrar_adelante();
void mostrar_atras();
void mostrar_matriz();

// ============================================================================
// IMPLEMENTACIÓN DE FUNCIONES
// ============================================================================

// ============================================================================
// FUNCIÓN 1: BUSCAR NODO
// ============================================================================

multilista* buscar_nodo(int fila, int columna)
{
    // Recorremos lista_global hasta encontrar el nodo con las coordenadas solicitadas
    multilista *nodo = lista_global;
    
    while (nodo != NULL)
    {
        // Si encontramos el nodo retornamos su dirección
        if (nodo->fila == fila && nodo->columna == columna)
            return nodo;
        
        // Continuamos buscando en el siguiente nodo
        nodo = nodo->siguiente;
    }
    
    // Si no encontramos nada retornamos NULL
    return NULL;
}

// ============================================================================
// FUNCIÓN 2: AGREGAR EN POSICIÓN ESPECÍFICA
// ============================================================================

void agregar_en_posicion(int fila, int columna, int valor)
{
    // Verificamos que no exista un nodo en esa posición
    if (buscar_nodo(fila, columna) != NULL)
    {
        cout << "Ya existe un nodo en (" << fila << ", " << columna << ")" << endl;
        return;
    }
    
    // Creamos el nuevo nodo dinámico
    multilista *nuevo = new multilista();
    nuevo->dato = valor;
    nuevo->fila = fila;
    nuevo->columna = columna;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    nuevo->sig_col = NULL;
    nuevo->ant_col = NULL;
    
    // Si la lista está vacía, este es el primer nodo
    if (lista_global == NULL)
    {
        lista_global = nuevo;
        cout << "Nodo agregado en (" << fila << ", " << columna << ")" << endl;
        return;
    }
    
    // Buscamos la posición correcta para mantener orden por fila y columna
    multilista *aux = lista_global;
    multilista *anterior = NULL;
    
    // Buscamos hasta encontrar una posición con mayor fila o columna
    while (aux != NULL && (aux->fila < fila || (aux->fila == fila && aux->columna < columna)))
    {
        anterior = aux;
        aux = aux->siguiente;
    }
    
    // Conectamos el nuevo nodo en la posición encontrada
    nuevo->siguiente = aux;
    nuevo->anterior = anterior;
    
    if (anterior != NULL)
        anterior->siguiente = nuevo;
    else
        lista_global = nuevo;  // Es el primer nodo
    
    if (aux != NULL)
        aux->anterior = nuevo;
    
    cout << "Nodo agregado en (" << fila << ", " << columna << ")" << endl;
}

// ============================================================================
// FUNCIÓN 3: AGREGAR AL INICIO
// ============================================================================

void agregar_al_inicio(int valor)
{
    // Simplemente llamamos a agregar_en_posicion con (0, 0)
    agregar_en_posicion(0, 0, valor);
}

// ============================================================================
// FUNCIÓN 4: AGREGAR AL FINAL
// ============================================================================

void agregar_al_final(int valor)
{
    // Encontramos el último nodo de la lista
    multilista *aux = lista_global;
    
    // Si la lista está vacía, agregamos al inicio
    if (aux == NULL)
    {
        agregar_en_posicion(0, 0, valor);
        return;
    }
    
    // Buscamos el último nodo
    while (aux->siguiente != NULL)
    {
        aux = aux->siguiente;
    }
    
    // Insertamos en la siguiente columna del último nodo
    int nueva_fila = aux->fila;
    int nueva_columna = aux->columna + 1;
    agregar_en_posicion(nueva_fila, nueva_columna, valor);
}

// ============================================================================
// FUNCIÓN 5: AGREGAR ORDENADO
// ============================================================================

void agregar_ordenado(int valor)
{
    // Buscamos la siguiente posición disponible (vacía)
    int fila = 0, columna = 0;
    bool encontrado = false;
    
    // Recorremos buscando una posición vacía
    for (int f = 0; f < 1000 && !encontrado; f++)
    {
        for (int c = 0; c < 1000 && !encontrado; c++)
        {
            // Si la posición está vacía (buscar_nodo devuelve NULL)
            if (buscar_nodo(f, c) == NULL)
            {
                fila = f;
                columna = c;
                encontrado = true;
            }
        }
    }
    
    // Si encontramos una posición disponible, agregamos
    if (encontrado)
        agregar_en_posicion(fila, columna, valor);
}

// ============================================================================
// FUNCIÓN 6: SACAR NODO DE POSICIÓN ESPECÍFICA
// ============================================================================

void sacar_posicion(int fila, int columna)
{
    // Buscamos el nodo a eliminar
    multilista *nodo = buscar_nodo(fila, columna);
    
    // Si no existe, avisamos
    if (nodo == NULL)
    {
        cout << "No existe nodo en (" << fila << ", " << columna << ")" << endl;
        return;
    }
    
    // Desconectamos el nodo de los enlaces horizontales
    if (nodo->anterior != NULL)
        nodo->anterior->siguiente = nodo->siguiente;
    else
        lista_global = nodo->siguiente;  // Era el primer nodo
    
    if (nodo->siguiente != NULL)
        nodo->siguiente->anterior = nodo->anterior;
    
    // Liberamos la memoria del nodo eliminado
    delete nodo;
    cout << "Nodo eliminado de (" << fila << ", " << columna << ")" << endl;
}

// ============================================================================
// FUNCIÓN 7: MOSTRAR HACIA ADELANTE
// ============================================================================

void mostrar_adelante()
{
    cout << "\n=== MOSTRAR HACIA ADELANTE ===" << endl;
    
    // Si la lista está vacía, lo indicamos
    if (lista_global == NULL)
    {
        cout << "La lista está vacía" << endl;
        return;
    }
    
    // Recorremos desde el primer nodo hasta el último
    multilista *nodo = lista_global;
    while (nodo != NULL)
    {
        cout << "(" << nodo->fila << ", " << nodo->columna << ") = [" << nodo->dato << "]  ";
        nodo = nodo->siguiente;
    }
    cout << endl;
}

// ============================================================================
// FUNCIÓN 8: MOSTRAR HACIA ATRÁS
// ============================================================================

void mostrar_atras()
{
    cout << "\n=== MOSTRAR HACIA ATRÁS ===" << endl;
    
    // Si la lista está vacía, lo indicamos
    if (lista_global == NULL)
    {
        cout << "La lista está vacía" << endl;
        return;
    }
    
    // Encontramos el último nodo
    multilista *nodo = lista_global;
    while (nodo->siguiente != NULL)
    {
        nodo = nodo->siguiente;
    }
    
    // Recorremos hacia atrás usando los enlaces anteriores
    while (nodo != NULL)
    {
        cout << "(" << nodo->fila << ", " << nodo->columna << ") = [" << nodo->dato << "]  ";
        nodo = nodo->anterior;
    }
    cout << endl;
}

// ============================================================================
// FUNCIÓN 9: MOSTRAR COMO MATRIZ
// ============================================================================

void mostrar_matriz()
{
    cout << "\n=== VISUALIZACIÓN COMO MATRIZ ===" << endl;
    
    // Si la lista está vacía, lo indicamos
    if (lista_global == NULL)
    {
        cout << "La matriz está vacía" << endl;
        return;
    }
    
    // Encontramos las dimensiones máximas de la matriz
    int max_fila = -1, max_columna = -1;
    multilista *nodo = lista_global;
    
    while (nodo != NULL)
    {
        if (nodo->fila > max_fila)
            max_fila = nodo->fila;
        if (nodo->columna > max_columna)
            max_columna = nodo->columna;
        nodo = nodo->siguiente;
    }
    
    // Imprimimos los encabezados de columnas
    cout << "   ";
    for (int c = 0; c <= max_columna; c++)
        cout << " Col" << c;
    cout << endl;
    
    // Imprimimos filas con sus elementos
    for (int f = 0; f <= max_fila; f++)
    {
        cout << "Fila" << f << ": ";
        for (int c = 0; c <= max_columna; c++)
        {
            // Buscamos el elemento en la posición (f, c)
            multilista *elemento = buscar_nodo(f, c);
            if (elemento != NULL)
                cout << " [" << elemento->dato << "]";
            else
                cout << " [ ]";  // Celda vacía
        }
        cout << endl;
    }
}

// ============================================================================
// FUNCIÓN PRINCIPAL - EJEMPLOS DE USO
// ============================================================================

int main()
{
    cout << "================== MULTILISTA FUNCIONANDO ==================" << endl;
    
    // --- PRUEBA 1: Agregar en posiciones específicas
    cout << "\n--- Agregando datos en posiciones específicas ---" << endl;
    agregar_en_posicion(0, 0, 10);
    agregar_en_posicion(0, 2, 20);
    agregar_en_posicion(1, 1, 30);
    agregar_en_posicion(2, 0, 40);
    agregar_en_posicion(1, 3, 50);
    
    // Mostrar adelante
    mostrar_adelante();
    
    // Mostrar matriz
    mostrar_matriz();
    
    // Mostrar atrás
    mostrar_atras();
    
    // --- PRUEBA 2: Agregar al inicio
    cout << "\n--- Agregando al inicio ---" << endl;
    agregar_al_inicio(100);
    
    mostrar_matriz();
    
    // --- PRUEBA 3: Agregar ordenado
    cout << "\n--- Agregando de forma ordenada ---" << endl;
    agregar_ordenado(15);
    agregar_ordenado(25);
    
    mostrar_adelante();
    
    // --- PRUEBA 4: Sacar nodo
    cout << "\n--- Eliminando nodo de la posicion (0, 2) ---" << endl;
    sacar_posicion(0, 2);
    
    mostrar_matriz();
    
    cout << "\n================= FIN DEL PROGRAMA =================" << endl;
    
    return 0;
}
