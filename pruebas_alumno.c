#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "testing.h"
#include "abb.h"

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

void pruebas_abb_alumno(void){
	pruebas_crear_abb_vacio();
	pruebas_abb_instertar();
}