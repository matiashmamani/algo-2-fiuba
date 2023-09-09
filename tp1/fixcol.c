#define MIN_ARGS 2
#define MAX_ARGS 3
#define POS_TAMANIO 1
#define POS_ARCHIVO 2
#define MODO_LECTURA "r"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status.h"
#include "utils.h"

status_t validar_args(int argc, char *argv[]){

    if(argc < MIN_ARGS || argc > MAX_ARGS){
        return ERROR_CANTIDAD_PARAMETROS;
    }

    if(!es_numero(argv[POS_TAMANIO])){
        return ERROR_CANTIDAD_PARAMETROS;
    }

    return OK;
}

status_t abrir_stream(int argc, char nombre_archivo[], FILE **stream){

    if(argc == MIN_ARGS){
        *stream = stdin;
        return OK;
    }

    *stream = fopen(nombre_archivo, MODO_LECTURA);
 
    if(*stream == NULL){
        return ERROR_ABRIR_ARCHIVO;
    }

    return OK;
}

void fixcol(int tam_buffer, FILE *stream){
    
    if(!tam_buffer) return;
    
    // Sumo 1 por el '\0'
    char *cadena = malloc(sizeof(char)*((size_t)tam_buffer + 1));

    while(fgets(cadena, tam_buffer + 1, stream) != NULL){
        
        size_t ultimo = strlen(cadena) - 1;

        // Corrijo si ultimo caracter es '\n'
        if(cadena[ultimo] == '\n'){
            cadena[ultimo] = '\0';
        }

        // Corrijo si primer caracter es '\n'
        if(cadena[0] == '\n'){
            cadena[0] = '\0';
        }        
        
        // Valido nuevo largo (pudo haber cambiado algun '\0' en los IFs)
        if(strlen(cadena)){        
            fprintf(stdout, "%s\n", cadena);
        }
    }

    free(cadena);
}

void cerrar_stream(FILE *stream){

    if(stream != stdin){
        fclose(stream);
    }
}

/* *****************************************************************
 *                    FUNCION PRINCIPAL (MAIN)
 * *****************************************************************/

int main(int argc, char *argv[]){

    status_t status;
    FILE *stream;

    status = validar_args(argc, argv);

    if(status != OK){
        imprimir_msj_error(status);
        return EXIT_FAILURE;
    }

    status = abrir_stream(argc, argv[POS_ARCHIVO], &stream);

    if(status != OK){
        imprimir_msj_error(status);
        return EXIT_FAILURE; 
    }
    
    fixcol(atoi(argv[POS_TAMANIO]), stream);
    
    cerrar_stream(stream);

    return EXIT_SUCCESS;
}