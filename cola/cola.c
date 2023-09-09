#include "cola.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo nodo_t;

struct nodo {
    void *dato;         // Apunta al dato almacenado
    nodo_t *prox;       // Apunta al próximo nodo
};

struct cola {
    nodo_t* primero;    // Apunta al primer nodo de la Cola
    nodo_t* ultimo;     // Apunta al último nodo de la Cola
};

// Función para uso interno
nodo_t *__crear_nodo(void *valor);

/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t *cola_crear(void){
    
    cola_t *cola = malloc(sizeof(cola_t));
    if(cola == NULL) return NULL;
    
    cola->primero = NULL;
    cola->ultimo = NULL;

    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){

    if(cola == NULL) return;

    void* dato;

    while(!cola_esta_vacia(cola)){

        dato = cola_desencolar(cola);

        if(destruir_dato != NULL){
            destruir_dato(dato);
        }
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){

    if(cola == NULL) return false;
    
    return (cola->primero == NULL) && (cola->ultimo == NULL);
}

bool cola_encolar(cola_t *cola, void *valor){

    if(cola == NULL) return false;

    nodo_t *nodo_nuevo = __crear_nodo(valor);
    if(nodo_nuevo == NULL) return false;       // No se pudo crear el nodo
   
    if(cola_esta_vacia(cola)){
        cola->primero = nodo_nuevo;       // Si la cola está vacia => el nuevo nodo es el primero
    } else {
        cola->ultimo->prox = nodo_nuevo;  // Quien era el último nodo debe apuntar al nuevo nodo
    }
    cola->ultimo  = nodo_nuevo;     // El nuevo nodo es siempre el último

    return true;
}

void *cola_ver_primero(const cola_t *cola){
    
    if(cola == NULL) return NULL;

    return cola_esta_vacia(cola)? NULL : cola->primero->dato;
}

void *cola_desencolar(cola_t *cola){

    if(cola == NULL) return NULL;
    if(cola_esta_vacia(cola)) return NULL;

    void *dato = cola_ver_primero(cola);
    nodo_t *nodo_aux = cola->primero->prox;
    free(cola->primero);
    cola->primero = nodo_aux;

    if(cola->primero == NULL){
        cola->ultimo = NULL;   // Solo cuando desencole el último elemento
    }

    return dato;
}

nodo_t *__crear_nodo(void *valor){

    nodo_t *nodo_nuevo = malloc(sizeof(nodo_t));
    if(nodo_nuevo == NULL) return NULL;

    nodo_nuevo->dato = valor;
    nodo_nuevo->prox = NULL;

    return nodo_nuevo;
}