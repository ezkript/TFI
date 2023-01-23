#include <stdlib.h>
#include <iostream>
using namespace std;

int main(void){
    int respuesta;

    cout << "Sistema de Gestion del Gimnasio" << endl
    << "1. Iniciar Sesion." << endl
    << "2. Salir de la aplicación." << endl 
    << "Respuesta: ";
    cin >> respuesta;

    do{
        switch (respuesta){
        case 1:
            login();
            break;
        case 2:
            lista();
            break;
        case 3:
            registrar();
            break;
        case 4:
            break;
        default:
            cout << "elegi bien chango";
            break;
        }
    } while (respuesta!=4);
    
    return 0;
}
