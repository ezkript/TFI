/*
TO-DO: 
 *Probar funcionalidad: calcular paga a entrenadores.
 *Agregar funcionalidad: Entrenador con mayor carga horaria.
*/

#include <locale.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <iostream>
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
    char contrasenia[32];
    Dia dias[6];
};

void registrar(FILE* fp, FILE* leer, struct entrenadores entrenador, struct usuarios usuario);
void login(FILE* fp, struct entrenadores &entrenador, struct usuarios &usuario, int respuesta);
void listar(FILE* fp, struct entrenadores entrenador, struct usuarios usuario, struct Actividades actividad);
bool validPass(char contrasenia[32]);
bool validUser(char user[100]);
bool validName(char name[60]);
bool repetition(FILE* fp, char user[100], struct usuarios usuario);
void Limpiar();
usuarios registrarAdmin(FILE *fp, struct usuarios usuario);
void registrarActividad(FILE *fp, Actividades actividad);
bool validTrainer(char actividad[100], char horario[50]);
bool validHourFormat(char hora[50]);
void calcularPago(entrenadores entrenador);

int main(){
    FILE *escribir,
        *leer;
    usuarios usuario;
    entrenadores entrenador;
    Actividades actividad;
    int respuesta;
    // //Establece el idioma a español 
    // setlocale(LC_ALL, "spanish");
    // //Establecer el idioma de la consola al español
    // SetConsoleCP(1252);
    // SetConsoleOutputCP(1252);
    leer = fopen("Usuarios.dat", "rb");
    if(leer==NULL){
        cout << "Bienvenido a la aplicacion para gestionar su gimnasio. \nComo es su primer ingreso, es necesario crear una cuenta de administrador: " << endl << endl;
        usuario=registrarAdmin(escribir, usuario);
        Limpiar();
        fclose(leer);
    } else {
        fclose(leer);
    }

    do
    {
        cout << "Bienvenid@ " << (strlen(usuario.apYNom)<1 ? "administrador" : usuario.apYNom) << "." << endl
        << "-----------------------------------------------" << endl
        << "1. Iniciar sesion." << endl
        << "2. Registrar usuario de Recepcion." << endl
        << "3. Registrar actividades del gym." << endl
        << "4. Calcular el pago al entrenador." << endl
        << "5. Entrenador con mayor carga horaria." << endl
        << "6. Listar usuarios y actividades." << endl
        << "7. Salir. " << endl
        << "-----------------------------------------------" << endl
        << "Ingresar una opcion: ";cin >> respuesta;
        system("CLS");

        switch (respuesta){
        case 1:
            login(escribir, entrenador, usuario, 1);
            break;
        case 2:
            if(usuario.tipo==2){
                registrar(escribir, leer, entrenador, usuario);
            } else {
                cout << "No hay ninguna sesion de administrador activa." << endl; 
            }
            break;
        case 3:
            if(usuario.tipo==2){
                registrarActividad(escribir, actividad);
            } else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
            break;
        case 4:
            if(usuario.tipo==2){
                calcularPago(entrenador);
            } else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
            break;
        case 5:

            break;
        case 6:
            if(usuario.tipo==2){
                listar(escribir, entrenador, usuario, actividad);
            } else {
                cout << "No hay ninguna sesion de administrador activa." << endl;
            }
        break;
        case 7:
            break;
        default:
            break;
        }
    } while (respuesta!=7);
    
    return 0;
}

void calcularPago(entrenadores entrenador){
    char trainerName[50];
    FILE *sp;
    int c=0;

    sp=fopen("Turnos.dat", "rb");
    if(sp!=NULL){
        cout << "Nombre del entrenador: ";
        fflush(stdin);
        cin.getline(trainerName, 50, '\n');

        fread(&entrenador, sizeof(entrenadores), 1, sp);
        while(!feof(sp)){
            if(strcmp(strlwr(trainerName),strlwr(entrenador.apYNom))==0){
                c++;
            }
            fread(&entrenador, sizeof(entrenadores), 1, sp);
        }
    } else {
        cout << "No hay personas realizando actividades." << endl;
    }
    fclose(sp);

    if(c!=0){
        cout << "La paga correspondiente al entrenador " << trainerName << "es $" << c*1500 << "." << endl << endl;
    } else {
        cout << "El entrenador no tiene ningun grupo de personas asignado." << endl << endl;
    }
    Limpiar();
}

void registrarActividad(FILE *fp, Actividades actividad){
    fp=fopen("Actividades.dat", "ab");
    if(fp!=NULL){
        cout << "REGISTRAR ACTIVIDADES" << endl
        << "-------------------------------------------" << endl
        << "Nombre de la actividad: "; 
        fflush(stdin); 
        cin.getline(actividad.NombreAct, 100, '\n');

        do{
            cout << "Horario de la actividad(FORMATO: HH:MM): ";
            fflush(stdin);
            cin.getline(actividad.Horario, 50, '\n');
            if(!validHourFormat(actividad.Horario)){
                cout << "El formato ingresado no es valido." << endl;
            }
        } while(!validHourFormat(actividad.Horario));
        
        do {
            cout << "Nombre del entrenador encargado: "; fflush(stdin); cin.getline(actividad.entrenadorEncargado, 100, '\n');
            if(!validTrainer(actividad.entrenadorEncargado, actividad.Horario)){
                cout << "Error: el entrenador no esta disponible o no esta registado." << endl;
            }
        } while (!validTrainer(actividad.entrenadorEncargado, actividad.Horario));
        
        fwrite(&actividad, sizeof(Actividades), 1, fp);
        fclose(fp);
        cout << "Actividad registrada correctamente." << endl;
    } else {
        cout << "Ha ocurrido un error." << endl;
    }
    Limpiar();
}

bool validTrainer(char entrenador[100], char horario[50]){
    FILE *fp;
    Actividades actividad;
    entrenadores entrenador2;
    int flag=0;

    fp=fopen("Entrenadores.dat", "rb");
    if(fp!=NULL){
        fread(&entrenador2, sizeof(entrenadores), 1, fp);

        while(!feof(fp)){
            if(strcmp(entrenador2.apYNom, entrenador)==0){
                flag=1;
            }
            fread(&entrenador2, sizeof(entrenadores), 1, fp);
        }

        if(flag==0){
            fclose(fp);
            return false;
        }
    } else {
        return false;
    }
    fclose(fp);

    fp=fopen("Actividades.dat", "rb");
    if(fp==NULL){
        return true;
    } else {
        fread(&actividad, sizeof(Actividades), 1, fp);
        while(!feof(fp)){
            if(strcmp(entrenador,actividad.entrenadorEncargado)==0 && strcmp(horario, actividad.Horario)==0){
                fclose(fp);
                return false;
            }
            fread(&actividad, sizeof(Actividades), 1, fp);
        }
    }
    fclose(fp);

    return true;
}

bool validHourFormat(char hora[50]){
    if(strlen(hora)>5) return false;
    if (isdigit(int(hora[0]))!=0 && 
        isdigit(int(hora[1]))!=0 && 
        int(hora[2])==58 && 
        isdigit(int(hora[3]))!=0 && 
        isdigit(int(hora[4]))!=0);
    else {
        return false;
    }
    
    if(int(hora[0])==48 || int(hora[0])==49){
        if(int(hora[1])<48 || int(hora[1])>57){
            return false;
        }
    } else if(int(hora[0])==50){
        if(int(hora[1])<48 || int(hora[1])>51){
            return false;
        }
    } else {
        return false;
    }

    if(int(hora[3])<48 || int(hora[3])>53){
        return false;
    }
    
    return true;
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
    if(fp!=NULL){
        cout << "USUARIOS: " << endl 
        << "----------------------------------------------" << endl;
        fread(&usuario, sizeof(usuarios), 1, fp);
        while (!feof(fp)) {
            cout << "Nombre: " << usuario.usuario << endl
                << "Contrasenia: " << usuario.contrasenia << endl
                << "Apellido y nombre: " << usuario.apYNom << endl
                << "Tipo de cuenta: " << usuario.tipo << "("<< (usuario.tipo==1?"Secretario":"Administrador") << ")" << endl << endl;
            fread(&usuario, sizeof(usuarios), 1, fp);
        }
        fclose(fp);
    } else {
        cout << "No hay ningún usuario cargado aún." << endl << endl;
    }
    
    cout << "ENTRENADORES" << endl
    << "----------------------------------------------" << endl;

    fp = fopen("Entrenadores.dat", "rb");
    if(fp!=NULL){
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
    } else {
        cout << "No hay ningun entrenador registrado aun." << endl << endl;
    }
    fclose(fp);
    
    cout << "ACTIVIDADES" << endl
    << "----------------------------------------------" << endl;

    fp=fopen("Actividades.dat", "rb");
    if(fp!=NULL){
        fread(&actividad, sizeof(Actividades), 1, fp);
        while(!feof(fp)){
            cout << "Actividad: " << actividad.NombreAct << endl
            << "Horario: " << actividad.Horario << endl
            << "Entrenador: " << actividad.entrenadorEncargado << endl << endl;
            fread(&actividad, sizeof(Actividades), 1, fp);
        }
    } else {
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
 * Descripción: permite el inicio de sesión de los usuarios y entrenadores.
*/
void login(FILE* fp, struct entrenadores &entrenador, struct usuarios &usuario, int respuesta) {
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
        Limpiar();
        break;
    case 2:
        fp = fopen("Entrenadores.dat", "a+b");
        cout << "Registrar Entrenador" << endl;
        do {
            cout << "Ingresar nombre: ";
            fflush(stdin);
            cin.getline(entrenador.apYNom, 60, '\n');
            if (!validName(entrenador.apYNom)) {
                cout << "El nombre ingresado no es valido." << endl;
            }
        } while (!validName(entrenador.apYNom));

        cout << endl;

        cout << "Cantidad de dias de trabajo: "; cin >> cantDias;
        for (int i = 0; i < (sizeof(entrenador.dias) / sizeof(entrenador.dias[0])); i++) {
            if (i < cantDias) {
                do {
                    cout << "Ingresar dia " << i + 1 << ": "; fflush(stdin);
                    cin.getline(entrenador.dias[i], 10, '\n');
                    if (!validName(entrenador.dias[i])) {
                        cout << "El dia ingresado no es correcto." << endl;
                    }
                } while (!validName(entrenador.dias[i]));
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
            if (!validPass(entrenador.contrasenia)) {
                cout << "La contrasenia es invalida." << endl;
            }
            else {
                break;
            }
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
    system("PAUSE");
    system("CLS");
}

//Num. del 0 al 9: 48-57
//Letras mayusculas: 65-90
//Letras minusculas: 97-122 

/**
 * Nombre: validPass()
 * @param contrasenia Contraseña a validar.
 * Tipo: Booleana
 * Retorna verdadero si la contraseña es válida, de lo contrario, retorna falso.
*/
bool validPass(char contrasenia[32]) {
    bool valid[3];
    valid[0] = false;
    valid[1] = false;
    valid[2] = false;
    char contrasenia2[32];
    strcpy(contrasenia2, contrasenia);

    //Valida que la contraseña tenga entre 6 y 32 caracteres.
    if (strlen(contrasenia) < 6 || strlen(contrasenia) > 32)return false;

    /*
    Valida que la contraseña tenga por lo menos 1 de los siguientes caracteres:
    -Letra mayúscula.
    -Letra minúscula.
    -Número.
    */
    for (int i = 0; i < strlen(contrasenia); i++) {
        //Validación del número.
        if (int(contrasenia[i]) >= 48 && int(contrasenia[i]) <= 57) {
            valid[0] = true;
        }

        //Validación de la letra mayúscula.
        if (int(contrasenia[i]) >= 65 && int(contrasenia[i]) <= 90) {
            valid[1] = true;
        }

        //Validación de la letra minúscula.
        if (int(contrasenia[i]) >= 97 && int(contrasenia[i]) <= 122) {
            valid[2] = true;
        }
        //lamamalinda123
    }
    if (valid[0] == false || valid[1] == false || valid[2] == false) {
        return false;
    }

    //Valida que la contraseña tenga un máximo de 3 números.
    for (int i = 0, c = 0; i < strlen(contrasenia); i++) {
        if (int(contrasenia[i]) >= 48 && int(contrasenia[i]) <= 57) {
            c++;
            if (c > 3) {
                return false;
            }
        }
        else {
            c = 0;
        }
    }

    //Valida que la contraseña sea alfanumérica.
    for (int i = 0; i < strlen(contrasenia); i++) {
        if (!(
            (int(contrasenia[i]) >= 48 && int(contrasenia[i]) <= 57) ||
            isalpha(contrasenia[i]) != 0
            ))
            return false;
    }

    /*
    Valida que la contraseña no contenga 2 letras
    alfabéticamente consecutivas.
    */
    strlwr(contrasenia2);
    for (int i = 0, c = 0; i < strlen(contrasenia2); i++) {
        if (isalpha(contrasenia2[i]) != 0) {
            if ((int(contrasenia2[i + 1]) - 1) == int(contrasenia2[i])) {
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
 * Retorna verdadero si el usuario es válido, de lo contrario, retorna falso.
*/
bool validUser(char user[100]) {

    //Valida que la primera letra del usuario sea minúscula.
    if (!(int(user[0]) >= 97 && int(user[0]) <= 122))return false;

    //Valida que el nombre de usuario tenga entre 6 y 10 caracteres.
    if (strlen(user) < 6 || strlen(user) > 10)return false;

    //Valida que el nombre de usuario NO tenga más de 3 números.
    for (int i = 0, c = 0; i < strlen(user); i++) {
        if (int(user[i]) >= 48 && int(user[i]) <= 57) {
            c++;
        }

        if (c == 4) {
            return false;
        }
    }

    /*
    Valida que el nombre solo esté conformado
    por caracteres alfanuméricos y el siguiente
    conjunto numérico: + - / * ? ¿ ! ¡
    */
    for (int i = 0; i < strlen(user); i++) {
        if (
            !(int(user[i]) >= 97 && int(user[i]) <= 122) &&
            !(int(user[i]) >= 65 && int(user[i]) <= 90) &&
            !(int(user[i]) >= 48 && int(user[i]) <= 57) &&
            !(int(user[i]) == 43 || int(user[i]) == 45 || int(user[i]) == 47 || int(user[i]) == 42 || int(user[i]) == 63 || int(user[i]) == 168 || int(user[i]) == 173 || int(user[i]) == 33))return false;
    }

    //Verifica que el usuario contenga mínimo 2 mayúsculas.
    for (int i = 0, c = 0; i < strlen(user); i++) {
        if (int(user[i]) >= 65 && int(user[i]) <= 90) {
            c++;
        }

        if (i == strlen(user) - 1 && c < 2) {
            return false;
        }
    }

    return true;
}

/**
 * Nombre: validName()
 * @param name Apellido y nombre del usuario.
 * Tipo: Booleana.
 * Retorna verdadero si el nombre del usuario es válido, sinó, falso.
*/
bool validName(char name[60]) {

    //Permite únicamente el ingreso de caracteres alfabéticos.
    for (int i = 0; i < strlen(name); i++) {
        if (isalpha(name[i]) == 0 && int(name[i]) != 32) {
            return false;
        }
    }

    return true;
}
/**
 * Nombre: repetition()
 * @param fp Puntero
 * @param user Nombre de usuario
 * @param Usuario
 * Tipo: Booleana.
 * Descripcion: Validar que el nombre de usuario ingresado no sea repetido.
*/
bool repetition(FILE* fp, char user[100], struct usuarios usuario) {
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

usuarios registrarAdmin(FILE *fp, struct usuarios usuario){
    fp = fopen("Usuarios.dat", "a+b");

    usuario.tipo=2;
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
