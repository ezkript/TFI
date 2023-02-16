#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>  
#include <string.h>
#include <conio.h>
#include <limits>

 using namespace std;
 
 typedef char indmed [60];

 
 /*cambio*/
 
 struct fechapago{
 	int dia;
 	int mes;
 	int anio;
 };
 
 struct socios{
 	char apnom [60];
 	char dom[60];
 	int dni;
 	fechapago fechas;
 	float altura;
 	float peso;
 	int numsocio;
 	fechapago pago;
    indmed indicaciones[10];
 	int tel;
 	
 	
 };

 struct usuarios {
    char usuario[100];
    char contrasenia[32];
    char apYNom[60];
    int tipo;
};

 struct registraractividad{
 	char act[100];
 	char nombresocio[60];
    char nombreEntrenador[100];
 };
 
struct Actividades {
    char NombreAct[100];
    char Horario[50];
    char entrenadorEncargado[100];
};
 
 


 
 void registrar(FILE *arch, socios soc, fechapago pago );
 void listado(FILE *arch, socios soc);
 void fechadepago(FILE *arch, fechapago pago, socios soc);
 int maximo(socios soc);
 void login(FILE* fp, usuarios& usuario);
 void listar(FILE* arch,FILE*Socios, Actividades actividad,registraractividad regis);
 void mostrar(FILE *Socios, registraractividad regis);
 bool canDo(char Actividad[100], indmed indicaciones[10]);
 bool validName(char name[60]);
 bool validDate(fechapago fecha);
 bool validIntDataType(int &value, int replace);
 bool validFloatDataType(float &value, float replace);

 main(){
 	FILE *arch=nullptr;
 	FILE *Socios;
 	arch= fopen("Socios.dat","a+b");
 	int respuesta;
 	fechapago fechas;
	usuarios usuario;
 	socios soc;
 	fechapago pago;
 	Actividades actividad;
 	registraractividad regis;

 
 	
 	do{
		cout<<endl;
		cout<<"\tBienvenid@ "<< (strlen(usuario.apYNom) < 1 ? "invitado" : usuario.apYNom) <<endl
		<< "----------------------------------" << endl
		<<(strlen(usuario.apYNom) < 1 ? " 1. Iniciar sesion.":" 1. Cambiar de cuenta.")<<endl
		<<" 2. Registrar socios."<<endl
		<<" 3. Registrar actividades de socios. "<<endl
		<<" 4. Listado de socios."<<endl
		<<" 5. Listado de fechas de pagos."<<endl
		<<" 6. Cerrar la aplicacion."<<endl
		<< "----------------------------------" << endl
		<<" Ingresar opcion: "; 
		cin>>respuesta;
		validIntDataType(respuesta, 0);
		cout<<endl;
 	
 		switch(respuesta)
 		{
 			case 1: 
				fclose(arch);
 				login(arch, usuario);
 				break;
 			case 2:
 				if(usuario.tipo==1 || usuario.tipo==2){
 				
 				registrar(arch ,soc, pago);
 				}
				else{
					cout<<"No hay ninguna sesion activa. "<<endl;
					system("PAUSE");
					system("CLS");
				}
 				break;
 			case 3:
 				if(usuario.tipo==1 || usuario.tipo==2){
 					
 				listar(arch,Socios,actividad,regis);
 				}
 				else{
 					cout<<"No hay ninguna sesion activa. "<<endl;	
					system("PAUSE");
					system("CLS");
 				}
 				break;
 			case 4:
 				if(usuario.tipo==1 || usuario.tipo==2){
 					listado(arch, soc);
 					system("PAUSE");
 					system("CLS");
 				}
 				else{
 					cout<<"No hay ninguna sesion activa. "<<endl;
					system("PAUSE");
					system("CLS");
 				}
 				break;
 			case 5: 
 				if(usuario.tipo==1 || usuario.tipo==2){
			  		fechadepago(arch, pago, soc);
				}
				else{
					cout<<"No hay ninguna sesion activa. "<<endl;
					system("PAUSE");
					system("CLS");
				}
				 break; 
 			case 6:
				break;
 			default: 
 				cout << "La opcion no existe." << endl;
 				system("PAUSE");
 				system("CLS");
			    break;	
 			
 		}
 	}while(respuesta!=6);
 	
 	
 	return 0;
 }

 void registrar(FILE *arch, socios soc, fechapago pago){
 	struct socios soc2;
	FILE *leer;
 	arch= fopen("Socios.dat","a+b");
 	int c=0;
 	int cont=0;
 	int respuesta;
 	
 	do {
 		fflush(stdin); 
 		cout<<"ingrese apellido y nombre: ";
		cin.getline(soc.apnom,60,'\n');
 		
 		if(!validName(soc.apnom)){
 			cout << "El nombre ingresado no es valido." << endl;
		}
 		
	} while(!validName(soc.apnom));
	
	fflush(stdin); 
 	cout<<"ingrese el domicilio: ";cin.getline(soc.dom,60,'\n');
 	do {
 		cout<<"ingrese dni: "; 
		cin>>soc.dni;	
		if(cin.fail()){
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	soc.dni=-1;
        	cout << "El DNI ingresado es incorrecto." << endl;
    	}
	} while(soc.dni==-1);
 	
	cout<<"Ingrese fecha de nacimiento: "<<endl;
	
 	do {
 		cout<<"Dia: "; cin>>soc.fechas.dia;
 		validIntDataType(soc.fechas.dia, -1);
 		cout<<"Mes: ";cin>>soc.fechas.mes;
 		validIntDataType(soc.fechas.mes, -1);
		cout<<"Anio: " ; cin>>soc.fechas.anio;
		validIntDataType(soc.fechas.anio, 1800);
		if(!validDate(soc.fechas)){
			cout << "Fecha invalida." << endl;
		}	
	}while(!validDate(soc.fechas));
	
	do {
		cout<<"Ingrese la altura: ";
		cin>>soc.altura;
		if(!validFloatDataType(soc.altura,0)){
			cout << "La altura es invalida." << endl;
		}
	} while(!validFloatDataType(soc.altura, 0));
	
	do {
		cout<<"Peso: "; 
		cin>>soc.peso;
		if(!validFloatDataType(soc.peso,0)){
			cout << "El peso es invalido." << endl;
		}	
	} while(!validFloatDataType(soc.peso, 0));
	
	
	cout<<"ingrese fecha de inicio: "<<endl;
	do {
		cout<<"dia: "; cin>>soc.pago.dia;
		validIntDataType(soc.pago.dia, -1);
		cout<<"mes: "; cin>>soc.pago.mes;
		validIntDataType(soc.pago.mes, -1);
		cout<<"anio: " ; cin>>soc.pago.anio;
		validIntDataType(soc.pago.anio, 1800);
		if(!validDate(soc.pago)){
			cout << "Fecha invalida." << endl;
		}	
	} while(!validDate(soc.pago));
	
	cout<<"Especificaciones medicas(maximo permitido: 5)\nEn caso de no tener especificaciones dejar en blanco." << endl;
	do{
		cout << "Actividad no permitida: "; 
		fflush(stdin);
		cin.getline(soc.indicaciones[cont],10,'\n');
		cont++;
		cout<<"Cargar otra indicacion?\n1 = No.\n2 = Si.\nRespuesta: "; cin>>respuesta;
	}while(respuesta==2 || c>=5);
	for(int i=cont; i<10; i++){
		strcpy(soc.indicaciones[i],".");
	}
	cout<< "telefono: " ; cin>>soc.tel;
 	
 	
	leer= fopen ("Socios.dat", "a+b");
	fread(&soc2, sizeof(socios), 1, leer);
	if(leer!=NULL){
		while(!feof(leer)){
			c++;
			fread(&soc2, sizeof(socios), 1, leer);
		}
		soc.numsocio=c;
	}
	else {
		soc.numsocio=1;
	}
	fclose(leer);
 
 	fwrite(&soc,sizeof(socios),1,arch);
 	fclose(arch);
 	
 	system("pause");
    system("cls");
 
 }

 
 
 void listado(FILE *arch, socios soc){
	
 	arch= fopen("Socios.dat","a+b");
 	fread(&soc, sizeof(socios),1,arch);
 	cout << "\tListado de socios" << endl 
 	<< "-------------------------------------------" << endl;
 	while (!feof(arch)){
        cout<<"Nombre: ";
        puts(soc.apnom);
        cout<<"Nomicilio: ";
        puts(soc.dom);
        cout<<"DNI: "<<soc.dni<<endl;
        cout<<"Fecha de nacimiento: " << soc.fechas.dia<<"/"<<soc.fechas.mes<<"/"<<soc.fechas.anio<<endl;
        cout<<"Altura: " << soc.altura<<endl;
        cout<<"Peso: "<<soc.peso<<endl;
        cout<<"Numero de socio: "<<soc.numsocio<<endl;
		cout<<"Ind. medicas: ";
        for(int i=0; i<10; i++){
			if(strcmp(soc.indicaciones[i], ".")!=0){
				cout << soc.indicaciones[i] << ", ";
			}
		}
		cout << endl;
        cout<<"Edad: " <<2023-soc.fechas.anio<<endl;
        cout<<"Altura: "<<soc.altura<<endl;
        cout<<"Telefono: " <<soc.tel<<endl;
        cout<<"Fecha de inicio: "<<soc.pago.dia<<" / "<<soc.pago.mes<<" / "<<soc.pago.anio<<endl <<endl;
        fread(&soc,sizeof(socios),1,arch);
    }
    fclose(arch);
    cout << "-------------------------------------------" << endl;
 }
 
 void fechadepago(FILE *arch, fechapago pago, socios soc){
 	bool band=false;
 	int numero=0;
 	
 	arch= fopen("Socios.dat","a+b");
 	
 	
 	cout<<"ingrese numero de socio: "; cin>> numero;
 	fread(&soc, sizeof(socios),1,arch);
 	
 	
 	while(!feof(arch)){ 
 	
 		 if(numero==soc.numsocio){
 		 	band=true;
 			if(soc.pago.mes>=12){
				soc.pago.anio++;
				soc.pago.mes=1;
				cout<<"su proxima fecha de pago es: "<<maximo(soc)<<" / "<<soc.pago.mes<<" / "<<soc.pago.anio<<endl;
			} else {
				cout<<"su proxima fecha de pago es: "<<maximo(soc)<<" / "<<soc.pago.mes+1<<" / "<<soc.pago.anio<<endl;
			}
			break;
			
 		}
 		  fread(&soc, sizeof(socios),1,arch);
 		}
	 	
	 	if(band==false){
	 		cout<<"el numero de socio ingresado no existe."<<endl;
	 	}
 	
 
 	fclose(arch);
 	system("pause");
    system("cls");
 	
 }

int maximo(socios soc){
 	int valor[12]={31,28,31,30,31,30,31,31,30,31,30,31};
 	int mes=soc.pago.mes-1;
 	int maximo=0;
 	
 	if(valor[mes]==soc.pago.dia){
 		if(valor[mes+1]<valor[mes]){
			maximo=valor[mes+1]; 		
 		} else {
 			maximo=soc.pago.dia;
 		}	
 	} else {
 		maximo=soc.pago.dia;
 	}
 	
	return maximo;
}


void login(FILE* fp, struct usuarios& usuario) {
    int legajo;
    bool sesion;
    char nombreUsuario[100],
        contrasenia[32];
		
    fp = fopen("Usuarios.dat", "rb");
 	cout << "Ingresar nombre de usuario: ";
    fflush(stdin);
    cin.getline(nombreUsuario, 100, '\n');
    cout << "Ingresar contrasenia: ";
    fflush(stdin);
    cin.getline(contrasenia, 32, '\n');
	if(fp!=NULL){
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
	} else {
		cout << "No hay usuarios registrados." << endl;
	}
    system("pause");
    system("cls");
}

void listar(FILE* arch,FILE *Socios ,Actividades actividad, registraractividad regis){
	fclose(arch);
 	FILE * fp = fopen("Socios.dat", "rb");
	Socios=fopen("Turnos.dat", "a+b");
	socios socio;
	bool flag=false;
	bool flag2=false;

	do{
		cout<< "Nombre del socio: "; 
		fflush(stdin);
		cin.getline(regis.nombresocio,60, '\n');
        rewind(fp);
		fread(&socio, sizeof(socios), 1, fp);
		while(!feof(fp)){
			if(strcmp(regis.nombresocio, socio.apnom)==0){
				flag=true;
				break;
			}
			fread(&socio, sizeof(socios), 1, fp);
		}	
		if (!flag) {
			cout<< "No se encontro el socio." << endl; 
		}
    } while(!flag);
	fclose(fp);

	cout << "ACTIVIDADES" << endl
        << "----------------------------------------------" << endl;
	
	fp=fopen("Actividades.dat", "rb");
	if(fp!=NULL){
		fread(&actividad, sizeof(Actividades),1, fp);
		while(!feof(fp)){
			if(canDo(actividad.NombreAct, socio.indicaciones)){
				cout << "Actividad: " << actividad.NombreAct << endl
				<< "Horario: " << actividad.Horario << endl
				<< "Entrenador: " << actividad.entrenadorEncargado << endl << endl;
			}
			fread(&actividad, sizeof(Actividades),1, fp);
		}

		flag=false;
		do{
			cout<< endl <<"Ingrese el nombre de la actividad a realizar: "; 
			fflush(stdin);
			cin.getline(regis.act, 100, '\n');
			// strlwr(regis.act);
			// strlwr(actividad.NombreAct);
			if(canDo(regis.act,socio.indicaciones)){
				rewind(fp);
				fread(&actividad, sizeof(Actividades), 1, fp);
				while(!feof(fp)){
					if(strcmp(actividad.NombreAct, regis.act)==0){
						strcpy(regis.nombreEntrenador,actividad.entrenadorEncargado);
						flag=true;
						break;
					}
					fread(&actividad, sizeof(Actividades), 1, fp);
				}
				if(!flag){
					cout << "La actividad no fue encontrada." << endl;
				} 
			} else {
				cout << "El socio no puede realizar esta actividad." << endl;
			}
		} while (!flag);
				
		fwrite(&regis, sizeof(registraractividad),1, Socios);
		fclose(Socios);
	} else {
		cout << "Error al abrir el archivo." << endl;
	}
	fclose(fp);
}


bool canDo(char Actividad[100], indmed indicaciones[10]){

	for(int i=0; i<10;i++){
		if(strcmp(Actividad, indicaciones[i])==0){
			return false;
		}
	}
	return true;
}
	
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

bool validDate(fechapago fecha){
	int valor[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(fecha.mes>12 || fecha.mes<1){
		return false;
	}
	if(fecha.anio<1900){
		return false;
	}
	for(int i=0; i<12; i++){
		if(valor[fecha.mes-1]<fecha.dia || fecha.dia <1){
			return false;
		}
	}
	return true;
}

bool validIntDataType(int &value, int replace){
	if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        value=replace;
        return false;
    }
    return true;
}

bool validFloatDataType(float &value, float replace){
	if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        value=replace;
        return false;
    }
    return true;
}
