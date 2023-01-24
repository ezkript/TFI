#include <locale.h>
#include <windows.h>
#include <iostream>
#include "functions.h"
using namespace std;

int main(void){
    int respuesta;
    bool sesion;
    // //Establece el idioma a español 
    // setlocale(LC_ALL, "spanish");
    // //Establecer el idioma de la consola al español
    // SetConsoleCP(1252);
    // SetConsoleOutputCP(1252);

    do
    {
        cout << "Bienvenido Administrador/a" << endl
        << "1. Iniciar sesión." << endl
        << "2. Registrar usuario de Recepción." << endl
        << "3. Registrar actividades del gym. - TEMPORAL LISTAR" << endl
        << "4. Entrenador con mayor carga horaria." << endl
        << "5. Atrás." << endl << endl
        << "Ingresar una opción: ";cin >> respuesta;
        system("CLS");
        switch (respuesta){
        case 1:
            sesion = login(3);
            break;
        case 2:
            if(sesion==true){
                registrar();
            } else {
                cout << "No hay ninguna sesión activa." << endl; 
            }
            break;
        case 3:
            listar();
        break;
        default:
            break;
        }
    } while (respuesta!=5);
    
    return 0;
}

