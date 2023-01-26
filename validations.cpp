#include <string.h>
#include <stdlib.h>
#include <cctype>
#include <iostream>
using namespace std;

#include "Structures.h"
#include "validations.h"

/**
 * Nombre: validTrainer()
 * @param entrenador Nombre del entrenador
 * @param horario Horario de la actividad
 * Tipo: Booleana
 * Retorna verdadero si el entrenador está disponible en el horario indicado, sino, retorna falso
*/
bool validTrainer(char entrenador[100], char horario[50]) {
    FILE* fp;
    Actividades actividad;
    entrenadores entrenador2;
    int flag = 0;

    fp = fopen("Entrenadores.dat", "rb");
    if (fp != NULL) {
        fread(&entrenador2, sizeof(entrenadores), 1, fp);

        while (!feof(fp)) {
            if (strcmp(entrenador2.apYNom, entrenador) == 0) {
                flag = 1;
            }
            fread(&entrenador2, sizeof(entrenadores), 1, fp);
        }

        if (flag == 0) {
            fclose(fp);
            return false;
        }
    }
    else {
        return false;
    }
    fclose(fp);

    fp = fopen("Actividades.dat", "rb");
    if (fp == NULL) {
        return true;
    }
    else {
        fread(&actividad, sizeof(Actividades), 1, fp);
        while (!feof(fp)) {
            if (strcmp(entrenador, actividad.entrenadorEncargado) == 0 && strcmp(horario, actividad.Horario) == 0) {
                fclose(fp);
                return false;
            }
            fread(&actividad, sizeof(Actividades), 1, fp);
        }
    }
    fclose(fp);

    return true;
}

/**
 * Nombre: validHourFormat()
 * @param hora Cadena de texto a evaluar
 * Tipo: Booleana
 * Retorna verdadero si la hora ingresada respeta el formato HH:MM; de lo contrario, retorna falso
*/
bool validHourFormat(char hora[50]) {
    if (strlen(hora) > 5) return false;
    if (isdigit(int(hora[0])) != 0 &&
        isdigit(int(hora[1])) != 0 &&
        int(hora[2]) == 58 &&
        isdigit(int(hora[3])) != 0 &&
        isdigit(int(hora[4])) != 0);
    else {
        return false;
    }

    if (int(hora[0]) == 48 || int(hora[0]) == 49) {
        if (int(hora[1]) < 48 || int(hora[1]) > 57) {
            return false;
        }
    }
    else if (int(hora[0]) == 50) {
        if (int(hora[1]) < 48 || int(hora[1]) > 51) {
            return false;
        }
    }
    else {
        return false;
    }

    if (int(hora[3]) < 48 || int(hora[3]) > 53) {
        return false;
    }

    return true;
}

/**
 * Nombre: validPass()
 * @param contrasenia Contrase�a a validar.
 * Tipo: Booleana
 * Retorna verdadero si la contrase�a es v�lida, de lo contrario, retorna falso.
*/
bool validPass(char contrasenia[32]) {
    bool valid[3];
    valid[0] = false;
    valid[1] = false;
    valid[2] = false;
    char contrasenia2[32];
    strcpy(contrasenia2, contrasenia);

    //Valida que la contrasenia tenga entre 6 y 32 caracteres.
    if (strlen(contrasenia) < 6 || strlen(contrasenia) > 32){
        cout << "La contrasenia debe tener entre 6 y 32 caracteres." << endl;
        return false;
    }

    /*
    Valida que la contrasenia tenga por lo menos 1 de los siguientes caracteres:
    -Letra mayuscula.
    -Letra minuscula.
    -Numero.
    */
    for (int i = 0; i < strlen(contrasenia); i++) {
        //Validaci�n del n�mero.
        if (int(contrasenia[i]) >= 48 && int(contrasenia[i]) <= 57) {
            valid[0] = true;
        }

        //Validaci�n de la letra may�scula.
        if (int(contrasenia[i]) >= 65 && int(contrasenia[i]) <= 90) {
            valid[1] = true;
        }

        //Validaci�n de la letra min�scula.
        if (int(contrasenia[i]) >= 97 && int(contrasenia[i]) <= 122) {
            valid[2] = true;
        }
        
    }
    if (valid[0] == false || valid[1] == false || valid[2] == false) {
        cout << "La contrasenia debe contener al menos:" << endl 
        << "->1 numero." << endl
        << "->1 letra mayuscula." << endl 
        << "->1 letra minuscula." << endl;
        return false;
    }

    //Valida que la contrase�a tenga un m�ximo de 3 n�meros.
    for (int i = 0, c = 0; i < strlen(contrasenia); i++) {
        if (int(contrasenia[i]) >= 48 && int(contrasenia[i]) <= 57) {
            c++;
            if (c > 3) {
                cout << "La contrasenia solo puede contener hasta 3 caracteres numericos consecutivos" << endl;
                return false;
            }
        }
        else {
            c = 0;
        }
    }

    //Valida que la contrase�a sea alfanum�rica.
    for (int i = 0; i < strlen(contrasenia); i++) {
        if (!((int(contrasenia[i]) >= 48 && int(contrasenia[i]) <= 57) ||
            isalpha(contrasenia[i]) != 0)){
                cout << "La contrasenia no puede contener caracteres especiales ni espacios." << endl;
                return false;
            }
    }

    /*
    Valida que la contrase�a no contenga 2 letras
    alfab�ticamente consecutivas.
    */
    strlwr(contrasenia2);
    for (int i = 0, c = 0; i < strlen(contrasenia2); i++) {
        if (isalpha(contrasenia2[i]) != 0) {
            if ((int(contrasenia2[i + 1]) - 1) == int(contrasenia2[i])) {
                cout << "La contrasenia no puede contener 2 letras alfabeticamente consecutivas." << endl;
                return false;
            }
        }
    }

    return true;
}

/**
 * Nombre: validUser()
 * @param user Nombre de usuario a validar.
 * Tipo: Booleana.
 * Retorna verdadero si el usuario es v�lido, de lo contrario, retorna falso.
*/
bool validUser(char user[100]) {

    //Valida que la primera letra del usuario sea min�scula.
    if (!(int(user[0]) >= 97 && int(user[0]) <= 122)){
        cout << "La contrasenia debe comenzar en minuscula." << endl;
        return false;
    }
    
    //Valida que el nombre de usuario tenga entre 6 y 10 caracteres.
    if (strlen(user) < 6 || strlen(user) > 10){
        cout << "El nombre de usuario debe tener entre 6 y 10 caracteres." << endl;
        return false;
    }
    
    //Valida que el nombre de usuario NO tenga m�s de 3 n�meros.
    for (int i = 0, c = 0; i < strlen(user); i++) {
        if (int(user[i]) >= 48 && int(user[i]) <= 57) {
            c++;
        }

        if (c == 4) {
            cout << "El nombre de usuario no debe contener mas de 3 numeros." << endl;
            return false;
        }
    }

    /*
    Valida que el nombre solo est� conformado
    por caracteres alfanum�ricos y el siguiente
    conjunto num�rico: + - / * ? � ! �
    */
    for (int i = 0; i < strlen(user); i++) {
        if (
            !(int(user[i]) >= 97 && int(user[i]) <= 122) &&
            !(int(user[i]) >= 65 && int(user[i]) <= 90) &&
            !(int(user[i]) >= 48 && int(user[i]) <= 57) &&
            !(int(user[i]) == 43 || int(user[i]) == 45 || int(user[i]) == 47 || int(user[i]) == 42 || int(user[i]) == 63 || int(user[i]) == 168 || int(user[i]) == 173 || int(user[i]) == 33)){
                cout << "El nombre de usuario solo puede estar conformado por:" << endl
                << "-> Caracteres alfanumericos." << endl
                << "-> Los siguientes caracteres especiales: + - / * ? ¿ ! ¡" << endl;   
                return false;
            }
    }

    //Verifica que el usuario contenga m�nimo 2 may�sculas.
    for (int i = 0, c = 0; i < strlen(user); i++) {
        if (int(user[i]) >= 65 && int(user[i]) <= 90) {
            c++;
        }

        if (i == strlen(user) - 1 && c < 2) {
            cout << "El nombre de usuario debe contener al menos 2 letras mayusculas." << endl;
            return false;
        }
    }

    return true;
}

/**
 * Nombre: validName()
 * @param name Apellido y nombre del usuario.
 * Tipo: Booleana.
 * Retorna verdadero si el nombre del usuario es v�lido, sin�, falso.
*/
bool validName(char name[60]) {

    //Permite �nicamente el ingreso de caracteres alfab�ticos.
    for (int i = 0; i < strlen(name); i++) {
        if (isalpha(name[i]) == 0 && int(name[i]) != 32) {
            cout << "El nombre solo puede contener letras." << endl;
            return false;
        }
    }

    return true;
}





