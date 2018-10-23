#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "abb.h"

/* ============ TIPOS DE DATOS PARA ABB =========== */

typedef struct abb_nodo{
	struct abb_nodo* izq;
	struct abb_nodo* der;
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
abb_nodo_t* abb_nodo_buscar(abb_t* abb, char* clave_buscada, abb_nodo_t* nodo_actual, abb_nodo_t** padre){
	if(!nodo_actual) return NULL;

	int comparacion_claves = abb->comparar_clave(clave_buscada,nodo_actual->clave);

	if(comparacion_claves==0){
		return nodo_actual;
	}

	*padre = nodo_actual;

	if(comparacion_claves>0){
		return abb_nodo_buscar(abb,clave_buscada, nodo_actual->der,padre);
	}else{
		return abb_nodo_buscar(abb,clave_buscada, nodo_actual->izq,padre);
	}
}


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



