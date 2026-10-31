#include <iostream>

#define N 6

using namespace std;


void Derecho(int a[][N]);
void Maximal_ady (int a[][N], int x);

int main(){
    int matrizady[N][N] = {{0}};

    matrizady [1][2] = 1;
    matrizady [1][3] = 1;
    matrizady [3][3] = 1;
    matrizady [3][2] = 1;
    matrizady [3][0] = 1;
    matrizady [3][4] = 1;
    matrizady [4][5] = 1;

    for (int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
            cout << matrizady [i][j] << "  "; 
        }
        cout << endl;
    }

    int cantrela = 0;

    for (int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
            cantrela += matrizady [i][j]; 
        }
    }

    cout << endl;
    for (int i = 0; i<N; i++){
        Maximal_ady(matrizady, i);
    }
    Derecho(matrizady);
}


void Maximal_ady (int a[][N], int x){
    bool max = true;
    for (int i = 0; i < N; i++){
        if (a[x][i] == 1) max = false;
    }
    if (max) cout << x << " es maximo" << endl << endl;
}

void Derecho(int a[][N]){
    for (int i = 0; i<N; i++){
        cout << "\nEl conjunto Derecho de " << i << " Son: ";
        for (int j = 0; j<N; j++){
            if (a[i][j] == 1){
                cout << j << ", ";
            }
        }
    }
}