#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux;

    aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    int max_i = n - 1;

    if(!n) return -1;

    for(int i = n - 1; i >= 0; i--){
        if (vector[i] >= vector[max_i]){
            max_i = i;
        }
    }

    return max_i;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {

    for(int i = 0; i < n1 && i < n2; i++){
        if(vector1[i] < vector2[i]) return -1;
        if(vector1[i] > vector2[i]) return 1;
    }

    if(n1 < n2) return -1;  
    if(n1 > n2) return 1;  
    
    // n1 == n2
    return 0;
}


void seleccion(int vector[], int n) {
    int max_i;

    // n == 0 o n == 1
    if(n < 2) return;

    for(int i = n - 1; i >= 0; i--){
        max_i = maximo(vector, i + 1);
        swap(vector + i, vector + max_i);
    }

}