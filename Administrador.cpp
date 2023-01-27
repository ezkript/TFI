/*
TO-DO:
 *Probar funcionalidad: calcular paga a entrenadores. Archivo "Turnos.dat" de Recepcion requerido.
*/

#include <locale.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <conio.h>
#include <iostream>
using namespace std;

#include "Structures.h"
#include "Functions.h"
#include "validations.h"

int main() {
    FILE* escribir=nullptr,
        * leer=nullptr;
    usuarios usuario{};
    entrenadores entrenador{};
    Actividades actividad{};
    int respuesta=0,
        mayor=0;
    // //Establece el idioma a espa�ol 
    // setlocale(LC_ALL, "spanish");
    // //Establecer el idioma de la consola al espa�ol
    // SetConsoleCP(1252);
    // SetConsoleOutputCP(1252);
    leer = fopen("Usuarios.dat", "rb");
    if (leer == NULL) {
        cout << "Bienvenido a la aplicacion para gestionar su gimnasio. \nComo es su primer ingreso, es necesario crear una cuenta de administrador: " << endl << endl;
        usuario = registrarAdmin(escribir, usuario);
        Limpiar();
        fclose(leer);
    } else {
        fclose(leer);
    }

    do
    {
        cout << "Bienvenid@ " << (strlen(usuario.apYNom) < 1 ? "administrador" : usuario.apYNom) << "." << endl
            << "-----------------------------------------------" << endl
            << "1. Iniciar sesion." << endl
            << "2. Registrar usuario de Recepcion." << endl
            << "3. Registrar actividades del gym." << endl
            << "4. Calcular el pago al entrenador." << endl
            << "5. Entrenador con mayor carga horaria." << endl
            << "6. Listar usuarios y actividades." << endl
            << "7. Salir. " << endl
            << "-----------------------------------------------" << endl
            << "Ingresar una opcion: "; cin >> respuesta;
        system("CLS");

        switch (respuesta) {
        case 1:
            login(escribir, entrenador, usuario, 1);
            break;
        case 2:
            if (usuario.tipo == 2) {
                registrar(escribir, leer, entrenador, usuario);
            }
            else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
            break;
        case 3:
            if (usuario.tipo == 2) {
                registrarActividad(escribir, actividad);
            }
            else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
            break;
        case 4:
            if (usuario.tipo == 2) {
                calcularPago(entrenador);
            }
            else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
            break;
        case 5:
            if(usuario.tipo==2){
                mayorCarga(entrenador,mayor);
                if(entrenador.legajo != -1){
                    cout << endl << "El entrenador con mayor carga horaria es " << entrenador.apYNom << " con " << mayor << " horas semanales registradas." << endl;
                }
                Limpiar();
            } else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
            break;
        case 6:
            if (usuario.tipo == 2) {
                listar(escribir, entrenador, usuario, actividad);
            }
            else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
            break;
        case 7:
            break;
        default:
            break;
        }
    } while (respuesta != 7);

    return 0;
}
