#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>  
#include <string.h>
#include<conio.h>

 using namespace std;
 
 typedef char indmed [60];

 
 /*cambio*/
 
 struct fechapago{
 	int dia;
 	int mes;
 	int anio;
 };
 struct fecha{
 	int dia;
 	int mes;
 	int anio;
 };
 struct socios{
 	char apnom [60];
 	char dom[60];
 	int dni;
 	fecha fechas;
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
 void login(FILE* fp, struct usuarios& usuario);
 void listar(FILE* arch,FILE*Socios, struct Actividades actividad,registraractividad regis);
 void mostrar(FILE *Socios, registraractividad regis);
bool canDo(char Actividad[100], indmed indicaciones[10]);

 main(){
 	FILE *arch;
 	FILE *Socios;
 	arch= fopen("Socios.dat","a+b");
 	int respuesta;
 	fecha fechas;
	usuarios usuario;
 	socios soc;
 	fechapago pago;
 	Actividades actividad;
 	registraractividad regis;

 
 	
 	do{
 	cout<<endl;
 			cout<<"Bienvenido a Recepcion"<<endl
 	<<"1. Iniciar Sesion."<<endl
 	<<"2. Registrar socios."<<endl
 	<<"3. Registrar actividades de socios. "<<endl
 	<<"4. Listado de socios."<<endl
 	<<"5. Listado de fechas de pagos."<<endl
 	<<"6. Cerrar la aplicacion."<<endl<<endl
 	<<"ingresar opcion: "; cin>>respuesta;
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
 			
 			default: 
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
 	fflush(stdin); 
 	cout<<"ingrese apellido y nombre: ";cin.getline(soc.apnom,60,'\n');
 	fflush(stdin); 
 	cout<<"ingrese el domicilio: ";cin.getline(soc.dom,60,'\n');
 	cout<<"ingrese dni: "; cin>>soc.dni;
 	cout<<"ingrese fecha de nacimiento: "<<endl;
 	cout<<"dia: "; cin>>soc.fechas.dia;
 	
	 while(soc.fechas.dia>31 || soc.fechas.dia<1){
	 
	 cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	 
}
	
 	cout<<"mes: ";cin>>soc.fechas.mes;
 	
 	while(soc.fechas.mes>12 || soc.fechas.mes<1){
	 
	 cout<< "fecha incorrecta, vuelva a ingresar el mes: "; cin>>soc.fechas.mes;
}

 		if(soc.fechas.mes== 1,3,5,7,8,10,12){
 			 while(soc.fechas.dia>31 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
		
			}
 		}
 		else{
 			while((soc.fechas.mes==2 && soc.fechas.dia==30) || soc.fechas.dia>30 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	     		
			}		
 		}


	cout<<"anio: " ; cin>>soc.fechas.anio;
	cout<<"ingrese la altura: ";cin>>soc.altura;
	cout<<"peso: "; cin>>soc.peso;
	cout<<"ingrese fecha de inicio: "<<endl;
	cout<<"dia: "; cin>>soc.pago.dia;
	
		 while(soc.pago.dia>31 || soc.pago.dia<1){
	 		cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.pago.dia;	 
		}
	cout<<"mes: ";cin>>soc.pago.mes;
	 	 while(soc.pago.mes>12 || soc.pago.mes<1){
	        cout<< "fecha incorrecta, vuelva a ingresar el mes: "; cin>>soc.pago.mes;
}
	
	cout<<"anio: " ; 
	cin>>soc.pago.anio;
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
 	while (!feof(arch)){
        cout<<"nombre: ";
        puts(soc.apnom);
        cout<<"domicilio: ";
        puts(soc.dom);
        cout<<"DNI: "<<soc.dni<<endl;
        cout<<"Fecha de nacimiento: " << soc.fechas.dia<<"/"<<soc.fechas.mes<<"/"<<soc.fechas.anio<<endl;
        cout<<"Altura: " << soc.altura<<endl;
        cout<<"peso: "<<soc.peso<<endl;
        cout<<"numero de socio: "<<soc.numsocio<<endl;
		cout<<"ind medicas: ";
        for(int i=0; i<10; i++){
			if(strcmp(soc.indicaciones[i], ".")!=0){
				cout << soc.indicaciones[i] << ", ";
			}
		}
		cout << endl;
        cout<<"edad: " <<2023-soc.fechas.anio<<endl;
        cout<<"altura: "<<soc.altura<<endl;
        cout<<"telefono: " <<soc.tel<<endl;
        cout<<"fecha de inicio: "<<soc.pago.dia<<" / "<<soc.pago.mes<<" / "<<soc.pago.anio<<endl <<endl;
        fread(&soc,sizeof(socios),1,arch);
    }
    fclose(arch);
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
			usuario={};
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
	


