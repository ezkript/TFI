#include <stdlib.h>
#include <iostream>
using namespace std;

int main(void){
    int respuesta,
        firstTime;
    FILE *fp;

    cout << "Sistema de Gestion del Gimnasio" << endl
    << "1. Iniciar Sesion." << endl
    << "2. Salir de la aplicación." << endl 
    << "Respuesta: ";
    cin >> respuesta;
    fp=fopen("Usuarios.dat","rb");
    if(fp==NULL){
        firstTime=1;
    } else {
        firstTime=2;
    }
    do{
        switch (respuesta){
        case 1:
            if(firstTime==1){
                login();
            }
            break;
        case 2:
            break;
        default:
            cout << "La opción no existe.";
            break;
        }
    } while (respuesta!=2);
    
    return 0;
}
