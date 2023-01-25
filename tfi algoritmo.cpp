<<<<<<< HEAD
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>  
 using namespace std;
 
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
 	char indmed[60];
 	int edad;
 	int tel;
 	
 };
 
 void registrar(FILE *arch, socios soc, fechapago pago );
 void listado(FILE *arch, socios soc);
 void fechadepago(FILE *arch, fechapago pago, socios soc);
 int maximo(socios soc);
 
 main(){
 	FILE *arch;
 	arch= fopen("Socios.dat","a+b");
 	int respuesta;
 	fecha fechas;
 	socios soc;
 	fechapago pago;

 
 	
 	do{
 			cout<<"Bienvenido a Recepcion"<<endl
 	<<"1. Iniciar Sesion."<<endl
 	<<"2. Registrar socios."<<endl
 	<<"3. Registrar actividades de socios. "<<endl
 	<<"4. Listado de socios."<<endl
 	<<"5. Listado de fechas de pagos."<<endl
 	<<"6. Cerrar la aplicacion."<<endl<<endl
 	<<"ingresar opcion: "; cin>>respuesta;
 		switch(respuesta)
 		{
 			case 1: 
 				
 				break;
 			case 2:
 				registrar(arch ,soc, pago);
 				break;
 			case 4:
 				listado(arch, soc);
 				break;
 			case 5: 
			    fechadepago(arch, pago, soc);
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
 	int c;
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
 	
/* 		while(soc.fechas.mes==2){
		 	
	    	 while(soc.fechas.dia>28 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	     
			}		
			
			break;
	           
		}	
	
		 while(soc.fechas.mes== 1,3,5,7,8,10,12){
		 	
	    	 while(soc.fechas.dia>31 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
			
			}
			break;	
		}
		
		 while(soc.fechas.mes== 4,6,9,11){
		 	
	    	 while(soc.fechas.dia>30 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	     		
			}		
			break;	         
		}

	

		while(soc.fechas.mes<12){
		cout<< "fecha incorrecta, vuelva a ingresar el mes: "; cin>>soc.fechas.mes;
			break;
		}   */
 		if(soc.fechas.mes== 1,3,5,7,8,10,12){
 			 while(soc.fechas.dia>31 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
		
			}
 		}
 		else{
 			while(soc.fechas.dia>30 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	     		
			}		
 		}


	cout<<"año: " ; cin>>soc.fechas.anio;
	cout<<"ingrese la altura: ";cin>>soc.altura;
	cout<<"peso: "; cin>>soc.peso;
	cout<<"ingrese fecha de inicio: ";
	cout<<"dia: "; cin>>soc.pago.dia;
 	cout<<"mes: ";cin>>soc.pago.mes;
	cout<<"año: " ; cin>>soc.pago.anio;
	fflush(stdin); 
	cout<<"especificaciones medicas: " ; cin.getline(soc.indmed,60,'\n');
	cout<<"edad: " ; cin>>soc.edad;
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
 
 }

 
 
 void listado(FILE *arch, socios soc){
	
 	arch= fopen("Socios.dat","a+b");
 	fread(&soc, sizeof(socios),1,arch);
 	 while (!feof(arch))
 {
 cout<<"nombre: ";
 puts(soc.apnom);
 cout<<"domicilio: ";
 puts(soc.dom);
 cout<<"DNI: "<<soc.dni<<endl;
 cout<<soc.fechas.dia<<"/"<<soc.fechas.mes<<"/"<<soc.fechas.anio<<endl;
 cout<<soc.altura<<endl;
 cout<<"peso: "<<soc.peso<<endl;
 cout<<"numero de socio: "<<soc.numsocio<<endl;
 cout<<"ind medicas: "<<soc.indmed<<endl;
 cout<<"edad: " <<soc.edad<<endl;
 cout<<"telefono: " <<soc.tel<<endl<<endl;
 fread(&soc,sizeof(socios),1,arch);
 }
 fclose(arch);
 }
 
 
 
 void fechadepago(FILE *arch, fechapago pago, socios soc){
 	int numero=0;
 	
 	arch= fopen("Socios.dat","a+b");
 	
 	
 	cout<<"ingrese numero de socio: "; cin>> numero;
 	fread(&soc, sizeof(socios),1,arch);
 	while(!feof(arch)){ 
 		if(numero==soc.numsocio){
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
 
 	fclose(arch);
 	
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





=======
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>  
 using namespace std;
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
 	char indmed[60];
 	int edad;
 	int tel;
 	
 };
 
 void registrar(FILE *arch, socios soc, fechapago pago );
 void listado(FILE *arch, socios soc);
 void fechadepago(FILE *arch, fechapago pago, socios soc);
 int maximo(socios soc);
 
 main(){
 	FILE *arch;
 	arch= fopen("Socios.dat","a+b");
 	int respuesta;
 	fecha fechas;
 	socios soc;
 	fechapago pago;

 
 	
 	do{
 			cout<<"Bienvenido a Recepcion"<<endl
 	<<"1. Iniciar Sesion."<<endl
 	<<"2. Registrar socios."<<endl
 	<<"3. Registrar actividades de socios. "<<endl
 	<<"4. Listado de socios."<<endl
 	<<"5. Listado de fechas de pagos."<<endl
 	<<"6. Cerrar la aplicacion."<<endl<<endl
 	<<"ingresar opcion: "; cin>>respuesta;
 		switch(respuesta)
 		{
 			case 1: 
 				
 				break;
 			case 2:
 				registrar(arch ,soc, pago);
 				break;
 			case 4:
 				listado(arch, soc);
 				break;
 			case 5: 
			    fechadepago(arch, pago, soc);
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
 	int c;
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
 	
/* 		while(soc.fechas.mes==2){
		 	
	    	 while(soc.fechas.dia>28 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	     
			}		
			
			break;
	           
		}	
	
		 while(soc.fechas.mes== 1,3,5,7,8,10,12){
		 	
	    	 while(soc.fechas.dia>31 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
			
			}
			break;	
		}
		
		 while(soc.fechas.mes== 4,6,9,11){
		 	
	    	 while(soc.fechas.dia>30 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	     		
			}		
			break;	         
		}

	

		while(soc.fechas.mes<12){
		cout<< "fecha incorrecta, vuelva a ingresar el mes: "; cin>>soc.fechas.mes;
			break;
		}   */
 		if(soc.fechas.mes== 1,3,5,7,8,10,12){
 			 while(soc.fechas.dia>31 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
		
			}
 		}
 		else{
 			while(soc.fechas.dia>30 || soc.fechas.dia<1)
			 {
	 
	     	cout<< "fecha incorrecta, vuelva a ingresar el dia: "; cin>>soc.fechas.dia;
	     		
			}		
 		}


	cout<<"año: " ; cin>>soc.fechas.anio;
	cout<<"ingrese la altura: ";cin>>soc.altura;
	cout<<"peso: "; cin>>soc.peso;
	cout<<"ingrese fecha de inicio: ";
	cout<<"dia: "; cin>>soc.pago.dia;
 	cout<<"mes: ";cin>>soc.pago.mes;
	cout<<"año: " ; cin>>soc.pago.anio;
	fflush(stdin); 
	cout<<"especificaciones medicas: " ; cin.getline(soc.indmed,60,'\n');
	cout<<"edad: " ; cin>>soc.edad;
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
 
 }

 
 
 void listado(FILE *arch, socios soc){
	
 	arch= fopen("Socios.dat","a+b");
 	fread(&soc, sizeof(socios),1,arch);
 	 while (!feof(arch))
 {
 cout<<"nombre: ";
 puts(soc.apnom);
 cout<<"domicilio: ";
 puts(soc.dom);
 cout<<"DNI: "<<soc.dni<<endl;
 cout<<soc.fechas.dia<<"/"<<soc.fechas.mes<<"/"<<soc.fechas.anio<<endl;
 cout<<soc.altura<<endl;
 cout<<"peso: "<<soc.peso<<endl;
 cout<<"numero de socio: "<<soc.numsocio<<endl;
 cout<<"ind medicas: "<<soc.indmed<<endl;
 cout<<"edad: " <<soc.edad<<endl;
 cout<<"telefono: " <<soc.tel<<endl<<endl;
 fread(&soc,sizeof(socios),1,arch);
 }
 fclose(arch);
 }
 
 
 
 void fechadepago(FILE *arch, fechapago pago, socios soc){
 	int numero=0;
 	
 	arch= fopen("Socios.dat","a+b");
 	
 	
 	cout<<"ingrese numero de socio: "; cin>> numero;
 	fread(&soc, sizeof(socios),1,arch);
 	while(!feof(arch)){ 
 		if(numero==soc.numsocio){
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
 
 	fclose(arch);
 	
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





>>>>>>> f0f789f0374c9ee3325b70c0985cd4a4b0661493
