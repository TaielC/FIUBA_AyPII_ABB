#include <stdlib.h>
#include <stdbool.h>

#include "abb.h"

/* ============ TIPOS DE DATOS PARA ABB =========== */

typedef struct abb_nodo{
	struct abb* izq;
	struct abb* der;
	char* clave;
	void* dato;
}abb_nodo_t;

typedef struct abb{
	abb_nodo_t* raiz;
	abb_comparar_clave_t comparar_clave;
	abb_destruir_dato_t destruir_dato;
	int cantidad;
}abb_t;

/* ------------- FUNCIONES AUXILIARES ------------- */


/* ============== PRIMITIVAS DE ABB ============== */

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;

	abb->raiz = NULL;
	abb->destruir_dato = destruir_dato;
	abb->comparar_clave = cmp;
	abb->cantidad = 0;

	return abb;
}



/* =========== PIMITIVA DEL ITER INTERNO =========== */




/* ========== PIMITIVAS DEL ITER INTERNO ========== */



