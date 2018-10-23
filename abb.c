#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

	abb_t* arbol = malloc(sizeof(abb_t));
	if(!arbol) return NULL;

	arbol->raiz = NULL;
	arbol->destruir_dato = destruir_dato;
	arbol->comparar_clave = cmp;
	arbol->cantidad = 0;

	return arbol;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if(!nodo) return false;

	nodo->clave = strdup(clave);
	if(!nodo->clave){
		free( nodo );
		return false;
	}
	nodo->dato = dato;
	arbol->cantidad++;

	if(!arbol->raiz){
		arbol->raiz = nodo;
		return true;
	}

	abb_nodo_t guardar = abb_nodo_buscar();

	return true;
}




/* =========== PIMITIVA DEL ITER INTERNO =========== */




/* ========== PIMITIVAS DEL ITER INTERNO ========== */



