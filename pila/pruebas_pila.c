#define VOLUMEN 100000

#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_pila_vacia(void) {

    printf("1. INICIO DE PRUEBAS CON PILA VACIA\n");
    pila_t *pila = pila_crear();
    print_test("- Crear pila vacía", pila != NULL);
    print_test("- Pila esta vacía", pila_esta_vacia(pila));
    print_test("- Ver tope de la pila vacia devuelve NULL", pila_ver_tope(pila) == NULL);
    print_test("- Desapilar en pila vacia devuelve NULL", pila_desapilar(pila) == NULL);
    pila_destruir(pila);
}

static void prueba_pila_algunos_elementos(void) {

    void **vec_null;
    int vec_int[]   = { 5, 9, -8, 10, 3, 1, -4};
    char vec_char[] = { 'h', 'o', 'l', 'a', '\n'};

    int n_null = 4;
    int n_int  = 7;
    int n_char = 5;

    // Creo vector de NULLs
    vec_null = malloc((size_t)n_null * sizeof(void*));
    for(int i = 0; i < n_null; i++){
        vec_null[i] = NULL;
    }
 
    printf("2. INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");
    printf("a) PILA QUE ALMACENA VALORES NULL:\n");
    pila_t *pila = pila_crear();
    print_test("- Crear pila", pila != NULL);

    bool ok = true;
    bool ok_ver_tope = true;
    void **p_null;
    for(int i = 0; i < n_null; i++){
        ok &= pila_apilar(pila, &vec_null[i]);
        p_null = pila_ver_tope(pila);
        ok_ver_tope &= (*p_null == NULL);
    }
    print_test("- Se pudieron apilar todos los elementos", ok);
    print_test("- El tope es NULL en cada apilada", ok_ver_tope);
    print_test("- Pila no esta vacía", !pila_esta_vacia(pila));

    ok = true;
    p_null = NULL;
    for(int i = n_null - 1; i >= 0; i--){
        p_null = pila_desapilar(pila);
        ok &= (*p_null == vec_null[i]);
    }
    print_test("- Se pudieron desapilar todos los elementos y mantienen invariante de pila", ok);
    print_test("- Pila quedó vacía después de desapilar todo", pila_esta_vacia(pila));
    print_test("- Tope de pila devuelve NULL después de desapilar todo", pila_ver_tope(pila) == NULL);
    print_test("- Desapilar en pila vacía devuelve NULL", pila_desapilar(pila) == NULL);
    pila_destruir(pila);
    
    // Destruyo vector de NULLs
    free(vec_null);

    printf("b) PILA QUE ALMACENA VALORES INT:\n");
    pila = pila_crear();
    print_test("- Crear pila", pila != NULL);
    
    ok = true;
    ok_ver_tope = true;
    int *p_int;
    for(int i = 0; i < n_int; i++){
        ok &= pila_apilar(pila, &vec_int[i]);
        p_int = pila_ver_tope(pila);
        ok_ver_tope &= (*p_int == vec_int[i]);
    } 
    print_test("- Se pudieron apilar todos los elementos", ok);
    print_test("- El tope fue el correcto en cada apilada", ok_ver_tope);
    print_test("- Pila no esta vacía", !pila_esta_vacia(pila));

    ok = true;
    p_int = NULL;
    for(int i = n_int - 1; i >= 0; i--){
        p_int = pila_desapilar(pila);
        ok &= (*p_int == vec_int[i]);
    }
    print_test("- Se pudieron desapilar todos los elementos y mantienen invariante de pila", ok);
    print_test("- Pila quedó vacía después de desapilar todo", pila_esta_vacia(pila));
    print_test("- Tope de pila devuelve NULL después de desapilar todo", pila_ver_tope(pila) == NULL);
    print_test("- Desapilar en pila vacía devuelve NULL", pila_desapilar(pila) == NULL);
    pila_destruir(pila);


    printf("c) PILA QUE ALMACENA VALORES CHAR:\n");
    pila = pila_crear();
    print_test("- Crear pila", pila != NULL);
    
    ok = true;
    ok_ver_tope = true;
    char *p_char;
    for(int i = 0; i < n_char; i++){
        ok &= pila_apilar(pila, &vec_char[i]);
        p_char = pila_ver_tope(pila);
        ok_ver_tope &= (*p_char == vec_char[i]);
    } 
    print_test("- Se pudieron apilar todos los elementos", ok);
    print_test("- El tope fue el correcto en cada apilada", ok_ver_tope);
    print_test("- Pila no esta vacía", !pila_esta_vacia(pila));

    ok = true;
    p_char = NULL;
    for(int i = n_char - 1; i >= 0; i--){
        p_char = pila_desapilar(pila);
        ok &= (*p_char == vec_char[i]);
    }
    print_test("- Se pudieron desapilar todos los elementos y mantienen invariante de pila", ok);
    print_test("- Pila quedó vacía después de desapilar todo", pila_esta_vacia(pila));
    print_test("- Tope de pila devuelve NULL después de desapilar todo", pila_ver_tope(pila) == NULL);
    print_test("- Desapilar en pila vacía devuelve NULL", pila_desapilar(pila) == NULL);
    pila_destruir(pila);
}

static void prueba_pila_volumen(void) {

    printf("3. INICIO DE PRUEBAS DE VOLUMEN\n");
    pila_t *pila = pila_crear();
    print_test("- Crear pila", pila != NULL);
    
    bool ok = true;
    bool ok_ver_tope = true;
    int aux;
    int *p_aux;
    for(int i = 0; i < VOLUMEN; i++){
        aux = i;
        ok &= pila_apilar(pila, &aux);
        p_aux = pila_ver_tope(pila);
        ok_ver_tope &= (*p_aux == aux);
    } 
    print_test("- Se pudieron apilar todos los elementos", ok);
    print_test("- El tope fue el correcto en cada apilada", ok_ver_tope);
    print_test("- Pila no esta vacía", !pila_esta_vacia(pila));

    ok = true;
    ok_ver_tope = true;
    p_aux = NULL;
    for(int i = VOLUMEN - 1; i >= 0; i--){
        aux = i;
        p_aux = pila_ver_tope(pila);
        ok_ver_tope &= (*p_aux == aux);
        p_aux = pila_desapilar(pila);
        ok &= (*p_aux == aux);
    }
    print_test("- El tope fue el correcto en cada desapilada", ok_ver_tope);
    print_test("- Se pudieron desapilar todos los elementos y mantienen invariante de pila", ok);
    print_test("- Pila quedó vacía después de desapilar todo", pila_esta_vacia(pila));
    print_test("- Tope de pila devuelve NULL después de desapilar todo", pila_ver_tope(pila) == NULL);
    print_test("- Desapilar en pila vacía devuelve NULL", pila_desapilar(pila) == NULL);
    pila_destruir(pila);
}


void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_algunos_elementos();
    prueba_pila_volumen();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
