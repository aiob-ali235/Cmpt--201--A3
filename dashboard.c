/*
 * dashboard.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
*/

//You may include other original headers as you see fit
#include <stdio.h>
#include <string.h>
#include "DB.h"

int main(int argc,char *argv[]){
    if(strcmp(argv[1],"-c")==0){
        importDB(argv[2]);
    }

    int option;
    while(1){
        printf("1 Export\n2 Count\n3 Sort\n4 Exit\n");
        scanf("%d",&option);

        if(option==1){
            exportDB("out.csv");
        }
        else if(option==2){
            printf("%d\n",countEntries("tt","1"));
        }
        else if(option==3){
            sortByMember("tt");
        }
        else break;
    }

    freeDB();
    return 0;
