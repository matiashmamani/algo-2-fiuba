#ifndef _STATUS_H
#define _STATUS_H

typedef enum {
    OK = 0,
    ERROR_CANTIDAD_PARAMETROS,
    ERROR_ABRIR_ARCHIVO
} status_t;

void imprimir_msj_error(status_t status);

#endif // _STATUS_H