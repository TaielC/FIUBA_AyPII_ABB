#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "testing.h"
#include "abb.h"

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

void pruebas_abb_alumno(void){
	pruebas_abb_reemplazar();
}