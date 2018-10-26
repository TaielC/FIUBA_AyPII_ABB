#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "testing.h"
#include "abb.h"

void pruebas_crear_abb_vacio(void){
	abb_t* abb = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));
}

void pruebas_abb_alumno(void){
	
}