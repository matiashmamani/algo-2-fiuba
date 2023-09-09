#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "hash.h"
#include "heap.h"
#include "usuarios.h"

struct usuarios {
    hash_t *hash;
};

typedef struct dato_hash {
    size_t pos;
    heap_t *heap;
} dato_hash_t;

typedef struct dato_heap {
    ssize_t id;
    size_t afinidad;
} dato_heap_t;

// Funcion de Comparacion para el heap
int afincmp(const void *a, const void *b){

    dato_heap_t* dato_heap1 = (dato_heap_t*)a;
    dato_heap_t* dato_heap2 = (dato_heap_t*)b;

    if(dato_heap1->afinidad < dato_heap2->afinidad) return 1;
    if(dato_heap1->afinidad > dato_heap2->afinidad) return -1;

    // dato_heap1->afinidad == dato_heap2->afinidad
    if(dato_heap1->id < dato_heap2->id) return 1;
    if(dato_heap1->id > dato_heap2->id) return -1;

    // NO PUEDE PUEDE PASAR NUNCA que tengan el mismo id
    return 0;
}

// Funciones auxiliares
dato_hash_t* __dato_hash_crear(size_t pos);
void __dato_hash_destruir(dato_hash_t *dato_hash);
void __wrapper_dato_hash_destruir(void *dato_hash);
dato_heap_t* __dato_heap_crear(ssize_t id, size_t afinidad);
void __dato_heap_destruir(dato_heap_t *dato_heap);
void __wrapper_dato_heap_destruir(void *dato_heap);

/* *****************************************************************
 *                    PRIMITIVAS DE TDA USUARIOS
 * *****************************************************************/
usuarios_t *usuarios_crear(void){

    usuarios_t *usuarios = malloc(sizeof(usuarios_t));
    if(!usuarios) return NULL;

    hash_t *hash = hash_crear(__wrapper_dato_hash_destruir);
    if(!hash){
        free(usuarios);
        return NULL;
    }

    usuarios->hash = hash;
    return usuarios;
}

bool usuarios_guardar(usuarios_t *usuarios, const char *usuario, size_t pos){

    dato_hash_t *dato_hash = __dato_hash_crear(pos);
    if(!dato_hash) return false;

    if(!hash_guardar(usuarios->hash, usuario, dato_hash)){
        __dato_hash_destruir(dato_hash);
        return false;
    }

    return true;
}

bool usuarios_pertenece(usuarios_t *usuarios, const char *usuario){
    return hash_pertenece(usuarios->hash, usuario);
}

bool usuarios_publicar(usuarios_t *usuarios, ssize_t id, const char *usuario){

    if(!hash_pertenece(usuarios->hash, usuario)) return false;
    dato_hash_t *dato_hash = hash_obtener(usuarios->hash, usuario);

    const char *usuario_activo = usuario;
    size_t pos_activo = dato_hash->pos;
    const char *usuario_actual;
    size_t pos_actual;
    size_t afinidad;

    dato_heap_t *dato_heap;
    hash_iter_t *hash_iter = hash_iter_crear(usuarios->hash);

    while(!hash_iter_al_final(hash_iter)){
        usuario_actual = hash_iter_ver_actual(hash_iter);
        if(!strcmp(usuario_activo, usuario_actual)){
        	hash_iter_avanzar(hash_iter);
        	continue;
        }

        dato_hash = hash_obtener(usuarios->hash, usuario_actual);
        pos_actual = dato_hash->pos;
        afinidad = (size_t)abs((int)pos_activo - (int)pos_actual);
        dato_heap = __dato_heap_crear(id, afinidad);
        if(!dato_heap){
            hash_iter_destruir(hash_iter);
            return false;
        }

        if(!heap_encolar(dato_hash->heap, dato_heap)){
            __dato_heap_destruir(dato_heap);
            hash_iter_destruir(hash_iter);
            return false;
        }

        hash_iter_avanzar(hash_iter);
    }

    hash_iter_destruir(hash_iter);
    return true;
}

ssize_t usuarios_ver_sig_feed(usuarios_t *usuarios, const char *usuario){

    if(!hash_pertenece(usuarios->hash, usuario)) return -1;
    dato_hash_t *dato_hash = hash_obtener(usuarios->hash, usuario);

    dato_heap_t *dato_heap = heap_desencolar(dato_hash->heap);
    if(!dato_heap) return -1;

    ssize_t id = dato_heap->id;
    __dato_heap_destruir(dato_heap);
    return id;
}

void usuarios_destruir(usuarios_t *usuarios){
    hash_destruir(usuarios->hash);
    free(usuarios);
}

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
dato_hash_t* __dato_hash_crear(size_t pos){

    dato_hash_t *dato_hash = malloc(sizeof(dato_hash_t));
    if(!dato_hash) return NULL;

    heap_t *heap = heap_crear(afincmp);
    if(!heap){
        free(dato_hash);
        return NULL;
    }

    dato_hash->pos = pos;
    dato_hash->heap = heap;
    return dato_hash;
}

void __dato_hash_destruir(dato_hash_t *dato_hash){
    heap_destruir(dato_hash->heap, __wrapper_dato_heap_destruir);
    free(dato_hash);
}

void __wrapper_dato_hash_destruir(void *dato_hash){
    __dato_hash_destruir((dato_hash_t*)dato_hash);
}

dato_heap_t* __dato_heap_crear(ssize_t id, size_t afinidad){

    dato_heap_t *dato_heap = malloc(sizeof(dato_heap_t));
    if(!dato_heap) return NULL;

    dato_heap->id = id;
    dato_heap->afinidad = afinidad;
    return dato_heap;
}

void __dato_heap_destruir(dato_heap_t *dato_heap){
    free(dato_heap);
}

void __wrapper_dato_heap_destruir(void *dato_heap){
    __dato_heap_destruir((dato_heap_t*)dato_heap);
}