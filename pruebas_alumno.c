#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "testing.h"
#include "abb.h"

#define LARGO_CLAVE 10
#define FIN_STRING '\0'

int strcmp_wrapper(const void* clave1, const void* clave2){
    return strcmp((const char*)clave1, (const char*)clave2);
}

void crear_array_para_insertar_ordenado(char** claves, int* index, int maximo, int minimo){
    if(maximo == 0 || maximo <= minimo) return;
    claves[*index] = malloc(sizeof(char)*LARGO_CLAVE);

    int medio = (maximo+minimo)/2;

    if(medio>= 1000)
        sprintf( claves[*index], "%d%c", medio, FIN_STRING);
    else if(medio >= 100)
        sprintf( claves[*index], "0%d%c", medio, FIN_STRING);
    else if(medio >= 10)
        sprintf( claves[*index], "00%d%c", medio, FIN_STRING);
    else
        sprintf( claves[*index], "000%d%c", medio, FIN_STRING);
    (*index)++;
    crear_array_para_insertar_ordenado(claves, index, medio, minimo );
    crear_array_para_insertar_ordenado(claves, index, maximo, medio+1);

}

void pruebas_crear_abb_vacio(void){
	abb_t* arbol = abb_crear(strcmp_wrapper, NULL, 0);

    print_test("Prueba abb crear abb vacio", arbol);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(arbol, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(arbol, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(arbol, "A"));

    abb_destruir(arbol);
}

void pruebas_abb_instertar(void){

	abb_t* arbol = abb_crear(strcmp_wrapper, NULL, 0);

	char* clave1 = "0050", *clave2 = "0025", *clave3 = "0100",
	*clave4 = "0000", *clave5 = "0035", *clave6 = "0075", *clave7 = "0125";
	char* dato1 = "Hello World!";
	int dato2 = 2048;
	long dato3 = 49102321;

	print_test("Prueba abb insertar clave1, con dato1", abb_guardar(arbol, clave1, dato1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave1 es dato1", !strcmp_wrapper(abb_obtener(arbol, clave1), dato1));
    print_test("Prueba abb obtener clave1 es dato1", !strcmp_wrapper(abb_obtener(arbol, clave1), dato1));
    print_test("Prueba abb clave1 pertenece, es true", abb_pertenece(arbol, clave1));
    print_test("Prueba abb insertar clave2, con dato2", abb_guardar(arbol, clave2, &dato2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 2);
    print_test("Prueba abb insertar clave3, con dato3", abb_guardar(arbol, clave3, &dato3));
    print_test("Prueba abb cantidad de elementos es 3", abb_cantidad(arbol) == 3);
    print_test("Prueba abb obtener clave3 es dato3", abb_obtener(arbol, clave3) == &dato3);
 	print_test("Prueba abb obtener clave2 es dato2", abb_obtener(arbol, clave3) == &dato3);
    print_test("Prueba abb clave2 pertenece", abb_pertenece(arbol, clave2));
    print_test("Prueba abb clave3 pertenece", abb_pertenece(arbol, clave3));
    print_test("Prueba abb borrar clave2, es dato2", abb_borrar(arbol, clave2) == &dato2);
    print_test("Prueba abb borrar clave2, es NULL", abb_borrar(arbol, clave2) == NULL );
    print_test("Prueba abb insertar clave2, con dato2", abb_guardar(arbol, clave2, &dato2));
    print_test("Prueba abb clave1 pertenece", abb_pertenece(arbol, clave1));

    print_test("Prueba abb insertar clave4, dato NULL", abb_guardar(arbol, clave4, NULL));
    print_test("Prueba abb insertar clave5, dato NULL", abb_guardar(arbol, clave5, NULL));
    print_test("Prueba abb insertar clave6, dato NULL", abb_guardar(arbol, clave6, NULL));
    print_test("Prueba abb insertar clave7, dato NULL", abb_guardar(arbol, clave7, NULL));
    print_test("Prueba abb cantidad es 7", abb_cantidad(arbol) == 7);
    printf("El arbol debería ser:\n\t    clave1\n\tclave2 | clave3\nclave4\tclave5 | clave6\tclave7\n");
    print_test("Prueba abb borrar una hoja, clave4", abb_borrar(arbol, clave4) == NULL);
    print_test("Prueba abb cantidad es 6", abb_cantidad(arbol) == 6);
    print_test("Prueba abb borrar con un solo hijo a derecha, clave2", abb_borrar(arbol, clave2) == &dato2);
    print_test("Prueba abb cantidad es 5", abb_cantidad(arbol) == 5);
    print_test("Prueba abb clave2 no pertenece", !abb_pertenece(arbol, clave2));
    print_test("Prueba abb clave5 pertenece", abb_pertenece(arbol, clave5));
    print_test("Prueba abb borrar con 2 hijos, clave3", abb_borrar(arbol, clave3) == &dato3);
    print_test("Prueba abb cantidad es 4", abb_cantidad(arbol) == 4);
    print_test("Prueba abb clave3 no pertenece", !abb_pertenece(arbol, clave3));
    print_test("Prueba abb clave7 pertenece", abb_pertenece(arbol, clave7));
    print_test("Prueba abb clave6 pertenece", abb_pertenece(arbol, clave6));
    print_test("Prueba abb borrar con un hijo a izquierda, clave6", abb_borrar(arbol, clave6) == NULL);
    print_test("Prueba abb cantidad es 3", abb_cantidad(arbol) == 3);
    print_test("Prueba abb borrar clave3, no esta, es NULL", abb_borrar(arbol, clave3) == NULL);
    abb_destruir(arbol);
}

void pruebas_abb_reemplazar(){
	abb_t* abb = abb_crear(strcmp_wrapper,NULL, 0);

	char *clave1 = "animalito", *valor1a = "perrito",*valor1b = "gatito";
	char *clave2 = "periferico", *valor2a = "mouse",*valor2b = "teclado";

	print_test("Prueba abb insertar clave1",abb_guardar(abb,clave1,valor1a));
	print_test("Prueba abb obtener valor clave1 es valor1a",abb_obtener(abb,clave1)==valor1a);
	print_test("Prueba abb obtener valor clave1 es valor1a",abb_obtener(abb,clave1)==valor1a);
	print_test("Prueba abb insertar clave2",abb_guardar(abb,clave2,valor2a));
	print_test("Prueba abb obtener valor clave2 es valor2a",abb_obtener(abb,clave2)==valor2a);
	print_test("Prueba abb obtener valor clave2 es valor2a",abb_obtener(abb,clave2)==valor2a);
	print_test("La cantidad de elementos es 2",abb_cantidad(abb)==2);

	print_test("Insertar clave1 con otro valor",abb_guardar(abb,clave1,valor1b));
	print_test("Prueba abb obtener valor clave1 es valor1b",abb_obtener(abb,clave1)==valor1b);
	print_test("Prueba abb obtener valor clave1 es valor1b",abb_obtener(abb,clave1)==valor1b);
	print_test("Insertar clave2 con otro valor",abb_guardar(abb,clave2,valor2b));
	print_test("Prueba abb obtener valor clave2 es valor2b",abb_obtener(abb,clave2)==valor2b);
	print_test("Prueba abb obtener valor clave2 es valor2b",abb_obtener(abb,clave2)==valor2b);
	print_test("La cantidad de elementos es 2",abb_cantidad(abb)==2);
	abb_destruir(abb);
}

void pruebas_abb_reemplazar_destruir(){
	abb_t* abb = abb_crear(strcmp_wrapper,free, 0);

	char *clave1 = "animalito", *valor1a,*valor1b;
	char *clave2 = "periferico", *valor2a,*valor2b;

	valor1a = malloc(10*sizeof(char));
	valor1b = malloc(10*sizeof(char));
	valor2a = malloc(10*sizeof(char));
	valor2b = malloc(10*sizeof(char));

	print_test("Prueba abb insertar clave1",abb_guardar(abb,clave1,valor1a));
	print_test("Prueba abb obtener valor clave1 es valor1a",abb_obtener(abb,clave1)==valor1a);
	print_test("Prueba abb obtener valor clave1 es valor1a",abb_obtener(abb,clave1)==valor1a);
	print_test("Prueba abb insertar clave2",abb_guardar(abb,clave2,valor2a));
	print_test("Prueba abb obtener valor clave2 es valor2a",abb_obtener(abb,clave2)==valor2a);
	print_test("Prueba abb obtener valor clave2 es valor2a",abb_obtener(abb,clave2)==valor2a);
	print_test("La cantidad de elementos es 2",abb_cantidad(abb)==2);

	print_test("Insertar clave1 con otro valor",abb_guardar(abb,clave1,valor1b));
	print_test("Prueba abb obtener valor clave1 es valor1b",abb_obtener(abb,clave1)==valor1b);
	print_test("Prueba abb obtener valor clave1 es valor1b",abb_obtener(abb,clave1)==valor1b);
	print_test("Insertar clave2 con otro valor",abb_guardar(abb,clave2,valor2b));
	print_test("Prueba abb obtener valor clave2 es valor2a",abb_obtener(abb,clave2)==valor2b);

	abb_destruir(abb);

}

void pruebas_abb_clave_vacia(){
	abb_t* abb = abb_crear(strcmp_wrapper,NULL, 0);
	char *clave = "", *valor = "";

	print_test("Prueba abb insertar clave vacia",abb_guardar(abb,clave,valor));
	print_test("Prueba abb la cantidad de elementos es 1",abb_cantidad(abb)==1);
	print_test("Prueba abb obtener clave vacia es valor",abb_obtener(abb,clave)==valor);
	print_test("Prueba abb clave vacia pertenece es true",abb_pertenece(abb,clave));
	print_test("Prueba abb borrar clave vacia es valor",abb_borrar(abb,clave));
	print_test("Prueba abb la cantidad de elementos es 0",abb_cantidad(abb)==0);

	abb_destruir(abb);
}

bool comprobar_in_order(const void* clave,void* valor,void* extra){
	if(*(int*)valor>((int*)extra)[0]){
		((int*)extra)[1]++;
	}

	return true;
}

void pruebas_abb_iter_interno(size_t cantidad_iterar){
	abb_t* abb = abb_crear(strcmp_wrapper,NULL, 0);

	int arreglo[cantidad_iterar];

	size_t largo_clave = 10;
	char (*claves)[largo_clave] = malloc(cantidad_iterar*largo_clave);
	bool ok = true;

	for(int i=0;i<cantidad_iterar;i++){
		arreglo[i] = i;
		sprintf(claves[i], "%08d", i);
		ok &= abb_guardar(abb,claves[i],&arreglo[i]);
	}

	print_test("Prueba abb guardar varios elementos",ok);

	ok = true;

	int arreglo_test[2] = {0,0};//{Valor anterior, cantidad de veces que se mantuvo el orden};

	abb_in_order(abb,comprobar_in_order,arreglo_test);
	print_test("Prueba abb iterador interno mantiene in order",arreglo_test[1]==cantidad_iterar-1);

	abb_destruir(abb);
	free(claves);
}

void pruebas_abb_iterar_vacio(){
	abb_t* abb = abb_crear(strcmp_wrapper,NULL, 0);
	abb_iter_t* iterador = abb_iter_in_crear(abb);

	print_test("Prueba abb crear iterador sobre arbol vacio",iterador);
	print_test("Prueba abb iterador esta al final",abb_iter_in_al_final(iterador));
	print_test("Prueba abb iterador avanzar es false",!abb_iter_in_avanzar(iterador));
	print_test("Prueba abb iterador ver actual es NULL",!abb_iter_in_ver_actual(iterador));

	abb_iter_in_destruir(iterador);
	abb_destruir(abb);
}

int strncmp_wrapper(const void* str1, const void* str2){
    return strncmp((char*)str1, (char*)str2, 4);
}

void pruebas_abb_iterar_volumen(int cantidad){
	abb_t* abb = abb_crear(strncmp_wrapper,NULL, 5);

	char* claves[cantidad];

	int index = 0;

	crear_array_para_insertar_ordenado(claves,&index,cantidad,0);

	bool ok = true;

	for(int i=0;i<cantidad;i++){
		ok &= abb_guardar(abb,claves[i],NULL);
	}

	print_test("Prueba abb insertar muchos elementos",ok);
	abb_iter_t* iterador = abb_iter_in_crear(abb);

	print_test("Prueba abb crear iterador",iterador);
	print_test("Prueba abb iterador no al final",!abb_iter_in_al_final(iterador));

	ok = true;
	bool avanzar = true;

	for(int i=0;i<cantidad;i++){
		ok &= atoi(abb_iter_in_ver_actual(iterador))==i; //Comprobacion del in-order
		avanzar &= abb_iter_in_avanzar(iterador);
	}

	print_test("Prueba abb el recorrido in order es el correcto",abb);
	print_test("Prueba abb se pudo avanzar todas las posiciones",avanzar);
	print_test("El iterador esta al final",abb_iter_in_al_final(iterador));

	for(int i =0;i<cantidad;i++){
		free(claves[i]);
	}
	
	abb_iter_in_destruir(iterador);
	abb_destruir(abb);
}


void pruebas_abb_volumen(int volumen){

    char** claves = malloc(sizeof(char*)*volumen);
    int posicion = 0;
    crear_array_para_insertar_ordenado(claves, &posicion, volumen, 0);
    bool ok_guardar = true;
    
    abb_t* abb = abb_crear(strcmp_wrapper, free, 0);
    for(posicion = 0; posicion < volumen ; posicion++ ){
        ok_guardar &= abb_guardar(abb, claves[posicion], claves[posicion]);
    }
    print_test("Pruebas abb volumen, insertar muchos elementos", ok_guardar );

    bool ok_borrar = true;
    bool ok_pertenece = false;
    for(posicion = 13; posicion < volumen ; posicion+=7){
        ok_borrar &= (!strcmp_wrapper(abb_borrar(abb, claves[posicion]),claves[posicion]));
        ok_pertenece |= abb_pertenece(abb, claves[posicion]);
    }
    print_test("Pruebas abb volumen, borrar elementos al azar", ok_borrar );
    print_test("Pruebas abb volumen, claves borradas no pertenecen", !ok_pertenece );

    ok_pertenece = true;
    bool ok_obtener = true;
    for(posicion = 17; posicion+1 < volumen; posicion += 7){
        ok_pertenece &= abb_pertenece(abb, claves[posicion]);
        ok_obtener &= (!strcmp_wrapper(abb_obtener(abb, claves[posicion+1]), claves[posicion+1]));
    }
    print_test("Pruebas abb volumen, pertenecen claves no borradas", ok_pertenece );
    print_test("Pruebas abb volumen, obtener claves datos correctos", ok_obtener);

    for(posicion = 13; posicion < volumen; posicion += 7){
        ok_guardar &= abb_guardar(abb, claves[posicion], claves[posicion]);
    }
    print_test("Pruebas abb volumen, guardar elementos borrados", ok_guardar);

    abb_destruir(abb);
    free(claves);
}

void pruebas_iterar_basicas(void){

    abb_t* abb = abb_crear(strcmp_wrapper, NULL, 0);

    int datos[15];
    datos[0] = 0;
    char* claves[15];
    crear_array_para_insertar_ordenado(claves, datos, 15, 0);
    for( int i = 0; i < 15; i++){
        datos[i] = i;
        abb_guardar(abb, claves[i], &datos[i]);
    }

    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("Pruebas abb iter externo, no está al final", !abb_iter_in_al_final(iter));
    print_test("Pruebas abb iter externo, ver actual es correcto",strcmp_wrapper(abb_iter_in_ver_actual(iter),"0000")==0);
    print_test("Pruebas abb iter externo, se puede avanzar", abb_iter_in_avanzar(iter));

    bool ok_avanzar = true;
    bool ok_actual = true;
    for( int i = 1; i < 15; i++ ){
        char* clave_actual = (char*)abb_iter_in_ver_actual(iter);
        for(int j = 1; j < 15; j++){
            if(!strcmp_wrapper(clave_actual, claves[j]))
                ok_actual &= (*(int*)abb_obtener(abb, clave_actual) == datos[j]);
        }
        ok_avanzar &= abb_iter_in_avanzar(iter);
    }
    print_test("Pruebas abb iter externo, ver actual para varios elementos es correcto", ok_actual);
    print_test("Pruebas abb iter externo, se puede avanzar varias veces", ok_avanzar);
    print_test("Pruebas abb iter externo, está al final", abb_iter_in_al_final(iter));
    print_test("Pruebas abb iter externo, no se puede avanzar", !abb_iter_in_avanzar(iter));

    abb_iter_in_destruir(iter);

    abb_destruir(abb);
    for( int i = 0; i < 15; i++){
        free(claves[i]);
    }

}

int difftime_wrappeado(const void* tiempo1, const void* tiempo2){
    double diferencia = difftime( *(time_t*)tiempo1,*(time_t*)tiempo2);

    if(diferencia < 0){
        return -1;
    }else if(diferencia > 0){
        return 1;
    }
    return 0;
}

void pruebas_iterar_desde(void){
    struct tm fecha1_tm = {0};
    struct tm fecha2_tm = {0};
    struct tm fecha3_tm = {0};
    struct tm fecha4_tm = {0};
    struct tm fecha5_tm = {0};
    struct tm fecha6_tm = {0};

    fecha1_tm.tm_year = 100;
    fecha2_tm.tm_year = 50;
    fecha3_tm.tm_year = 150;
    fecha4_tm.tm_year = 75;
    fecha5_tm.tm_year = 125;
    fecha6_tm.tm_year = 40;

    time_t fecha1 = mktime(&fecha1_tm);
    time_t fecha2 = mktime(&fecha2_tm);
    time_t fecha3 = mktime(&fecha3_tm);
    time_t fecha4 = mktime(&fecha4_tm);
    time_t fecha5 = mktime(&fecha5_tm);
    time_t fecha6 = mktime(&fecha6_tm);

    abb_t* arbol = abb_crear(difftime_wrappeado,NULL,sizeof(time_t));
    bool ok = true;

    ok &= abb_guardar(arbol,&fecha1,NULL);
    ok &= abb_guardar(arbol,&fecha2,NULL);
    ok &= abb_guardar(arbol,&fecha3,NULL);
    ok &= abb_guardar(arbol,&fecha4,NULL);
    ok &= abb_guardar(arbol,&fecha5,NULL);

    print_test("Prcrear_desdeueba abb insertar varios time_t",ok);
    abb_iter_t* iterador = abb_iter_in_crear_desde(arbol,&fecha6);

    print_test("Prueba abb crear iterador desde un nodo diferente al primero",iterador);
    print_test("Prueba abb el iterador no esta al final",!abb_iter_in_al_final(iterador));
    print_test("Prueba abb iter ver actual es el correcto",difftime_wrappeado(abb_iter_in_ver_actual(iterador),&fecha2)==0);
    print_test("Prueba abb avanzar funciona",abb_iter_in_avanzar(iterador));
    print_test("Ver actual es el correcto",difftime_wrappeado(abb_iter_in_ver_actual(iterador),&fecha4)==0);
    abb_iter_in_destruir(iterador);
    abb_destruir(arbol);
}


void pruebas_abb_alumno(void){
	// pruebas_crear_abb_vacio();
	// pruebas_abb_instertar();
	pruebas_abb_reemplazar();
	pruebas_abb_reemplazar_destruir();
	// pruebas_abb_clave_vacia();
	// pruebas_abb_iter_interno(50);
	// pruebas_abb_iterar_vacio();
	// pruebas_abb_iterar_volumen(500);
 //    pruebas_abb_volumen(100);
 //    pruebas_iterar_basicas();
 //    pruebas_iterar_desde();
}
