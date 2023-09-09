#include <stdio.h>
#include "status.h"

const char *status_msj[] = {
    "Ok",
    "Error: Cantidad erronea de parametros",
    "Error: archivo fuente inaccesible"
};

void imprimir_msj_error(status_t status){
    fprintf(stderr, "%s\n", status_msj[status]);
}