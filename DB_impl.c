/* DB_impl.c
 *
 * This file contains helper functions used by the database.
 * It includes functions for searching and adding values
 * to lookup tables.
 *
 * Authors: Almoatassem Namroush, Aiob Ali, Kunwar Mahajan
 * Lab instructor: Ardy
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
    (*table)[*size].value = malloc(strlen(value) + 1);
    strcpy((*table)[*size].value, value);
    (*size)++;
    return id;
}