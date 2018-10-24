#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "pila.h"
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

typedef struct abb_iter{
	abb_t* arbol;
	pila_t* pila;
}abb_iter_t;
/* ------------- FUNCIONES AUXILIARES ------------- */

abb_nodo_t* abb_nodo_buscar(abb_t* abb, char* clave_buscada, abb_nodo_t* nodo_actual, abb_nodo_t** padre){
	if(!nodo_actual) return NULL;

	int comparacion_claves = abb->comparar_clave(clave_buscada,nodo_actual->clave);

	if(!comparacion_claves)
		return nodo_actual;

	*padre = nodo_actual;

	if(comparacion_claves>0)
		return abb_nodo_buscar(abb,clave_buscada, nodo_actual->der,padre);
	else
		return abb_nodo_buscar(abb,clave_buscada, nodo_actual->izq,padre);
}

bool abb_nodo_insertar(abb_t* arbol, abb_nodo_t** nodo_actual, const char* clave_guardar, void* dato){
	if(!(*nodo_actual)){
		abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
		if( !nodo ) return false;
		nodo->clave = strdup(clave_guardar);
		nodo->dato = dato;
		*nodo_actual = nodo;
		return true;
	}

	int comparacion_claves = arbol->comparar_clave( clave_guardar, (*nodo_actual)->clave);

	if(!comparacion_claves){
		(*nodo_actual)->dato = dato;
		return true;
	}
	else if( comparacion_claves > 0 )
		return abb_nodo_insertar( arbol , &(*nodo_actual)->der, clave_guardar, dato);
	else 
		return abb_nodo_insertar( arbol , &(*nodo_actual)->der, clave_guardar, dato);
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

void _abb_in_order(abb_nodo_t* nodo,bool visitar(const char *, void *, void *),void* extra){
	if(!nodo) return;

	_abb_in_order(nodo->izq,visitar,extra);

	if(visitar(nodo->clave,nodo->dato,extra)){
		_abb_in_order(nodo->der,visitar,extra);
	}
}

void abb_apilar_izquierdos(pila_t* pila,abb_nodo_t* nodo){
	while(nodo){
		pila_apilar(pila,nodo);
		nodo = nodo->izq;
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
	return abb_nodo_insertar(arbol, &arbol->raiz, clave, dato);
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


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	_abb_in_order(arbol->raiz,visitar,extra);
}

/* ========== PIMITIVAS DEL ITER EXTERNO ========== */

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iterador = malloc(sizeof(abb_iter_t));
	if(!iterador) return NULL;

	iterador->pila = pila_crear();
	if(!iterador->pila){
		free(iterador);
		return NULL;
	}

	iterador->arbol = (abb_t*) arbol;
	abb_apilar_izquierdos(iterador->pila,arbol->raiz);

	return iterador;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if(pila_esta_vacia(iter->pila)) return false;

	abb_nodo_t* desapilado = pila_desapilar(iter->pila);
	abb_apilar_izquierdos(iter->pila,desapilado->der);
	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	return pila_ver_tope(iter->pila);
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}