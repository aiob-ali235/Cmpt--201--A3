/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "DB_impl.h"

int findValue(Table *table, int size, char *value){
    for(int i=0;i<size;i++){
        if(strcmp(table[i].value,value)==0)
            return table[i].id;
    }
    return -1;
}

int addValue(Table **table, int *size, char *value){
    int id = *size;
    *table = realloc(*table, (*size + 1)*sizeof(Table));
    (*table)[*size].id = id;
    (*table)[*size].value = strdup(value);
    (*size)++;
    return id;
}