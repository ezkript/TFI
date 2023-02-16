#include <stdlib.h>
#include <iostream>
#include <limits>
#include <conio.h>
#include <string.h>
#include <cctype>
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

struct registraractividad{
 	char act[100];
 	char nombresocio[60];
    char nombreEntrenador[100];
 };

 struct registroRutina{
    char rutina[500];
    char grupo[100];
    char horario[50];
    char Entrenador[100];
 };

void validIntDataType(int &intVar, int numberToReplace);
void listarTurnos(FILE *fp);
int menu(entrenadores entrenador);
void login(FILE* fp, struct entrenadores& entrenador, struct usuarios& usuario, int respuesta);
void Limpiar();
void listarSocios(FILE *fp, entrenadores entrenador);
void registrarRutina(FILE *fp, entrenadores entrenador);
void verRutina(FILE *fp, entrenadores entrenador);

int main(){
    int respuesta;
    FILE *fp;
    entrenadores entrenador;
    usuarios usuario;
    do {
        respuesta=menu(entrenador);
        system("CLS");
        switch (respuesta)
        {
        case 1:
            login(fp, entrenador, usuario, 2);
            break;
        case 2:
            if(entrenador.tipo==3){
                listarSocios(fp, entrenador);
            } else {
                cout << "No hay una sesion de entrenador activa." << endl;
            }  
            Limpiar();
            break;
        case 3:
            if(entrenador.tipo==3){
                registrarRutina(fp, entrenador);
            } else {
                cout << "No hay una sesion de entrenador activa." << endl;
            }  
            Limpiar();
            break;
        case 4:
            if(entrenador.tipo==3){
                verRutina(fp, entrenador);
            } else {
                cout << "No hay una sesion de entrenador activa." << endl;
            }  
            Limpiar();
            break;
        case 5:
            break;
        // case 6:
        //     listarTurnos(fp);
        //     Limpiar();
        //     break;
        default:
            cout << "La opcion ingresada no existe." << endl;
            Limpiar();
            break;
        }
    } while(respuesta!=5);
    return 0;
}

int menu(entrenadores entrenador){
    int respuesta;
    cout << "\tBienvenid@ " << (strlen(entrenador.apYNom) < 1 ? "invitado" : entrenador.apYNom) << "." << endl
    << "----------------------------------" << endl
    << (strlen(entrenador.apYNom) < 1 ? " 1. Iniciar sesion.":" 1. Cambiar de cuenta.") << endl
    << " 2. Listado de socios y actividad que desarrollan." << endl
    << " 3. Registro de rutinas de gimnasia." << endl
    << " 4. Ver rutinas registradas." << endl
    << " 5. Salir." << endl
    << "-----------------------------------" << endl
    << " Respuesta: ";
    cin >> respuesta;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        respuesta=-1;
    }

    return respuesta;
}

void listarSocios(FILE *fp, entrenadores entrenador){
    fp=fopen("Turnos.dat", "rb");
    registraractividad actividad;
    char nombre1[60];
    char nombre2[100];
    strcpy(nombre1, entrenador.apYNom);
    if(fp!=NULL){
        fread(&actividad, sizeof(registraractividad), 1, fp);
        while(!feof(fp)){
            strcpy(nombre2, actividad.nombreEntrenador);
            strlwr(nombre1);
            strlwr(nombre2);
            if(strcmp(actividad.nombreEntrenador,entrenador.apYNom)==0){
                cout << "Nombre de la actividad: " << actividad.act << endl
                << "Nombre del socio: " << actividad.nombresocio << endl;
            }
            fread(&actividad, sizeof(registraractividad), 1, fp);
        }
    } else {
        cout << "No hay ningun turno registrado." << endl;
    }
    fclose(fp);
}

void Limpiar(){
    cout << endl << "Presione cualquier tecla para continuar." << endl;
    getch();
    system("CLS");
}

void listarTurnos(FILE *fp){
    fp = fopen("Turnos.dat", "rb");
    registraractividad actividad;
    if(fp!=NULL){
        fread(&actividad, sizeof(registraractividad), 1, fp);
        while(!feof(fp)){
            cout << "Nombre del socio: " << actividad.nombresocio << endl
            << "Actividad: " << actividad.act << endl 
            << "Entrenador: " << actividad.nombreEntrenador << endl << endl;
            fread(&actividad, sizeof(registraractividad), 1, fp);
        }

    } else {
        cout << "No hay turnos registrados." << endl;
    }
    fclose(fp);
}

void login(FILE* fp, entrenadores& entrenador, usuarios& usuario, int respuesta) {
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
        if(fp!=NULL){
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
        }
        if (sesion) {
            cout << "Sesion iniciada." << endl;
        }
        else {
            cout << "Error de autenticacion." << endl;
            entrenador={};
        }
        Limpiar();
        break;
    default:
        cout << "La opcion no existe." << endl;
        Limpiar();
        break;
    }
}

void registrarRutina(FILE *fp, entrenadores entrenador){
    fp=fopen("Actividades.dat", "rb");
    FILE *routine=fopen("Routine.dat", "ab");
    Actividades actividad;
    registroRutina rutina;
    bool flag=false;
    if(fp!=NULL){   
        do{
            rewind(fp);
            cout << "Nombre del grupo: "; fflush(stdin); cin.getline(rutina.grupo, 100, '\n');
            fread(&actividad, sizeof(Actividades), 1, fp);
            while(!feof(fp)){
                if((strcmp(rutina.grupo,actividad.NombreAct)==0)&&(strcmp(actividad.entrenadorEncargado,entrenador.apYNom)==0)){
                    strcpy(rutina.horario, actividad.Horario);
                    strcpy(rutina.Entrenador, actividad.entrenadorEncargado);
                    cout << "Rutina(max. 380 caracteres): "; fflush(stdin); cin.getline(rutina.rutina,500, '\n');
                    if(strlen(rutina.rutina)>380){
                        flag=false;
                    } else {
                        flag=true;
                    }
                    break;
                }
                fread(&actividad, sizeof(Actividades), 1, fp);
            }
            
            if(!flag){
                cout << "El nombre del grupo es incorrecto." << endl;
            }   
        } while (!flag);
        fwrite(&rutina, sizeof(registroRutina), 1, routine);
    } else {
        cout << "No hay turnos registrados." << endl;
    }
    fclose(fp);
    fclose(routine);
}

void verRutina(FILE *fp, entrenadores entrenador){
    fp=fopen("Routine.dat", "rb");
    registroRutina rutina;
    if(fp!=NULL){
        fread(&rutina, sizeof(registroRutina), 1, fp);
        while(!feof(fp)){
            if(strcmp(rutina.Entrenador,entrenador.apYNom)==0){
                cout << "Grupo: " << rutina.grupo << "(" << rutina.horario << ")" << endl 
                << "Rutina: " << rutina.rutina << endl << endl;
            }
            fread(&rutina, sizeof(registroRutina), 1, fp);
        }
    } else {
        cout << "No hay rutinas registradas." << endl;
    }
    fclose(fp);
}

void validIntDataType(int &intVar, int numberToReplace){
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        intVar=numberToReplace;
    }
}