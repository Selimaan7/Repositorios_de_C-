#include <iostream>
#include <string>
using namespace std;

int main() {
    
  cout << "hola novia como estas sabes que te amo mucho pero........" << endl;
    int aux = 0;

    string amar, fin;   
      while (aux == 0) {
      cout << "vos me amas?" << endl;
      cin >> amar;
        if (amar == "si") {
          cout << "te amo mucho mi amor" << endl;
          aux = 1;
        }
        else if (amar == "no") {
          cout << "no me amas?" << endl;
        }
        else {
            cout << "no entiendo tu respuesta" << endl;
        }
    cin >> fin;
    } return 0;   
} 
