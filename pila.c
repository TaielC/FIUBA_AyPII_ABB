#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define TAM_INICIAL 10

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

bool pila_redimensionar(pila_t* pila,size_t cap_nueva);
/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){

	//Alloc del puntero a la pila.
	pila_t* pila = malloc(sizeof(pila_t));

	if(pila==NULL){
		return NULL;
	}

	
	pila->capacidad=TAM_INICIAL;

	//Alloc del array de punteros a datos de la pila.
	pila->datos = malloc(sizeof(void*)*pila->capacidad);

	if(pila->datos==NULL){
		return NULL;
	}

	pila->cantidad=0;

	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad==0;
}

bool pila_apilar(pila_t *pila, void* valor){

	//Redimensionamiento de la pila en caso de que este llena.
	if(pila->cantidad>=pila->capacidad){
		if(!pila_redimensionar(pila,pila->capacidad*2)){
			return false;
		}
	}

	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}


void* pila_ver_tope(const pila_t *pila){

	if(pila_esta_vacia(pila)){
		return NULL;
	}

	return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){

	if(pila_esta_vacia(pila)){
		return NULL;
	}

	void* dato = pila_ver_tope(pila);
	pila->cantidad--;

	if( ((float)pila->cantidad < (float)(pila->capacidad)*0.25) && pila->capacidad>1){
		if(!pila_redimensionar(pila,(pila->capacidad)/2)){
			return NULL;
		}
	}

	return dato;
}


bool pila_redimensionar(pila_t* pila,size_t cap_nueva){

	//Reallocamiento de los datos con la capacidad nueva.
	void** datos_nuevo = realloc(pila->datos , sizeof(void*)*cap_nueva);

	if(datos_nuevo==NULL){
		return false;
	}
	printf("Pila redimensionada a %d\n",(int)cap_nueva);
	pila->datos=datos_nuevo;
	pila->capacidad=cap_nueva;

	return true;
}

