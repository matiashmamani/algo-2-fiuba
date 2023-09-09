#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

bool es_numero(char arg_tam[]){
    
    for(int i = 0; i < strlen(arg_tam); i++){
        if(!isdigit(arg_tam[i])){
            return false;
        }
    }

    return true;
}