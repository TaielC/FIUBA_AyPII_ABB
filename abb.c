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
	void* dato = nodo->dato;
	free(nodo->clave);
	
	free(nodo);
	return dato;
}

void abb_destruir_nodos(abb_nodo_t* nodo_actual,abb_destruir_dato_t destruir_dato){
	if(!nodo_actual) return;

	abb_destruir_nodos(nodo_actual->izq,destruir_dato);
	abb_destruir_nodos(nodo_actual->der,destruir_dato);

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

abb_nodo_t* abb_buscar_siguiente( abb_t* arbol, abb_nodo_t* nodo_actual){
	if(!nodo_actual) return NULL;
	if(!nodo_actual->der) return NULL;
	nodo_actual = nodo_actual->der;

	while(nodo_actual->izq)
		nodo_actual = nodo_actual->izq;

	return nodo_actual;
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
		abb_nodo_t* reemplazante = abb_buscar_siguiente( arbol, *nodo_borrar);
		char* clave_reemplazante = strdup(reemplazante->clave);
		dato = (*nodo_borrar)->dato;
		(*nodo_borrar)->dato = abb_borrar( arbol, clave_reemplazante);
		(*nodo_borrar)->clave = clave_reemplazante;
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
	abb_destruir_nodos(arbol->raiz,arbol->destruir_dato);
	free(arbol);
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	abb_t* arbol_buscar = (abb_t*)arbol;
	abb_nodo_t** nodo = abb_nodo_buscar(arbol_buscar,clave,&arbol_buscar->raiz);
	if(*nodo){
		return (*nodo)->dato;
	}
	return NULL;
}

/* =========== PIMITIVA DEL ITER INTERNO =========== */


void _abb_in_order(abb_nodo_t* nodo,bool visitar(const char *, void *, void *),void* extra){
	if(!nodo) return;

	_abb_in_order(nodo->izq,visitar,extra);

	if(visitar(nodo->clave,nodo->dato,extra)){
		_abb_in_order(nodo->der,visitar,extra);
	}
}

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