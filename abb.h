#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdbool.h>

/* ---------- Definición de tipos de datos ---------- */

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const void *, const void *);
typedef void (*abb_destruir_dato_t) (void *);

typedef struct abb_iter abb_iter_t;

/* -------------- Primitivas del ABB -------------- */


/*
Crea el arbol
Pre:cmp es una funcion es una funcion que recibe dos cadenas y devuelve:
Un entero menor que 0 si la primera es menor que la segunda, un entero mayor que 0 
si la primera es mayor que la segunda, o 0 si ambas son iguales. Además recibe un tamaño,
en bytes, de las claves a utilizar (se sugiere dar un byte de más para evitar errores),
si estas son strings de longitud variable se puede asignar a 0.
Destruir dato es una funcion capaz de destruir los datos almacenados en el abb, o NULL.
Post:El abb fue creado.
*/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato, int tamanio);

/*
Pre: El arbol fue creado.
Post:Se guardo la clave y su dato asociado en el arbol. Devuelve
true si el guardado fue exitoso, false en caso contrario.
*/
bool abb_guardar(abb_t *arbol, const void *clave, void *dato);

/*
Pre:El arbol fue creado.
Post: La clave junto con su dato asociado
fueron removidos del arbol.
Devuelve el dato borrado en caso de que este haya estado 
en el arbol, o NULL en caso contrario.
*/
void *abb_borrar(abb_t *arbol, const void *clave);

/*
Pre:El arbol fue creado
Post: Se devolvio el valor asociado a la clave, en caso de que
este haya estado en el arbol, o NULL en caso contrario.
*/
void *abb_obtener(const abb_t *arbol, const void *clave);

/*
Pre: El arbol fue creado
Post: Se devolvio true si la clave estaba en el arbol, o false en caso
contrario.
*/
bool abb_pertenece(const abb_t *arbol, const void *clave);

/*
Pre: El arbol fue creado
Post: Se devolvio la cantidad de claves que contiene
el arbol.
*/
size_t abb_cantidad(abb_t *arbol);

/*
Pre: El arbol fue creado
Post: Se eliminaron todos los elementos almacenados en el arbol 
utilizando la funcion destruir_dato pasada en la creacion del arbol.
Se elimino tambien el arbol en si.
*/
void abb_destruir(abb_t *arbol);

/* -------- Primitiva del iterador interno del ABB -------- */
/*
Pre: El arbol fue creado, visitar es una funcion de callback 
que recibe una clave, su dato asociado, y un extra, y que devuelve
verdadero en caso de que se quiera seguir iterando, y false en caso contrario.
Post: Se realizo un recorrido in-order del arbol siempre que la funcion visitar devolvio
true, aplicandosele esta a cada uno de los elementos del arbol en el orden mencionado.
*/
void abb_in_order(abb_t *arbol, bool visitar(const void *, void *, void *), void *extra);


/* -------- Primitivas del iterador externo del ABB -------- */

/*
Pre: El arbol fue creado
Post: Se devolvio un puntero a iterador.
*/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

abb_iter_t* abb_iter_in_crear_desde(const abb_t *arbol,void* desde);

/*
Pre: El iterador fue creado
Post: De ser posible, se avanzo al siguiente elemento en el arbol (Realizando un recorrido in-order).
Devuelve true si fue posible avanzar, false en caso contrario.
*/
bool abb_iter_in_avanzar(abb_iter_t *iter);

/*
Pre: El iterador fue creado
Post: Devuelve la clave sobre la cual se encuentra el iterador en este momento, o
NULL si el iterador se encuentra al final.
*/
const void *abb_iter_in_ver_actual(const abb_iter_t *iter);

/*
Pre: El iterador fue creado
Post: Se devolvio true si el iterador se encontraba al final del recorrido in-order del arbol
o false en caso contrario.
*/
bool abb_iter_in_al_final(const abb_iter_t *iter);

/*
Pre: El iterador fue creado
Post:Se destruyo el iterador.
*/
void abb_iter_in_destruir(abb_iter_t* iter);



#endif //ABB_H