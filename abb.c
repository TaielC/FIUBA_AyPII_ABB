#define _GNU_SOURCE
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

abb_nodo_t** abb_nodo_buscar(abb_t* abb, const char* clave_buscada, abb_nodo_t** nodo_actual){
	if(!*nodo_actual) return nodo_actual;

	int comparacion_claves = abb->comparar_clave(clave_buscada,(*nodo_actual)->clave);

	if(!comparacion_claves)
		return nodo_actual;

	if(comparacion_claves>0)
		return abb_nodo_buscar(abb,clave_buscada, &(*nodo_actual)->der);
	else
		return abb_nodo_buscar(abb,clave_buscada, &(*nodo_actual)->izq);
}


bool abb_nodo_insertar(abb_t* arbol, const char* clave_guardar, void* dato){
	
	abb_nodo_t** nodo = abb_nodo_buscar(arbol, clave_guardar, &arbol->raiz);

	if(!*nodo){
		abb_nodo_t* nodo_guardar = malloc(sizeof(abb_nodo_t));
		if( !nodo ) return false;
		nodo_guardar->clave = strdup(clave_guardar);
		if( !nodo_guardar->clave ){
			free(nodo);
			return false;
		}
		nodo_guardar->dato = dato;
		*nodo = nodo_guardar;
		arbol->cantidad++;
		return true;
	}

	int comparacion_claves = arbol->comparar_clave( clave_guardar, (*nodo)->clave);

	if(!comparacion_claves){
		(*nodo)->dato = dato;
		return true;
	}
	return false;
}

void* abb_destruir_nodo( abb_nodo_t* nodo ){
	if(!nodo) return NULL;
	free(nodo->clave);
	free(nodo);
}

void _abb_destruir_nodos(abb_nodo_t* nodo_actual,abb_destruir_dato_t destruir_dato){
	if(!nodo_actual) return;

	_abb_destruir_nodos(nodo_actual->izq,destruir_dato);
	_abb_destruir_nodos(nodo_actual->der,destruir_dato);

	void* dato = abb_destruir_nodo(nodo_actual);
	if( destruir_dato )
		destruir_dato( dato );
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

abb_nodo_t** abb_buscar_siguiente( abb_t* arbol, abb_nodo_t** nodo_actual){
	if(!*nodo_actual) return NULL;
	if(!(*nodo_actual)->der) return NULL;
	*nodo_actual = (*nodo_actual)->der;

	while((*nodo_actual)->izq)
		*nodo_actual = (*nodo_actual)->izq;

	return nodo_actual;
}

void abb_swap_nodos( abb_nodo_t* nodo_1, abb_nodo_t* nodo_2){
	abb_nodo_t* aux = nodo_1;
	nodo_1 = nodo_2;
	nodo_2 = aux;
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
	return abb_nodo_insertar(arbol, clave, dato);
}

void* abb_borrar(abb_t* arbol, const char* clave){

	abb_nodo_t** nodo_borrar = abb_nodo_buscar(arbol, clave, &arbol->raiz);
	if(!*nodo_borrar) NULL;

	int cant_hijos = nodo_cant_hijos( *nodo_borrar );
	void* dato = NULL;
	if(cant_hijos == 0){
		dato = abb_destruir_nodo( *nodo_borrar );
		*nodo_borrar = NULL;
	}
	else if(cant_hijos == 1){
		abb_nodo_t* reemplazante;
		if((*nodo_borrar)->der)
			reemplazante = (*nodo_borrar)->der;
		else 
			reemplazante = (*nodo_borrar)->izq;

		dato = abb_destruir_nodo(*nodo_borrar);
		*nodo_borrar = reemplazante;
	}
	else{
		abb_nodo_t** reemplazante = abb_buscar_siguiente( arbol, nodo_borrar);
		abb_swap_nodos( *reemplazante, *nodo_borrar);
		dato = abb_destruir_nodo(*reemplazante);
		*reemplazante = NULL;
	}
	arbol->cantidad--;
	return dato;
}

size_t abb_cantidad(abb_t* arbol){
	return arbol->cantidad;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){

	if(*abb_nodo_buscar((abb_t*)arbol,(char*)clave,(abb_nodo_t**)&arbol->raiz)){
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



