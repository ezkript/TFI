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
