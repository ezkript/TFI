#include <locale.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <conio.h>
#include <iostream>
#include <exception>
#include <limits>
using namespace std;

typedef char Dia[10];

struct Actividades {
    char NombreAct[100];
    char Horario[50];
    char entrenadorEncargado[100];
};

struct usuarios {
    char usuario[100];
    char contrasenia[32];
    char apYNom[60];
    int tipo;
};

struct entrenadores {
    char apYNom[60];
    int legajo;
    int tipo;
    char contrasenia[32];
    Dia dias[6];
};

bool validUser(char user[100]);
bool validTrainer(char actividad[100], char horario[50]);
bool validName(char name[60]);
bool validDayName(char name[60]);
bool validPass(char contrasenia[32]);
bool validHourFormat(char hora[50]);
void validIntDataType(int &intVar, int numberToReplace);
bool repetition(FILE* fp, char user[100], struct usuarios usuario);
void registrar(FILE* fp, FILE* leer, struct entrenadores entrenador, struct usuarios usuario);
void login(FILE* fp, struct entrenadores& entrenador, struct usuarios& usuario, int respuesta);
void listar(FILE* fp, struct entrenadores entrenador, struct usuarios usuario, struct Actividades actividad);
void Limpiar();
usuarios registrarAdmin(FILE* fp, struct usuarios usuario);
void registrarActividad(FILE* fp, Actividades actividad);
void calcularPago(Actividades actividad);
void mayorCarga(entrenadores &entrenador, int &mayor);
int cantDias(Dia cantDias[6]);
int cantHoras(char nombre[60]);

int main() {
    FILE* escribir=nullptr,
        * leer=nullptr;
    bool flag=false;
    usuarios usuario{};
    entrenadores entrenador{};
    Actividades actividad{};
    int respuesta=0,
        mayor=0;
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
        cout << " Bienvenid@ " << (strlen(usuario.apYNom) < 1 ? "administrador" : usuario.apYNom) << "." << endl
            << "-----------------------------------------------" << endl
            << (strlen(usuario.apYNom) < 1 ? " 1. Iniciar sesion.":" 1. Cambiar de cuenta.") << endl
            << " 2. Registrar usuario de Recepcion." << endl
            << " 3. Registrar actividades del gym." << endl
            << " 4. Calcular el pago al entrenador." << endl
            << " 5. Entrenador con mayor carga horaria." << endl
            << " 6. Listar usuarios y actividades." << endl
            << " 7. Salir. " << endl
            << "-----------------------------------------------" << endl;

        cout << " Ingresar una opcion: "; 
        cin >> respuesta;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            respuesta=0;
            flag=true;
        }
        
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
            Limpiar();
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
                calcularPago(actividad);
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
            (flag)
                ? cout << "Se debe ingresar un numero." << endl
                : cout << "La opcion elegida no existe." << endl;
            flag=false;
            Limpiar();
            break;
        }
    } while (respuesta != 7);

    return 0;
}


/**************************************************
 *----------------- VALIDACIONES -----------------*
 **************************************************/
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
        Limpiar();
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
        Limpiar();
        return false;
    }

    //Valida que la contrase�a tenga un m�ximo de 3 n�meros.
    for (int i = 0, c = 0; i < strlen(contrasenia); i++) {
        if (int(contrasenia[i]) >= 48 && int(contrasenia[i]) <= 57) {
            c++;
            if (c > 3) {
                cout << "La contrasenia solo puede contener hasta 3 caracteres numericos consecutivos" << endl;
                Limpiar();
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
                Limpiar();
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
                Limpiar();
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
        Limpiar();
        return false;
    }
    
    //Valida que el nombre de usuario tenga entre 6 y 10 caracteres.
    if (strlen(user) < 6 || strlen(user) > 10){
        cout << "El nombre de usuario debe tener entre 6 y 10 caracteres." << endl;
        Limpiar();
        return false;
    }
    
    //Valida que el nombre de usuario NO tenga m�s de 3 n�meros.
    for (int i = 0, c = 0; i < strlen(user); i++) {
        if (int(user[i]) >= 48 && int(user[i]) <= 57) {
            c++;
        }

        if (c == 4) {
            cout << "El nombre de usuario no debe contener mas de 3 numeros." << endl;
            Limpiar();
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
                Limpiar();
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
            Limpiar();
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

bool validDayName(char name[60]) {
    char namelwr[60];
    strcpy(namelwr, name);
    strlwr(namelwr);
    Dia diaSemana[]={"lunes", "martes", "miercoles", "jueves", "viernes", "sabado"};

    for(int i=0; i<6; i++){
        if(strcmp(diaSemana[i], namelwr)==0){
            return true;
        }
    }
    
    return false;
}

void validIntDataType(int &intVar, int numberToReplace){
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        intVar=numberToReplace;
    }
}

/*********************************************
 * --------------- FUNCIONES ----------------*
 *********************************************/

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

void calcularPago(Actividades actividad) {
    char trainerName[60];
    FILE* sp;
    int c = 0;

    sp = fopen("Actividades.dat", "rb");
    if (sp != NULL) {
        cout << "Nombre del entrenador: ";
        fflush(stdin);
        cin.getline(trainerName, 60, '\n');

        fread(&actividad, sizeof(Actividades), 1, sp);
        while (!feof(sp)) {
            if (strcmp(strlwr(trainerName), strlwr(actividad.entrenadorEncargado)) == 0) {
                c++;
            }
            fread(&actividad, sizeof(Actividades), 1, sp);
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
        cout << "El entrenador no tiene ninguna actividad asignada." << endl << endl;
    }
    Limpiar();
}

/**
 * Nombre: registrarActividad()
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
                << "Tipo: " << entrenador.tipo << endl;
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

        do {
            cout << "Ingresar legajo: ";
            cin >> legajo;
            validIntDataType(legajo, -404);
        } while(legajo==-404);

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
    int respuesta2,
        cantDias,
        c = 0;
    struct entrenadores entrenador2;

    cout << "REGISTRAR" << endl
        << "-------------------" << endl
        << "1. USUARIO" << endl
        << "2. ENTRENADOR" << endl
        << "-------------------" << endl
        << "Respuesta: ";
    
    cin >> respuesta2;
    validIntDataType(respuesta2, 0);
    cout << endl;
    system("CLS");
    switch (respuesta2)
    {
    case 1:
        fp = fopen("Usuarios.dat", "a+b");
        cout << "Registrar Usuario" << endl
            << "1. Secretario." << endl
            << "2. Administrador." << endl;
        do {
            cout << "Respuesta: ";
            cin >> usuario.tipo;
            validIntDataType(usuario.tipo, 5);
            if (usuario.tipo != 1 && usuario.tipo != 2) {
                cout << "El tipo de usuario no existe." << endl;
            }
        } while (usuario.tipo != 1 && usuario.tipo != 2);
        system("CLS");
        do {
            cout << "\tEl nombre de usuario debe cumplir los siguientes requisitos:" << endl
            << "-> Debe tener entre 6 y 10 caracteres." << endl 
            << "-> Debe comenzar con minuscula." << endl
            << "-> Debe tener al menos 2 mayusculas." << endl
            << "-> Puede estar conformado por numeros, letras o los siguientes caracteres: +, -, /,*,?,¿,!,¡" << endl
            << "-> Puede contener un maximo de 3 digitos." << endl << endl;
            cout << "Ingresar usuario: ";
            fflush(stdin);
            cin.getline(usuario.usuario, 100, '\n');
            if (!repetition(fp, usuario.usuario, usuario)) {
                cout << "El nombre de usuario ya se encuentra en uso." << endl;
                Limpiar();
            }
        } while (!validUser(usuario.usuario) || !repetition(fp, usuario.usuario, usuario));

        system("CLS");
        do {
            cout << "\tLa contrasenia debe cumplir con los siguientes requisitos: " << endl
            << "-> Debe contener al menos una letra mayuscula, una letra minuscula y un numero." << endl
            << "-> Debe estar conformada unicamente por caracteres alfanumericos." << endl
            << "-> Debe tener entre 6 y 32 caracteres." << endl
            << "-> No debe tener mas de 3 caracteres numericos consecutivos." << endl
            << "-> No debe contener 2 caracteres consecutivos que refieran a 2 letras alfabeticamente consecutivas ascendentemente." << endl << endl;
            cout << "Ingresar contrasenia: ";
            fflush(stdin);
            cin.getline(usuario.contrasenia, 32, '\n');
        } while (!validPass(usuario.contrasenia));

        system("CLS");

        do {
            cout << "Ingresar nombre completo: ";
            fflush(stdin);
            cin.getline(usuario.apYNom, 60, '\n');
        } while (!validName(usuario.apYNom));

        system("CLS");

        fwrite(&usuario, sizeof(usuarios), 1, fp);
        fclose(fp);
        cout << "Registro exitoso." << endl << endl;
        break;
    case 2:
        fp = fopen("Entrenadores.dat", "a+b");
        do {
            system("CLS");
            cout << "Registrar Entrenador" << endl;
            cout << "Ingresar nombre: ";
            fflush(stdin);
            cin.getline(entrenador.apYNom, 60, '\n');
        } while (!validName(entrenador.apYNom));

        system("CLS");

        do {
            cout << "Cantidad de dias de trabajo: "; 
            cin >> cantDias;
            validIntDataType(cantDias, 10);
            if(cantDias>6){
                cout << "La cantidad de dias no debe ser mayor a 6." << endl;
                Limpiar();
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

        system("CLS");

        do {
            cout << "\tLa contrasenia debe cumplir con los siguientes requisitos: " << endl
            << "-> Debe contener al menos una letra mayuscula, una letra minuscula y un numero." << endl
            << "-> Debe estar conformada unicamente por caracteres alfanumericos." << endl
            << "-> Debe tener entre 6 y 32 caracteres." << endl
            << "-> No debe tener mas de 3 caracteres numericos consecutivos." << endl
            << "-> No debe contener 2 caracteres consecutivos que refieran a 2 letras alfabeticamente consecutivas ascendentemente." << endl << endl;
            cout << "Ingresar contrasenia: ";
            fflush(stdin);
            cin.getline(entrenador.contrasenia, 32, '\n');
        } while (!validPass(entrenador.contrasenia));
        
        entrenador.tipo=3;
        
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