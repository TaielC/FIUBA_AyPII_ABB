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

	if(comparacion_claves==0)
		return nodo_actual;

	*padre = nodo_actual;

	if(comparacion_claves>0)
		return abb_nodo_buscar(abb,clave_buscada, nodo_actual->der,padre);
	else
		return abb_nodo_buscar(abb,clave_buscada, nodo_actual->izq,padre);
	
}

void _abb_destruir_nodos(abb_nodo_t* nodo_actual,abb_destruir_dato_t destruir_dato){
	if(!nodo_actual) return;

	_abb_destruir_nodos(nodo_actual->izq,destruir_dato);
	_abb_destruir_nodos(nodo_actual->der,destruir_dato);

	if(destruir_dato){
		destruir_dato(nodo_actual->dato);
	}
	free(nodo_actual->clave);
	free(nodo_actual);
}

size_t nodo_cant_hijos(abb_nodo_t* nodo){
	size_t cant_hijos = 0;
	if(nodo->izq){
		cant_hijos++;
	}
	if(nodo->der){
		cant_hijos++;
	}

	return cant_hijos;
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

size_t abb_cantidad(abb_t* arbol){
	return arbol->cantidad;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	abb_nodo_t* padre = NULL;
	if(abb_nodo_buscar((abb_t*)arbol,(char*)clave,arbol->raiz,&padre)){
		return true;
	}
	return false;
}

void abb_destruir(abb_t *arbol){
	_abb_destruir_nodos(arbol->raiz,arbol->destruir_dato);
	free(arbol);
}


/* =========== PIMITIVA DEL ITER INTERNO =========== */




/* ========== PIMITIVAS DEL ITER INTERNO ========== */



