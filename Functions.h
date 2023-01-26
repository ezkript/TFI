bool repetition(FILE* fp, char user[100], struct usuarios usuario);
void registrar(FILE* fp, FILE* leer, struct entrenadores entrenador, struct usuarios usuario);
void login(FILE* fp, struct entrenadores& entrenador, struct usuarios& usuario, int respuesta);
void listar(FILE* fp, struct entrenadores entrenador, struct usuarios usuario, struct Actividades actividad);
void Limpiar();
usuarios registrarAdmin(FILE* fp, struct usuarios usuario);
void registrarActividad(FILE* fp, Actividades actividad);
void calcularPago(entrenadores entrenador);