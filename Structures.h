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