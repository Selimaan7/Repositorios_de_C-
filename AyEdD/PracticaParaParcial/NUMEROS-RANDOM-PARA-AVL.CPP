#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX 20


int main (){
    srand(time(nullptr));

    for (int i = 0; i <= MAX; i++){
        int numero = rand() % (100);
        cout << numero << "   ";
    }
    cout << endl; 
    cout << endl;
    for (int i = 0; i <= MAX; i++){
        int numero = rand() % (100);
        cout << numero << "   ";
    }
    cout << endl; 
    cout << endl;   
    for (int i = 0; i <= MAX; i++){
        int numero = rand() % (100);
        cout << numero << "   ";
    }
    cout << endl; 
    cout << endl;
    for (int i = 0; i <= MAX; i++){
        int numero = rand() % (100);
        cout << numero << "   ";
    }
    cout << endl; 
    cout << endl;
    for (int i = 0; i <= MAX; i++){
        int numero = rand() % (100);
        cout << numero << "   ";
    }
    cout << endl; 
    cout << endl;
    for (int i = 0; i <= MAX; i++){
        int numero = rand() % (100);
        cout << numero << "   ";
    }
    cout << endl; 
    cout << endl;
    
}