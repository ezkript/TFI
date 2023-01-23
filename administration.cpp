#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cctype>

using namespace std;

typedef char Dia[10];

struct usuarios {
    char usuario[10];
    char contrasenia[32];
    char apYNom[60];
    int tipo;
};

struct entrenadores{
    char apYNom[60];
    int legajo;
    char contrasenia[32];
    Dia dias[6];
};

void registrar(FILE *fp, FILE *leer, struct usuarios usuario, struct entrenadores entrenador);
bool login(FILE *fp, struct usuarios usuario, struct entrenadores entrenador, int );
void listar(FILE *fp, struct usuarios usuario, struct entrenadores entrenador);
bool validPass(char contrasenia[32]);
bool validUser(char user[10]);
bool validName(char name[60]);
bool repetition(FILE *fp, char user[32], struct usuarios usuario);
void Limpiar();

int main(void){
    FILE *escribir, *leer;
    int respuesta;
    bool sesion;
    usuarios usuario;
    entrenadores entrenador; 

    //Establece el idioma a español 
    setlocale(LC_ALL, "spanish");
    //Establecer el idioma de la consola al español
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

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
            sesion=login(escribir, usuario, entrenador, 3);
            break;
        case 2:
            if(sesion==true){
                registrar(escribir, leer, usuario, entrenador);
            } else {
                cout << "No hay ninguna sesión activa." << endl; 
            }
            break;
        case 3:
            listar(escribir, usuario, entrenador);
            break;
        default:
            break;
        }
    } while (respuesta!=5);
    
    return 0;
}
/**
 * Nombre: Listar()
 * @param fp Puntero.
 * @param usuario Estructura del usuario.
 * @param entrenador Estructura del entrenador.
 * Tipo: sin tipo.
 * Descripcion: Permite visualizar los usuarios registrados.
*/
void listar(FILE *fp, struct usuarios usuario, struct entrenadores entrenador){
    fp=fopen("Usuarios.dat", "rb");
    cout << "USUARIOS: " << endl << endl;
    fread(&usuario, sizeof(usuarios), 1, fp);
    while(!feof(fp)){
        cout << "Nombre: " << usuario.usuario << endl
        << "Contrasenia: " << usuario.contrasenia << endl
        << "Apellido y nombre: " << usuario.apYNom << endl
        << "Tipo de cuenta: " << usuario.tipo << endl << endl;
        fread(&usuario, sizeof(usuarios), 1, fp);
    }
    fclose(fp);
    cout << "ENTRENADORES" << endl << endl;

    fp=fopen("Entrenadores.dat", "rb");
    fread(&entrenador, sizeof(entrenadores), 1, fp);
    while(!feof(fp)){
        cout << "Apellido y nombre:" << entrenador.apYNom << endl
        << "Legajo: " << entrenador.legajo << endl
        << "Contrasenia: " << entrenador.contrasenia << endl;
        cout << "Dias de atencion: ";
        for(int i=0; i<(sizeof(entrenador.dias)/sizeof(entrenador.dias[0])); i++){
            if(strcmp(entrenador.dias[i],"-")!=0){
                cout << entrenador.dias[i] << ", ";
            }
        }
        cout << endl;
        fread(&entrenador, sizeof(entrenadores), 1, fp);
    }

    cout << endl;

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
bool login(FILE *fp, struct usuarios usuario, struct entrenadores entrenador, int respuesta){
    int legajo;
    bool sesion;
    char nombreUsuario[10],
        contrasenia[32];

    switch (respuesta){
    case 1:
        fp=fopen("Usuarios.dat", "rb");

        cout << "Ingresar nombre de usuario: ";
        fflush(stdin);
        cin.getline(nombreUsuario, 10, '\n');
        cout << "Ingresar contraseña: ";
        fflush(stdin);
        cin.getline(contrasenia, 32, '\n');

        fread(&usuario, sizeof(usuarios), 1, fp);
        while(!feof(fp)){
            if(usuario.tipo==1 && strcmp(nombreUsuario, usuario.usuario)==0 && strcmp(contrasenia, usuario.contrasenia)==0){
                sesion=true;
                break;
            } else {
                sesion=false;
            }
            fread(&usuario, sizeof(usuarios), 1, fp);
        }

        fclose(fp);
        if(sesion){
            cout << "Sesión iniciada." << endl;
        } else {
            cout << "Error de autenticación." << endl;
        }
        Limpiar();
        break;
    case 2:
        fp=fopen("Entrenadores.dat", "rb");

        cout << "Ingresar legajo: ";
        cin >> legajo;
        cout << "Ingresar contraseña: ";
        fflush(stdin);
        cin.getline(contrasenia, 32, '\n');

        fread(&entrenador, sizeof(entrenadores), 1, fp);
        while(!feof(fp)){
            if(legajo==entrenador.legajo && strcmp(contrasenia, entrenador.contrasenia)==0){
                sesion=true;
                break;
            } else {
                sesion=false;
            }
            fread(&entrenador, sizeof(entrenadores), 1, fp);
        }

        fclose(fp);
        if(sesion){
            cout << "Sesión iniciada." << endl;
        } else {
            cout << "Error de autenticación." << endl;
        }
        Limpiar();
        break;
    case 3:
        fp=fopen("Usuarios.dat", "rb");

        cout << "Ingresar nombre de usuario: ";
        fflush(stdin);
        cin.getline(nombreUsuario, 10, '\n');
        cout << "Ingresar contraseña: ";
        fflush(stdin);
        cin.getline(contrasenia, 32, '\n');

        fread(&usuario, sizeof(usuarios), 1, fp);
        while(!feof(fp)){
            if(usuario.tipo==2 && strcmp(nombreUsuario, usuario.usuario)==0 && strcmp(contrasenia, usuario.contrasenia)==0){
                sesion=true;
                break;
            } else {
                sesion=false;
            }
            fread(&usuario, sizeof(usuarios), 1, fp);
        }

        fclose(fp);
        if(sesion){
            cout << "Sesión iniciada." << endl;
        } else {
            cout << "Error de autenticación." << endl;
        }
        Limpiar();
        break;    
    default:
        cout << "La opcion no existe." << endl;
        Limpiar();
        break;
    }
    return sesion;
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
void registrar(FILE *fp, FILE *leer, struct usuarios usuario, struct entrenadores entrenador){
    int respuesta,
        cantDias,
        c=0;
    struct entrenadores entrenador2;

    cout << "REGISTRAR" << endl
    << "1. USUARIO" << endl
    << "2. ENTRENADOR" << endl
    << "Respuesta: "; cin >> respuesta;
    
    cout << endl;
    
    switch (respuesta)
    {
    case 1:
        fp=fopen("Usuarios.dat", "a+b");
        cout << "Registrar Usuario" << endl
        << "1. Secretario." << endl
        << "2. Administrador." << endl; 
        do{
            cout << "Respuesta: ";cin >> usuario.tipo;
            if(usuario.tipo != 1 && usuario.tipo!=2){
                cout << "El tipo de usuario no existe." << endl;
            }
        } while (usuario.tipo != 1 && usuario.tipo!=2);

        cout << endl;

        do{
            cout << "Ingresar usuario: ";
            fflush(stdin);
            cin.getline(usuario.usuario, 10, '\n');  
            if(!validUser(usuario.usuario) || !repetition(fp, usuario.usuario, usuario)){
                cout << "Usuario inválido." << endl;
            }
        } while (!validUser(usuario.usuario) || !repetition(fp, usuario.usuario, usuario));

        cout << endl;

        do{
            cout << "Ingresar contraseña: ";
            fflush(stdin);
            cin.getline(usuario.contrasenia, 32, '\n');
            if(!validPass(usuario.contrasenia)){
                cout << "Contraseña no válida" << endl;
            }
        } while (!validPass(usuario.contrasenia));

        cout << endl;

        do {
            cout << "Ingresar nombre completo: ";
            fflush(stdin);
            cin.getline(usuario.apYNom, 60, '\n');
            if(!validName(usuario.apYNom)){
                cout << "Nombre no válido." << endl;
            }
        } while (!validName(usuario.apYNom));

        cout << endl;

        fwrite(&usuario, sizeof(usuarios), 1, fp);
        fclose(fp);
        cout << "Registro exitoso." << endl << endl;
        Limpiar();
        break;
    case 2:
        fp=fopen("Entrenadores.dat", "a+b");
        cout << "Registrar Entrenador" << endl;
        do{
            cout << "Ingresar nombre: ";
            fflush(stdin);
            cin.getline(entrenador.apYNom, 60, '\n');
            if(!validName(entrenador.apYNom)){
                cout << "El nombre ingresado no es valido." << endl;
            }
        } while (!validName(entrenador.apYNom));

        cout << endl;
        
        cout << "Cantidad de días de trabajo: "; cin >> cantDias; 
        for(int i=0; i<(sizeof(entrenador.dias)/sizeof(entrenador.dias[0])); i++){
            if(i<cantDias){
                do{
                    cout << "Ingresar dia" << i+1 << ": "; fflush(stdin);
                    cin.getline(entrenador.dias[i], 10, '\n');
                    if(!validName(entrenador.dias[i])){
                        cout << "El día ingresado no es correcto." << endl;
                    } 
                } while(!validName(entrenador.dias[i]));
            } else {
                strcpy(entrenador.dias[i],"-");
            }
        }

        cout << endl;

        do {
            cout << "Ingresar contraseña: ";
            fflush(stdin);
            cin.getline(entrenador.contrasenia, 32, '\n');
            if(!validPass(entrenador.contrasenia)){
                cout << "La contraseña es inválida." << endl;
            } else {
                break;
            }
        } while(!validPass(entrenador.contrasenia));

        cout << endl;
        leer=fopen("Entrenadores.dat", "rb");
        fread(&entrenador2, sizeof(entrenadores), 1, leer);
        if(leer!=NULL){
            while(!feof(leer)){
                c++;
                fread(&entrenador2, sizeof(entrenadores), 1, leer);
            }
            entrenador.legajo=c;
        } else {
            entrenador.legajo=1;
        }
        fclose(leer);

        cout << "Registro exitoso." << endl;
        cout << "Legajo asignado: " << entrenador.legajo << endl;
        fwrite(&entrenador, sizeof(entrenadores), 1, fp);
        fclose(fp);
        Limpiar();
        break;
    default:
        cout << "La opción no existe." << endl;
        break;
    }
}

/**
 * Nombre: Limpiar()
 * Tipo: sin tipo.
 * @param -
 * Hace una pausa, y luego limpia la consola.
*/
void Limpiar(){
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
bool validPass(char contrasenia[32]){
    bool valid[2];
    valid[0]=false;
    valid[1]=false;
    valid[2]=false;
    char contrasenia2[32];
    strcpy(contrasenia2, contrasenia);
    
    //Valida que la contraseña tenga entre 6 y 32 caracteres.
    if(strlen(contrasenia)<6 || strlen(contrasenia)>32)return false;

    /*
    Valida que la contraseña tenga por lo menos 1 de los siguientes caracteres:
    -Letra mayúscula.
    -Letra minúscula.
    -Número.
    */
    for(int i=0; i<strlen(contrasenia); i++){
        //Validación del número.
        if(int(contrasenia[i])>=48 && int(contrasenia[i])<=57){
            valid[0]=true;
        }

        //Validación de la letra mayúscula.
        if(int(contrasenia[i])>=65 && int(contrasenia[i])<=90){
            valid[1]=true;
        }

        //Validación de la letra minúscula.
        if(int(contrasenia[i])>=97 && int(contrasenia[i])<=122){
            valid[2]=true;
        }
        //lamamalinda123
    }
    if(valid[0]==false || valid[1]==false || valid[2]==false){
        return false;
    }

    //Valida que la contraseña tenga un máximo de 3 números.
    for(int i=0,c=0;i<strlen(contrasenia);i++){
        if(int(contrasenia[i])>=48 && int(contrasenia[i])<=57){
            c++;
            if(c>3){
                return false;
            }
        } else {
            c=0;
        }
    }

    //Valida que la contraseña sea alfanumérica.
    for(int i=0; i<strlen(contrasenia); i++){
        if(!(
            (int(contrasenia[i])>=48 && int(contrasenia[i])<=57) || 
            isalpha(contrasenia[i])!=0
            ))
            return false;
    }

    /*
    Valida que la contraseña no contenga 2 letras
    alfabéticamente consecutivas.
    */
    strlwr(contrasenia2);
    for(int i=0,c=0;i<strlen(contrasenia2);i++){
        if(isalpha(contrasenia2[i])!=0){
            if((int(contrasenia2[i+1])-1)==int(contrasenia2[i])){
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
bool validUser(char user[10]){
    
    //Valida que la primera letra del usuario sea minúscula.
    if(!(int(user[0])>=97 && int(user[0])<=122))return false;

    //Valida que el nombre de usuario tenga entre 6 y 10 caracteres.
    if(strlen(user)<6 || strlen(user)>10)return false;

    //Valida que el nombre de usuario NO tenga más de 3 números.
    for(int i=0,c=0;i<strlen(user);i++){
        if(int(user[i])>=48 && int(user[i])<=57){
            c++;
        }

        if(c==4){
            return false;
        }
    }
    
    /* 
    Valida que el nombre solo esté conformado
    por caracteres alfanuméricos y el siguiente
    conjunto numérico: + - / * ? ¿ ! ¡
    */
    for(int i=0; i<strlen(user); i++){
        if(
            !(int(user[i])>=97 && int(user[i])<=122) && 
            !(int(user[i])>=65 && int(user[i])<=90) &&
            !(int(user[i])>=48 && int(user[i])<=57) &&
            !(int(user[i])==43 || int(user[i])==45 || int(user[i])==47 || int(user[i])==42 || int(user[i])==63 || int(user[i])==168 || int(user[i])==173 || int(user[i])==33))return false;
    }

    //Verifica que el usuario contenga mínimo 2 mayúsculas.
    for(int i=0, c=0; i<strlen(user); i++){
        if(int(user[i])>=65 && int(user[i])<=90){
            c++;
        }

        if(i==strlen(user)-1 && c<2){
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
bool validName(char name[60]){

    //Permite únicamente el ingreso de caracteres alfabéticos.
    for(int i=0; i<strlen(name);i++){
        if(isalpha(name[i])==0 && int(name[i])!=32){
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
bool repetition(FILE *fp, char user[10], struct usuarios usuario){
    fp=fopen("Usuarios.dat", "rb");

    fread(&usuario, sizeof(usuarios), 1, fp);
    while(!feof(fp)){
        if(strcmp(user,usuario.usuario)==0){
            return false;
        }
        fread(&usuario, sizeof(usuarios), 1, fp);
    }
    fclose(fp);

    return true;
}