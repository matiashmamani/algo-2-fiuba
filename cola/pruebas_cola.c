#define VOLUMEN 100000
#define POS_PRIMERO 0

#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

void limpiar_entero(void *dato){
    int *p_int;
    p_int = (int*)dato;
    *p_int = 0;
}

static void prueba_cola_vacia(void) {

    printf("1. INICIO DE PRUEBAS CON COLA VACIA\n");
    cola_t *cola = cola_crear();
    print_test("- Crear cola vacía", cola != NULL);
    print_test("- Cola esta vacía", cola_esta_vacia(cola));
    print_test("- Ver primero de la cola vacia devuelve NULL", cola_ver_primero(cola) == NULL);
    print_test("- Desencolar en cola vacia devuelve NULL", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
    print_test("- Destruir cola vacía", true);
}

static void prueba_cola_algunos_elementos_estaticos(void) {

    void *p_null = NULL;
    int n_null = 5;
    
    printf("2. INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS ESTATICOS\n");
    printf("COLA QUE ALMACENA VALORES NULL:\n");
    cola_t *cola = cola_crear();
    print_test("- Crear cola", cola != NULL);

    bool ok = true;
    bool ok_ver_primero = true;
    for(int i = 0; i < n_null; i++){
        ok &= cola_encolar(cola, p_null);
        ok_ver_primero &= (cola_ver_primero(cola) == NULL);
    }
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento de la cola es NULL en cada encolado", ok_ver_primero);
    print_test("- Cola no esta vacía", !cola_esta_vacia(cola));

    ok = true;
    for(int i = 0; i < n_null; i++){
        p_null = cola_desencolar(cola);
        ok &= (p_null == NULL);
    }
    print_test("- Se pudieron desencolar todos los elementos y mantienen invariante de cola", ok);
    print_test("- Cola quedó vacía después de desencolar todo", cola_esta_vacia(cola));
    print_test("- Ver primero de cola devuelve NULL después de desencolar todo", cola_ver_primero(cola) == NULL);
    print_test("- Desencolar en cola vacía devuelve NULL", cola_desencolar(cola) == NULL);
    for(int i = 0; i < n_null; i++){
        cola_encolar(cola, p_null);
    }
    print_test("- Cola se llenó de vuelta", !cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
    print_test("- Destruir cola (con NULL)", true);
}

static void prueba_cola_algunos_elementos_dinamicos(void){

    int **vec_int;
    int n_int  = 3;

    // Creo arreglo de arreglos de enteros
    vec_int = malloc((size_t)n_int * sizeof(int*));
    for(int i = 0; i < n_int; i++){
        vec_int[i] = malloc((size_t)n_int * sizeof(int));
        for(int j = 0; j < n_int; j++){
            vec_int[i][j] = i;
        }
    }

    printf("3. INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS DINAMICOS\n");
    printf("COLA QUE ALMACENA VECTORES DINAMICOS:\n");
    cola_t *cola = cola_crear();
    print_test("- Crear cola", cola != NULL);

    bool ok = true;
    bool ok_ver_primero = true;
    int *p_int;
    for(int i = 0; i < n_int; i++){
        ok &= cola_encolar(cola, vec_int[i]);
        p_int = cola_ver_primero(cola);
        ok_ver_primero &= (p_int == vec_int[POS_PRIMERO]);
    }
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento de la cola es correcto en cada encolado", ok_ver_primero);
    print_test("- Cola no esta vacía", !cola_esta_vacia(cola));

    cola_destruir(cola, free);
    print_test("- Destruir cola (con free())", true);
    free(vec_int);
}

static void prueba_cola_volumen(void) {

    printf("4. INICIO DE PRUEBAS DE VOLUMEN\n");
    cola_t *cola = cola_crear();
    print_test("- Crear cola", cola != NULL);
    
    bool ok = true;
    bool ok_ver_primero = true;
    int *p_int;
    int vec_int[VOLUMEN];
    for(int i = 0; i < VOLUMEN; i++){
        vec_int[i] = i;
        ok &= cola_encolar(cola, &vec_int[i]);
        p_int = cola_ver_primero(cola);
        ok_ver_primero &= (*p_int == vec_int[POS_PRIMERO]);
    } 
    print_test("- Se pudieron encolar todos los elementos", ok);
    print_test("- El primer elemento de la cola es correcto en cada encolado", ok_ver_primero);
    print_test("- Cola no esta vacía", !cola_esta_vacia(cola));

    ok = true;
    p_int = NULL;
    for(int i = 0; i < VOLUMEN; i++){
        p_int = cola_desencolar(cola);
        ok &= (*p_int == vec_int[i]);
    }
    print_test("- Se pudieron desencolar todos los elementos y se mantiene el invariante de cola", ok);
    print_test("- Cola quedó vacía después de desencolar todo", cola_esta_vacia(cola));
    print_test("- Ver primero de la cola devuelve NULL después de desencolar todo", cola_ver_primero(cola) == NULL);
    print_test("- Desencolar en cola vacía devuelve NULL", cola_desencolar(cola) == NULL);
    
    for(int i = 0; i < VOLUMEN; i++){
        vec_int[i] = i;
        cola_encolar(cola, &vec_int[i]);
    }
    print_test("- Cola se llenó de vuelta", !cola_esta_vacia(cola));
    cola_destruir(cola, limpiar_entero);
    print_test("- Destruir cola (con funcion())", true);
}

void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_cola_algunos_elementos_estaticos();
    prueba_cola_algunos_elementos_dinamicos();
    prueba_cola_volumen();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
