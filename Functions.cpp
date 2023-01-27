#include <stdlib.h>
#include <conio.h>
#include <cctype>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "Structures.h"
#include "validations.h"
#include "Functions.h"

/**
 * Nombre: repetition()
 * @param fp Puntero
 * @param user Nombre de usuario
 * @param Usuario
 * Tipo: Booleana.
 * Descripcion: Validar que el nombre de usuario ingresado no sea repetido.
*/
bool repetition(FILE* fp, char user[100], struct usuarios usuario){
    fp = fopen("Usuarios.dat", "rb");

    fread(&usuario, sizeof(usuarios), 1, fp);
    while (!feof(fp)) {
        if (strcmp(user, usuario.usuario) == 0) {
            return false;
        }
        fread(&usuario, sizeof(usuarios), 1, fp);
    }
    fclose(fp);

    return true;
}

void calcularPago(entrenadores entrenador) {
    char trainerName[50];
    FILE* sp;
    int c = 0;

    sp = fopen("Turnos.dat", "rb");
    if (sp != NULL) {
        cout << "Nombre del entrenador: ";
        fflush(stdin);
        cin.getline(trainerName, 50, '\n');

        fread(&entrenador, sizeof(entrenadores), 1, sp);
        while (!feof(sp)) {
            if (strcmp(strlwr(trainerName), strlwr(entrenador.apYNom)) == 0) {
                c++;
            }
            fread(&entrenador, sizeof(entrenadores), 1, sp);
        }
    }
    else {
        cout << "No hay personas realizando actividades." << endl;
    }
    fclose(sp);

    if (c != 0) {
        cout << "La paga correspondiente al entrenador " << trainerName << "es $" << c * 1500 << "." << endl << endl;
    }
    else {
        cout << "El entrenador no tiene ningun grupo de personas asignado." << endl << endl;
    }
    Limpiar();
}

/**
 * Nombre: Listar()
 * @param fp Puntero
 * @param Actividad Estructura de la actividad
 * Tipo: sin tipo.
 * Descripcion: Permite registrar las actividades del gimnasio.
*/
void registrarActividad(FILE* fp, Actividades actividad) {
    FILE *sp=fopen("Entrenadores.dat", "rb");
    fp = fopen("Actividades.dat", "ab");

    //Verifica que hayan entrenadores registrados
    if(sp==NULL){
        fp=nullptr;
    }
    fclose(sp);

    if (fp != NULL) {
        cout << "REGISTRAR ACTIVIDADES" << endl
            << "-------------------------------------------" << endl
            << "Nombre de la actividad: ";
        fflush(stdin);
        cin.getline(actividad.NombreAct, 100, '\n');

        do {
            cout << "Horario de la actividad(FORMATO: HH:MM): ";
            fflush(stdin);
            cin.getline(actividad.Horario, 50, '\n');
            if (!validHourFormat(actividad.Horario)) {
                cout << "El formato ingresado no es valido." << endl;
            }
        } while (!validHourFormat(actividad.Horario));

        do {
            cout << "Nombre del entrenador encargado: "; fflush(stdin); cin.getline(actividad.entrenadorEncargado, 100, '\n');
            if (!validTrainer(actividad.entrenadorEncargado, actividad.Horario)) {
                cout << "Error: el entrenador no esta disponible o no esta registado." << endl;
            }
        } while (!validTrainer(actividad.entrenadorEncargado, actividad.Horario));

        fwrite(&actividad, sizeof(Actividades), 1, fp);
        cout << "Actividad registrada correctamente." << endl;
    }
    else {
        cout << "No hay ningun entrenador disponible." << endl;
    }

    fclose(fp);
    Limpiar();
}

/**
 * Nombre: listar()
 * @param fp Puntero.
 * @param usuario Estructura del usuario.
 * @param entrenador Estructura del entrenador.
 * @param actividad Estructura de la actividad.
 * Tipo: sin tipo.
 * Descripcion: Permite visualizar los usuarios registrados.
*/
void listar(FILE* fp, struct entrenadores entrenador, struct usuarios usuario, struct Actividades actividad) {
    fp = fopen("Usuarios.dat", "rb");
    if (fp != NULL) {
        cout << "USUARIOS: " << endl
            << "----------------------------------------------" << endl;
        fread(&usuario, sizeof(usuarios), 1, fp);
        while (!feof(fp)) {
            cout << "Nombre: " << usuario.usuario << endl
                << "Contrasenia: " << usuario.contrasenia << endl
                << "Apellido y nombre: " << usuario.apYNom << endl
                << "Tipo de cuenta: " << usuario.tipo << "(" << (usuario.tipo == 1 ? "Secretario" : "Administrador") << ")" << endl << endl;
            fread(&usuario, sizeof(usuarios), 1, fp);
        }
        fclose(fp);
    }
    else {
        cout << "No hay ning�n usuario cargado a�n." << endl << endl;
    }

    cout << "ENTRENADORES" << endl
        << "----------------------------------------------" << endl;

    fp = fopen("Entrenadores.dat", "rb");
    if (fp != NULL) {
        fread(&entrenador, sizeof(entrenadores), 1, fp);
        while (!feof(fp)) {
            cout << "Apellido y nombre:" << entrenador.apYNom << endl
                << "Legajo: " << entrenador.legajo << endl
                << "Contrasenia: " << entrenador.contrasenia << endl;
            cout << "Dias de atencion: ";
            for (int i = 0; i < (sizeof(entrenador.dias) / sizeof(entrenador.dias[0])); i++) {
                if (strcmp(entrenador.dias[i], "-") != 0) {
                    cout << entrenador.dias[i] << ", ";
                }
            }
            cout << endl << endl;
            fread(&entrenador, sizeof(entrenadores), 1, fp);
        }

        cout << endl;
    }
    else {
        cout << "No hay ningun entrenador registrado aun." << endl << endl;
    }
    fclose(fp);

    cout << "ACTIVIDADES" << endl
        << "----------------------------------------------" << endl;

    fp = fopen("Actividades.dat", "rb");
    if (fp != NULL) {
        fread(&actividad, sizeof(Actividades), 1, fp);
        while (!feof(fp)) {
            cout << "Actividad: " << actividad.NombreAct << endl
                << "Horario: " << actividad.Horario << endl
                << "Entrenador: " << actividad.entrenadorEncargado << endl << endl;
            fread(&actividad, sizeof(Actividades), 1, fp);
        }
    }
    else {
        cout << "No hay actividades registradas." << endl;
    }
    fclose(fp);

    Limpiar();
}
/**
 * Nombre: login()
 * @param fp Puntero
 * @param usuario Estructura del usuario
 * @param entrenador Estructura del entrenador
 * @param respuesta 1: Secretario / 2: Entrenador / 3: Administrador.
 * Tipo: booleana.
 * Descripci�n: permite el inicio de sesi�n de los usuarios y entrenadores.
*/
void login(FILE* fp, struct entrenadores& entrenador, struct usuarios& usuario, int respuesta) {
    int legajo;
    bool sesion;
    char nombreUsuario[100],
        contrasenia[32];

    switch (respuesta) {
    case 1:
        fp = fopen("Usuarios.dat", "rb");

        cout << "Ingresar nombre de usuario: ";
        fflush(stdin);
        cin.getline(nombreUsuario, 100, '\n');
        cout << "Ingresar contrasenia: ";
        fflush(stdin);
        cin.getline(contrasenia, 32, '\n');

        fread(&usuario, sizeof(usuarios), 1, fp);
        while (!feof(fp)) {
            if (strcmp(nombreUsuario, usuario.usuario) == 0 && strcmp(contrasenia, usuario.contrasenia) == 0) {
                sesion = true;
                break;
            }
            else {
                sesion = false;
            }
            fread(&usuario, sizeof(usuarios), 1, fp);
        }

        fclose(fp);
        if (sesion) {
            cout << "Sesion iniciada." << endl;
        }
        else {
            usuario={};
            cout << "Error de autenticacion." << endl;
        }
        Limpiar();
        break;
    case 2:
        fp = fopen("Entrenadores.dat", "rb");

        cout << "Ingresar legajo: ";
        cin >> legajo;
        cout << "Ingresar contrasenia: ";
        fflush(stdin);
        cin.getline(contrasenia, 32, '\n');

        fread(&entrenador, sizeof(entrenadores), 1, fp);
        while (!feof(fp)) {
            if (legajo == entrenador.legajo && strcmp(contrasenia, entrenador.contrasenia) == 0) {
                sesion = true;
                break;
            }
            else {
                sesion = false;
            }
            fread(&entrenador, sizeof(entrenadores), 1, fp);
        }

        fclose(fp);
        if (sesion) {
            cout << "Sesion iniciada." << endl;
        }
        else {
            cout << "Error de autenticacion." << endl;
        }
        Limpiar();
        break;
    default:
        cout << "La opcion no existe." << endl;
        Limpiar();
        break;
    }
}

/**
 * Nombre: registrar()
 * @param fp Puntero.
 * @param usuario Estructura del usuario.
 * @param entrenador Estructura del entrenador.
 * Tipo: Sin tipo.
 * Retorna: Nada.
 * Permite el registro de nuevos usuarios(secretarios o administradores) y entrenadores.
*/
void registrar(FILE* fp, FILE* leer, struct entrenadores entrenador, struct usuarios usuario) {
    char auxDay[60];
    int respuesta,
        cantDias,
        c = 0;
    struct entrenadores entrenador2;

    cout << "REGISTRAR" << endl
        << "-------------------" << endl
        << "1. USUARIO" << endl
        << "2. ENTRENADOR" << endl
        << "-------------------" << endl
        << "Respuesta: "; cin >> respuesta;

    cout << endl;

    switch (respuesta)
    {
    case 1:
        fp = fopen("Usuarios.dat", "a+b");
        cout << "Registrar Usuario" << endl
            << "1. Secretario." << endl
            << "2. Administrador." << endl;
        do {
            cout << "Respuesta: "; cin >> usuario.tipo;
            if (usuario.tipo != 1 && usuario.tipo != 2) {
                cout << "El tipo de usuario no existe." << endl;
            }
        } while (usuario.tipo != 1 && usuario.tipo != 2);

        cout << endl;

        do {
            cout << "Ingresar usuario: ";
            fflush(stdin);
            cin.getline(usuario.usuario, 100, '\n');
            if (!repetition(fp, usuario.usuario, usuario)) {
                cout << "El nombre de usuario ya se encuentra en uso." << endl;
            }
        } while (!validUser(usuario.usuario) || !repetition(fp, usuario.usuario, usuario));

        cout << endl;

        do {
            cout << "Ingresar contrasenia: ";
            fflush(stdin);
            cin.getline(usuario.contrasenia, 32, '\n');
        } while (!validPass(usuario.contrasenia));

        cout << endl;

        do {
            cout << "Ingresar nombre completo: ";
            fflush(stdin);
            cin.getline(usuario.apYNom, 60, '\n');
        } while (!validName(usuario.apYNom));

        cout << endl;

        fwrite(&usuario, sizeof(usuarios), 1, fp);
        fclose(fp);
        cout << "Registro exitoso." << endl << endl;
        Limpiar();
        break;
    case 2:
        fp = fopen("Entrenadores.dat", "a+b");
        cout << "Registrar Entrenador" << endl;
        do {
            cout << "Ingresar nombre: ";
            fflush(stdin);
            cin.getline(entrenador.apYNom, 60, '\n');
        } while (!validName(entrenador.apYNom));

        cout << endl;

        do {
            cout << "Cantidad de dias de trabajo: "; cin >> cantDias;
            if(cantDias>6){
                cout << "La cantidad de dias no debe ser mayor a 6." << endl;
            }
        } while(cantDias>6);
        for (int i = 0; i < (sizeof(entrenador.dias) / sizeof(entrenador.dias[0])); i++) {
            if (i < cantDias) {
                do {
                    cout << "Ingresar dia " << i + 1 << ": "; fflush(stdin);
                    cin.getline(entrenador.dias[i], 10, '\n');
                    if (!validDayName(entrenador.dias[i])) {
                        cout << "El dia ingresado no es correcto." << endl;
                    }
                } while (!validDayName(entrenador.dias[i]));
            }
            else {
                strcpy(entrenador.dias[i], "-");
            }
        }

        cout << endl;

        do {
            cout << "Ingresar contrasenia: ";
            fflush(stdin);
            cin.getline(entrenador.contrasenia, 32, '\n');
        } while (!validPass(entrenador.contrasenia));

        cout << endl;
        leer = fopen("Entrenadores.dat", "rb");
        fread(&entrenador2, sizeof(entrenadores), 1, leer);
        if (leer != NULL) {
            while (!feof(leer)) {
                c++;
                fread(&entrenador2, sizeof(entrenadores), 1, leer);
            }
            entrenador.legajo = c;
        }
        else {
            entrenador.legajo = 1;
        }
        fclose(leer);

        cout << "Registro exitoso." << endl;
        cout << "Legajo asignado: " << entrenador.legajo << endl;
        fwrite(&entrenador, sizeof(entrenadores), 1, fp);
        fclose(fp);
        Limpiar();
        break;
    default:
        cout << "La opcion no existe." << endl;
        break;
    }
}

/**
 * Nombre: Limpiar()
 * Tipo: sin tipo.
 * @param -
 * Hace una pausa, y luego limpia la consola.
*/
void Limpiar() {
    cout << endl << "Presione cualquier tecla para continuar." << endl;
    getch();
    system("CLS");
}

//Num. del 0 al 9: 48-57
//Letras mayusculas: 65-90
//Letras minusculas: 97-122 

usuarios registrarAdmin(FILE* fp, struct usuarios usuario) {
    fp = fopen("Usuarios.dat", "a+b");

    usuario.tipo = 2;
    do {
        cout << "Ingresar usuario: ";
        fflush(stdin);
        cin.getline(usuario.usuario, 100, '\n');
        if (!validUser(usuario.usuario) || !repetition(fp, usuario.usuario, usuario)) {
            cout << "Usuario invalido." << endl;
        }
    } while (!validUser(usuario.usuario) || !repetition(fp, usuario.usuario, usuario));
    cout << endl;
    do {
        cout << "Ingresar contrasenia: ";
        fflush(stdin);
        cin.getline(usuario.contrasenia, 32, '\n');
        if (!validPass(usuario.contrasenia)) {
            cout << "Contrasenia no valida" << endl;
        }
    } while (!validPass(usuario.contrasenia));
    cout << endl;
    do {
        cout << "Ingresar nombre completo: ";
        fflush(stdin);
        cin.getline(usuario.apYNom, 60, '\n');
        if (!validName(usuario.apYNom)) {
            cout << "Nombre no valido." << endl;
        }
    } while (!validName(usuario.apYNom));
    cout << endl;
    fwrite(&usuario, sizeof(usuarios), 1, fp);
    fclose(fp);
    cout << "Registro exitoso." << endl << endl;

    return usuario;
}

void mayorCarga(entrenadores &entrenador, int &mayor){
    FILE *fp,
        *sp;
    Actividades actividad;
    entrenadores entrenador2;
    int c=0;
    int horasActividades=0;
    int diasEntrenadores=0;
    int horasTotales=0;

    sp=fopen("Entrenadores.dat", "rb");
    if(sp!=NULL){
        fread(&entrenador2, sizeof(entrenadores), 1, sp);
        while(!feof(sp)){
            horasTotales=cantHoras(entrenador2.apYNom)*cantDias(entrenador2.dias);
            if(horasTotales>mayor){
                mayor=horasTotales;
                entrenador=entrenador2;
            }
            fread(&entrenador2, sizeof(entrenadores), 1, sp);
        }
    } else {
        cout << "No hay entrenadores registrados." << endl;
        entrenador.legajo=-1;
    }
    fclose(sp);
}

int cantHoras(char nombre[60]){
    FILE *fp;
    fp=fopen("Actividades.dat", "rb");
    Actividades actividad;
    int c=0;
    
    if(fp!=NULL){
        fread(&actividad, sizeof(Actividades), 1, fp);
        while(!feof(fp)){
            if(strcmp(nombre, actividad.entrenadorEncargado)==0){
                c++;
            }
            fread(&actividad, sizeof(Actividades), 1, fp);
        }
    } else {
        cout << "No hay actividades cargadas." << endl;
    }

    return c;
}

int cantDias(Dia cantDias[6]){
    int c=0;
    for(int i=0; i<6; i++){
        if(strcmp(cantDias[i], "-")!=0){
            c++;
        }
    }
    return c;
}