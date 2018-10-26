#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "testing.h"
#include "abb.h"

#define GRAN_VOL 10000
#define LARGO_CLAVE 10
#define FIN_STRING '\0'

void pruebas_crear_abb_vacio(void){
	abb_t* arbol = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", arbol);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(arbol) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(arbol, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(arbol, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(arbol, "A"));

    abb_destruir(arbol);
}

void pruebas_abb_instertar(void){

	abb_t* arbol = abb_crear(strcmp, NULL);

	char* clave1 = "0050", *clave2 = "0025", *clave3 = "0100",
	*clave4 = "0000", *clave5 = "0035", *clave6 = "0075", *clave7 = "0125";
	char* dato1 = "Hello World!";
	int dato2 = 2048;
	long dato3 = 49102321;

	  print_test("Prueba abb insertar clave1, con dato1", abb_guardar(arbol, clave1, dato1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Prueba abb obtener clave1 es dato1", !strcmp(abb_obtener(arbol, clave1), dato1));
    print_test("Prueba abb obtener clave1 es dato1", !strcmp(abb_obtener(arbol, clave1), dato1));
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
	abb_t* abb = abb_crear(strcmp,NULL);

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
	print_test("Prueba abb obtener valor clave2 es valor2a",abb_obtener(abb,clave2)==valor2b);
	print_test("Prueba abb obtener valor clave2 es valor2a",abb_obtener(abb,clave2)==valor2b);
	print_test("La cantidad de elementos es 2",abb_cantidad(abb)==2);
	abb_destruir(abb);
}

void pruebas_abb_reemplazar_destruir(){
	abb_t* abb = abb_crear(strcmp,free);

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

void pruebas_abb_volumen(void){

    char* claves[GRAN_VOL];
    int posicion = 0;
    crear_array_para_insertar_ordenado(claves, &posicion, GRAN_VOL, 0);
    bool ok_guardar = true;

    abb_t* abb = abb_crear(strcmp, free);
    for(posicion = 0; posicion < GRAN_VOL ; posicion++ ){
        ok_guardar &= abb_guardar(abb, claves[posicion], claves[posicion]);
    }
    print_test("Pruebas abb volumen, insertar muchos elementos", ok_guardar );

    bool ok_borrar = true;
    bool ok_pertenece = false;
    for(posicion = 13; posicion < GRAN_VOL ; posicion+=7){
        ok_borrar &= (abb_borrar(abb, claves[posicion])==claves[posicion]);
        ok_pertenece |= abb_pertenece(abb, claves[posicion]);
    }
    print_test("Pruebas abb volumen, borrar elementos al azar", ok_borrar );
    print_test("Pruebas abb volumen, claves borradas no pertenecen", !ok_pertenece );

    ok_pertenece = true;
    bool ok_obtener = true;
    for(posicion = 17; posicion+1 < GRAN_VOL; posicion += 7){
        ok_pertenece &= abb_pertenece(abb, claves[posicion]);
        ok_obtener &= (abb_obtener(abb, claves[posicion+1]) == claves[posicion+1]);
    }
    print_test("Pruebas abb volumen, pertenecen claves no borradas", ok_pertenece );
    print_test("Pruebas abb volumen, obtener claves datos correctos", ok_obtener);

    for(posicion = 13; posicion < GRAN_VOL; posicion += 7){
        ok_guardar &= abb_guardar(abb, claves[posicion], claves[posicion]);
    }
    print_test("Pruebas abb volumen, guardar elementos borrados", ok_guardar);

    abb_destruir(abb);
}

void pruebas_iterar_basicas(void){

    abb_t* abb = abb_crear(strcmp, NULL);

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
    print_test("Pruebas abb iter externo, ver actual es correcto", *(int*)abb_iter_in_ver_actual(iter) == datos[0]);
    print_test("Pruebas abb iter externo, se puede avanzar", abb_iter_in_avanzar(iter));

    bool ok_avanzar = true;
    bool ok_actual = true;
    for( int i = 1; i < 15; i++ ){
        char* clave_actual = (char*)abb_iter_in_ver_actual(iter);
        for(int j = 1; j < 15; j++){
            if(!strcmp(clave_actual, claves[j]))
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

void pruebas_abb_alumno(void){
	pruebas_crear_abb_vacio();
	pruebas_abb_instertar();
    pruebas_abb_reemplazar();
    pruebas_abb_reemplazar_destruir();
    pruebas_abb_volumen();

    pruebas_iterar_basicas();
}