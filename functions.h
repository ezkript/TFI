#include "structures.h"

void registrar();
bool login(int);
void listar();
bool validPass(char contrasenia[32]);
bool validUser(char user[10]);
bool validName(char name[60]);
bool repetition(FILE *fp, char user[10], struct usuarios usuario);
void Limpiar();