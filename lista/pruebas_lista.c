#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_VOLUMEN 1000

void limpiar_entero(void *dato){
    int *p_int;
    if(dato != NULL)
    {
        p_int = (int*)dato;
        *p_int = 0;
    }
}

static void prueba_lista_vacia(void) {

	lista_t *lista = lista_crear();

    	printf("1. INICIO DE PRUEBAS CON LISTA VACIA\n");
	
	print_test("Lista vacía creada", lista != NULL);
	
	print_test("Lista vacía",lista_esta_vacia(lista));
	
	//Pruebas borde
	print_test("Ver primer elemento lista vacía", lista_ver_primero(lista) == NULL);
	
	print_test("Borrar elemento lista vacía", lista_borrar_primero(lista) == NULL);
	
	lista_destruir(lista,NULL);
}

bool prueba_insertar_borrar_elementos(lista_t * lista){
	bool bool_ok= true;
	int * aux_pointer;
	
    int int_element = 5;
    int int_element_aux = 8;

	bool_ok &= lista_insertar_primero(lista, &int_element);
	
	print_test("Se pudo insertar el elemento INT", !lista_esta_vacia(lista));
	
	print_test("Ver primer elemento con un elemento INT", lista_ver_primero(lista) == &int_element);
	
	aux_pointer = lista_borrar_primero(lista);
      	bool_ok = bool_ok & (*aux_pointer == int_element);
	
	print_test("Se pudo borrar el elemento INT", lista_esta_vacia(lista));
	
	//Insertar primero insertar ultimo borrar solo primero
	bool_ok &= lista_insertar_primero(lista, &int_element);
	print_test("Se pudo insertar primero el elemento INT 1", !lista_esta_vacia(lista));
	print_test("Ver largo con un solo elemento", lista_largo(lista) == 1);
	
	bool_ok &= lista_insertar_ultimo(lista, &int_element_aux);
	print_test("Se pudo insertar último el elemento INT 2", bool_ok);
	print_test("Ver largo con dos elementos", lista_largo(lista) == 2);
	
	print_test("Ver primer elemento en lista con más de un elemento INT", lista_ver_primero(lista) == &int_element);
	print_test("Ver último elemento en lista con más de un elemento INT", lista_ver_ultimo(lista) == &int_element_aux);
	
	aux_pointer = lista_borrar_primero(lista);
      	bool_ok = bool_ok & (*aux_pointer == int_element);
	
	print_test("Luego de borrar primer elemento ver primer elemento debe devolver el elemento auxiliar", lista_ver_primero(lista) == &int_element_aux);
	
	aux_pointer = lista_borrar_primero(lista);
      	bool_ok = bool_ok & (*aux_pointer == int_element);
	
	return bool_ok;
} 

static void prueba_insertar_borrar(void) {

    printf("2. INICIO DE PRUEBAS INSERTAR Y BORRAR ELEMENTOS\n");

    lista_t *lista = lista_crear();
    print_test("Lista vacía creada. Pruebas insertar", lista != NULL);

	//Prueba insertar/borrar elementos enteros
	prueba_insertar_borrar_elementos(lista);
    
    //Pruebas borde 
	print_test("lista vacía despues de insertar y borrar", lista_esta_vacia(lista));
    	
    print_test("Ver primer elemento lista vacía", lista_ver_primero(lista)== NULL);
    	
    print_test("Borrar primero  lista vacía despues de insertar y borrar", lista_borrar_primero(lista)== NULL);
    	
	lista_destruir(lista,NULL);	   	
}

bool prueba_lista_volumen_types_int(lista_t * lista,int cant_elements)
{
	int *vec_aux;
	
	vec_aux = malloc((size_t)cant_elements * sizeof(int));
	
	if(vec_aux == NULL) return false;
	
	bool bool_ok = true;
	bool bool_ok_ver = true;
	for (int i= 0; i < cant_elements; i++){
		vec_aux[i] = i; 
		bool_ok &= lista_insertar_ultimo(lista, &vec_aux[i]);
		bool_ok_ver &= (lista_ver_ultimo(lista) == &vec_aux[i]);		
	}
	
	print_test("Todos los elementos tipo INT insertados satisfactoriamente.", bool_ok);
	print_test("Todos los elementos tipo INT insertados y vistos satisfactoriamente.", bool_ok_ver);
	print_test("Se pudieron enlistar todos los elementos tipo INT.La lista no está vacía", !lista_esta_vacia(lista));
	print_test("El largo de la lista coincide con la cantidad de elementos insertados", lista_largo(lista) == cant_elements);
	

	if(bool_ok)
	{
		bool_ok = true;
		int * aux_pointer;

		for(int i = 0; i < cant_elements; i++)
		{
       		aux_pointer = lista_borrar_primero(lista);
	        	bool_ok &= (*aux_pointer == vec_aux[i]);
    		}		
		print_test("Todos los elementos tipo INT borrados satisfactoriamente.", bool_ok);
		print_test("lista vacía.Todos los elementos tipo INT desenlistados.", lista_esta_vacia(lista));
		print_test("Pruebas tipo INT.Ver primer elemento lista borrada vacía", lista_ver_primero(lista)== NULL);
		print_test("Pruebas tipo INT.Desenlistar lista nuevamente vacía", lista_borrar_primero(lista)== NULL);
	}
	
	free(vec_aux);
	
	return bool_ok;
}

static void prueba_lista_volumen(int max_volumen) {

    printf("3. INICIO DE PRUEBAS DE VOLUMEN\n");
	lista_t *lista = lista_crear();
	print_test("Todos los elementos INT enlistados y desenlistados satisfactoriamente.",prueba_lista_volumen_types_int(lista,max_volumen));
	
	lista_destruir(lista,NULL);
}

static void prueba_destruir_con_funcion_limpiar_entero(void)
{
	int cant_elements = 20;

    printf("5. INICIO DE PRUEBAS DESTRUIR CON FUNCION LIMPIAR ENTERO\n");

	lista_t *lista = lista_crear();
	int *vec_aux;
	
	vec_aux = malloc((size_t)cant_elements * sizeof(int));
	if(vec_aux == NULL)
		return;

	bool bool_ok = true;
	for (int i= 0; i < cant_elements; i++){
		vec_aux[i] = i; 
		bool_ok &= lista_insertar_ultimo(lista, &vec_aux[i]);
	}
	
	print_test("Lista con elementos.", !lista_esta_vacia(lista));
	lista_destruir(lista, limpiar_entero);
	print_test("Destruir lista (con funcion())", lista != NULL);
	
	free(vec_aux);
}

static void prueba_destruir_con_funcion_free(void)
{
 	int * vector_aux_int = malloc((size_t)5* sizeof(int));
 	char * vector_aux_char = malloc((size_t)5* sizeof(char));

	if(!vector_aux_int || !vector_aux_char)
		return;

	printf("4. INICIO DE PRUEBAS DESTRUIR CON FUNCION FREE\n");

	lista_t *lista = lista_crear();

	/* Pruebo enlistar los elementos */
	print_test("Se pudo insertar puntero INT", lista_insertar_ultimo(lista, vector_aux_int));
	
	print_test("Se pudo insertar puntero CHAR", lista_insertar_primero(lista, vector_aux_char));

	lista_destruir(lista, free);
	print_test("Pila destruida utilizando función free como parámetro", lista != NULL);
}

//Corta cuando sea mayor o igual a 15
bool sumar_mayor_igual_15(void* dato, void* extra)
{
	*(int*)extra += *(int*)dato;
	if(*(int*)extra >= 15) 
		return false;
		
	return true; 
}

//Suma todo 
bool sumar_todo(void* dato, void* extra)
{
	*(int*)extra += *(int*)dato;

	return true; 
}

static void prueba_lista_iterador_interno(void)
{
	int cant_elements = 10;
	int extra = 0;
	int acum = 0;
		
    printf("6. INICIO DE PRUEBAS DEL ITERADOR INTERNO DE LA LISTA\n");

	lista_t *lista = lista_crear();
	
	int *vec_aux;
	
	vec_aux = malloc((size_t)cant_elements * sizeof(int));
	
	if(!vec_aux)
		return ;
	
	bool bool_ok = true;
	for (int i= 0; i < cant_elements; i++){
		vec_aux[i] = i; 
		acum += i;
		bool_ok &= lista_insertar_ultimo(lista, &vec_aux[i]);
	}
	
	//Prueba sin corte 
	lista_iterar(lista,sumar_todo ,&extra);
	print_test("La suma de todos los números es igual a lo acumulado.", extra == acum);
	
	//Prueba con corte
	extra = 0;
	lista_iterar(lista,sumar_mayor_igual_15 ,&extra);
	print_test("Los números sumados son mayor o igual a 15", extra >= 15);
	
	free(vec_aux);
	lista_destruir(lista, NULL);
}

static void  prueba_lista_iterador_externo_insertar_principio(lista_t* lista,lista_iter_t* iter, int dato_int, int * p_int){
    lista = lista_crear();
    print_test("- Crear lista", lista != NULL);
    iter = lista_iter_crear(lista);
    print_test("- Crear iterador externo de la lista", iter != NULL);
    print_test("- Insertar en primera posición con iterador externo", lista_iter_insertar(iter, &dato_int));
    p_int = lista_ver_primero(lista);
    print_test("- Efectivamente se inserta al principio", dato_int == *p_int);
    lista_iter_destruir(iter);
    print_test("- Destruir iterador externo", true);
    lista_destruir(lista, NULL);
    print_test("- Destruir lista", true);
}


static void  prueba_lista_iterador_externo_insertar_final(lista_t* lista,lista_iter_t* iter, int nvec_int, int* vec_int, int dato_int, int* p_int){
    lista = lista_crear();
    print_test("- Crear lista", lista != NULL);
    iter = lista_iter_crear(lista);
    print_test("- Crear iterador externo de la lista", iter != NULL);
    bool ok = true;
    for(int i = 0; i < nvec_int; i++){
        ok &= lista_iter_insertar(iter, &vec_int[i]);
    }
    print_test("- Insertar varios enteros", ok);
    while(!lista_iter_al_final(iter)){
        lista_iter_avanzar(iter);
    }
    print_test("- Avanzar hasta el final", lista_iter_ver_actual(iter) == NULL);
    print_test("- Insertar en última posición con iterador externo", lista_iter_insertar(iter, &dato_int));
    p_int = lista_ver_ultimo(lista);
    print_test("- Efectivamente se inserta al final", dato_int == *p_int);
    lista_iter_destruir(iter);
    print_test("- Destruir iterador externo", true);
    lista_destruir(lista, NULL);
    print_test("- Destruir lista", true);
    
}

static void prueba_lista_iterador_externo_insertar_al_medio(lista_t* lista,lista_iter_t* iter, int nvec_int, int* vec_int, int dato_int, int* p_int, int n_aux){

    lista = lista_crear();
    print_test("- Crear lista", lista != NULL);
    iter = lista_iter_crear(lista);
    print_test("- Crear iterador externo de la lista", iter != NULL);
    bool ok = true;
    for(int i = 0; i < nvec_int; i++){
        ok &= lista_iter_insertar(iter, &vec_int[i]);
    }
    print_test("- Insertar varios enteros", ok);
    ok = true;
    for(int i = 0; i < n_aux; i++){
        ok &= lista_iter_avanzar(iter);        
    }
    print_test("- Avanzar hasta el medio", ok);
    print_test("- Insertar en el medio con iterador externo", lista_iter_insertar(iter, &dato_int));
    p_int = lista_iter_ver_actual(iter);
    print_test("- Efectivamente se inserta en el medio", dato_int == *p_int);
    lista_iter_destruir(iter);
    print_test("- Destruir iterador externo", true);
    lista_destruir(lista, NULL);
    print_test("- Destruir lista", true);
    
}

static void prueba_lista_iterador_externo_remover_primer_elemento(lista_t* lista,lista_iter_t* iter, int nvec_int, int* vec_int, int* p_int, int* p_int2){
    
    lista = lista_crear();
    print_test("- Crear lista", lista != NULL);
    iter = lista_iter_crear(lista);
    print_test("- Crear iterador externo de la lista", iter != NULL);
    bool ok = true;
    for(int i = 0; i < nvec_int; i++){
        ok &= lista_iter_insertar(iter, &vec_int[i]);
    }
    print_test("- Insertar varios enteros", ok);

    p_int = lista_ver_primero(lista);
    print_test("- Borrar primer elemento con iterador externo", lista_iter_borrar(iter) != NULL);
    p_int2 = lista_ver_primero(lista);
    print_test("- Al haber removido primero elemento con iterador externo cambia el primero", p_int != p_int2);
    lista_iter_destruir(iter);
    print_test("- Destruir iterador externo", true);
    lista_destruir(lista, NULL);
    print_test("- Destruir lista", true);
    
}

static void prueba_lista_iterador_externo_remover_ultimo_elemento(lista_t* lista,lista_iter_t* iter, int nvec_int, int* vec_int, int* p_int, int* p_int2){    

    lista = lista_crear();
    print_test("- Crear lista", lista != NULL);
    iter = lista_iter_crear(lista);
    print_test("- Crear iterador externo de la lista", iter != NULL);
    bool ok = true;
    for(int i = 0; i < nvec_int; i++){
        ok &= lista_iter_insertar(iter, &vec_int[i]);
    }
    print_test("- Insertar varios enteros", ok);
    for(int i = 0; i < nvec_int - 1; i++){
        lista_iter_avanzar(iter);
    }
    print_test("- Avanzar hasta el último elemento (no NULL)", lista_iter_ver_actual(iter) != NULL);
    p_int = lista_ver_ultimo(lista);
    print_test("- Borrar ultimo elemento con iterador externo", lista_iter_borrar(iter) != NULL);
    p_int2 = lista_ver_ultimo(lista);
    print_test("- Al haber removido ultimo elemento con iterador externo cambia el ultimo", p_int != p_int2);
    lista_iter_destruir(iter);
    print_test("- Destruir iterador externo", true);
    lista_destruir(lista, NULL);
    print_test("- Destruir lista", true);

}

static void prueba_lista_iterador_externo_remover_elemento_medio(lista_t* lista,lista_iter_t* iter, int nvec_int, int n_aux, int* vec_int, int* p_int, int* p_int2){       

    lista = lista_crear();
    print_test("- Crear lista", lista != NULL);
    iter = lista_iter_crear(lista);
    print_test("- Crear iterador externo de la lista", iter != NULL);
    bool ok = true;
    for(int i = 0; i < nvec_int; i++){
        ok &= lista_iter_insertar(iter, &vec_int[i]);
    }
    print_test("- Insertar varios enteros", ok);
    ok = true;
    for(int i = 0; i < n_aux; i++){
        ok &= lista_iter_avanzar(iter);        
    }
    print_test("- Avanzar hasta el medio", ok);
    p_int = lista_iter_ver_actual(iter);
    print_test("- Borrar elemento del medio con iterador externo", lista_iter_borrar(iter) != NULL);
    p_int2 = lista_iter_ver_actual(iter);
    print_test("- Verificar que elemento del medio borrado ya no existe", p_int != p_int2);
    lista_iter_destruir(iter);
    print_test("- Destruir iterador externo", true);
    lista_destruir(lista, NULL);
    print_test("- Destruir lista", true);
}


static void prueba_lista_iterador_externo(void){
    
    int dato_int = 50;
    int* p_int = NULL;
    int* p_int2 = NULL;
    int vec_int[] = {-1, 10, 33, 44, 55, 100};
    int nvec_int = 6;
    int n_aux = 3;
    
    lista_t* lista = NULL;
    lista_iter_t* iter = NULL;

    printf("7. INICIO DE PRUEBAS DEL ITERADOR EXTERNO DE LA LISTA\n");

/******************************************************************************************/
    printf("a) INSERTAR AL PRINCIPIO:\n");
    prueba_lista_iterador_externo_insertar_principio(lista, iter, dato_int, p_int);
    
/******************************************************************************************/
    printf("b) INSERTAR AL FINAL:\n");
    prueba_lista_iterador_externo_insertar_final(lista, iter, nvec_int, vec_int, dato_int, p_int);

/******************************************************************************************/
    printf("c) INSERTAR EN ALGUNA PARTE DEL MEDIO:\n");
    prueba_lista_iterador_externo_insertar_al_medio(lista, iter, nvec_int, vec_int, dato_int, p_int, n_aux);

/******************************************************************************************/
    printf("d) REMOVER PRIMER ELEMENTO CON ITERADOR CAMBIA EL PRIMERO DE LA LISTA:\n");
    prueba_lista_iterador_externo_remover_primer_elemento(lista, iter, nvec_int, vec_int, p_int, p_int2);
    
/******************************************************************************************/
    printf("e) REMOVER ULTIMO ELEMENTO CON ITERADOR CAMBIA EL ULTIMO DE LA LISTA:\n");   
    prueba_lista_iterador_externo_remover_ultimo_elemento(lista, iter, nvec_int,vec_int, p_int, p_int2);
    
/******************************************************************************************/
    printf("f) REMOVER ELEMENTO DEL MEDIO CON ITERADOR:\n");  
    prueba_lista_iterador_externo_remover_elemento_medio(lista, iter,nvec_int,n_aux,vec_int,p_int,p_int2);   
    
}

void destruir_elemento_pila_wrapper(void* elem) {
    pila_destruir(elem);
}

static void prueba_destruir_con_TDA_pila(void)
{
	void * element_pointer;
        int int_element = 5;
        pila_t * pila = pila_crear();

	printf("8. INICIO DE PRUEBAS DESTRUIR CON TDA pila\n");

        print_test("Pila creada satisfactoriamente", pila != NULL);

	element_pointer = &int_element;
	
	pila_apilar(pila, element_pointer);
	print_test("Se pudo apilar el elemento INT", !pila_esta_vacia(pila));
	print_test("Ver tope pila con un elemento INT",pila_ver_tope(pila));

	lista_t *lista = lista_crear();

	/* Pruebo enlistar los elementos */
	print_test("Se pudo insertar pila en la lista", lista_insertar_ultimo(lista, pila));
	
	lista_destruir(lista, destruir_elemento_pila_wrapper);
	print_test("Lista con elemento pila almacenado destruido utilizando función pila_destruir como parámetro", lista != NULL);
}

void pruebas_lista_estudiante(void){
	prueba_lista_vacia();
	prueba_insertar_borrar();
	prueba_lista_volumen(MAX_VOLUMEN);
	prueba_destruir_con_funcion_free();
	prueba_destruir_con_funcion_limpiar_entero();
	prueba_lista_iterador_interno();
    	prueba_lista_iterador_externo();
    	prueba_destruir_con_TDA_pila();
}

#ifndef CORRECTOR

int main(void){

    pruebas_lista_estudiante();
    return failure_count() > 0;     // Indica si fallo alguna prueba.
}

#endif
