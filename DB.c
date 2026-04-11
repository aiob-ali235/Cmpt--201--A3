/* DB.c
 *
 * This file contains the main database implementation.
 * It handles importing data from CSV, exporting data,
 * counting entries, sorting, editing, and reporting.
 *
 * Authors: Almoatassem Namroush, Aiob Ali, Kunwar Mahajan
 * Lab instructor: Ardy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DB.h"
#include "DB_impl.h"

DataBase *Db = NULL;

void importDB(char *fileName) {
    FILE *fp;
    char line[1024];
    char *token;
    PicnicTable p;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        Db = NULL;
        return;
    }

    Db = malloc(sizeof(DataBase));
    if (Db == NULL) {
        fclose(fp);
        return;
    }

    memset(Db, 0, sizeof(DataBase));

    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {

        /* start every field with safe values */
        p.tableId = Db->picnicSize;
        p.siteId = 0;
        p.tableTypeId = -1;
        p.surfaceMaterialId = -1;
        p.structuralMaterialId = -1;
        p.streetAvenue = NULL;
        p.neighbourhoodId = 0;
        p.ward = NULL;
        p.latitude = NULL;
        p.longitude = NULL;
        p.ward = NULL;
        p.location = NULL;

        token = strtok(line, ",");
        if (token != NULL) {
            p.siteId = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            int id = findValue(Db->tableTypeTable, Db->tableTypeSize, token);
            if (id == -1) {
                id = addValue(&Db->tableTypeTable, &Db->tableTypeSize, token);
            }
            p.tableTypeId = id;
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            int id = findValue(Db->surfaceMaterialTable, Db->surfaceMaterialSize, token);
            if (id == -1) {
                id = addValue(&Db->surfaceMaterialTable, &Db->surfaceMaterialSize, token);
            }
            p.surfaceMaterialId = id;
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            int id = findValue(Db->structuralMaterialTable, Db->structuralMaterialSize, token);
            if (id == -1) {
                id = addValue(&Db->structuralMaterialTable, &Db->structuralMaterialSize, token);
            }
            p.structuralMaterialId = id;
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            p.streetAvenue = malloc(strlen(token) + 1);
            strcpy(p.streetAvenue, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            p.neighbourhoodId = atoi(token);
        }

        token = strtok(NULL, ",");
if (token != NULL) {
    int found = -1;
    int i;

    for (i = 0; i < Db->neighborhoodSize; i++) {
        if (Db->neighborhoodTable[i].id == p.neighbourhoodId) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        Db->neighborhoodTable = realloc(
            Db->neighborhoodTable,
            (Db->neighborhoodSize + 1) * sizeof(NeighbourhoodTable)
        );

        Db->neighborhoodTable[Db->neighborhoodSize].id = p.neighbourhoodId;
        Db->neighborhoodTable[Db->neighborhoodSize].name = malloc(strlen(token) + 1);
        strcpy(Db->neighborhoodTable[Db->neighborhoodSize].name, token);

        Db->neighborhoodSize++;
    }
}

        token = strtok(NULL, ",");
        if (token != NULL) {
            p.ward = malloc(strlen(token) + 1);
            strcpy(p.ward, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            p.latitude = malloc(strlen(token) + 1);
            strcpy(p.latitude, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            p.longitude = malloc(strlen(token) + 1);
            strcpy(p.longitude, token);
        }
        token = strtok(NULL, "\n");
        if (token != NULL) {
            p.location = malloc(strlen(token) + 1);
            strcpy(p.location, token);
        }
        Db->picnicTableTable = realloc(Db->picnicTableTable,
            (Db->picnicSize + 1) * sizeof(PicnicTable));

        Db->picnicTableTable[Db->picnicSize] = p;
        Db->picnicSize++;
    }

    fclose(fp);
}

void exportDB(char *fileName) {
    FILE *fp;
    int i;

    if (Db == NULL) return;

    fp = fopen(fileName, "w");
    if (fp == NULL) return;

    fprintf(fp, "Id,Table Type,Surface Material,Structural Material,Street / Avenue,Neighbourhood Id,Neighbourhood Name,Ward,Latitude,Longitude,Location\n");

    for (i = 0; i < Db->picnicSize; i++) {
        PicnicTable p = Db->picnicTableTable[i];

        fprintf(fp, "%d,", p.siteId);

        if (p.tableTypeId >= 0 && p.tableTypeId < Db->tableTypeSize)
            fprintf(fp, "%s,", Db->tableTypeTable[p.tableTypeId].value);
        else
            fprintf(fp, ",");

        if (p.surfaceMaterialId >= 0 && p.surfaceMaterialId < Db->surfaceMaterialSize)
            fprintf(fp, "%s,", Db->surfaceMaterialTable[p.surfaceMaterialId].value);
        else
            fprintf(fp, ",");

        if (p.structuralMaterialId >= 0 && p.structuralMaterialId < Db->structuralMaterialSize)
            fprintf(fp, "%s,", Db->structuralMaterialTable[p.structuralMaterialId].value);
        else
            fprintf(fp, ",");

        fprintf(fp, "%s,", p.streetAvenue ? p.streetAvenue : "");
        fprintf(fp, "%d,", p.neighbourhoodId);

        {
        int i;
        int found = 0;

        for (i = 0; i < Db->neighborhoodSize; i++) {
            if (Db->neighborhoodTable[i].id == p.neighbourhoodId) {
                fprintf(fp, "%s,", Db->neighborhoodTable[i].name);
                found = 1;
                break;
            }
        }

    if (!found) {
        fprintf(fp, ",");
    }
}

        fprintf(fp, "%s,", p.ward ? p.ward : "");
        fprintf(fp, "%s,", p.latitude ? p.latitude : "");
        fprintf(fp, "%s,", p.longitude ? p.longitude : "");

        fprintf(fp, "%s\n", p.location ? p.location : "\"\"");
    }

    fclose(fp);
}

int countEntries(char *memberName,char *value){
    int count=0;
    for(int i=0;i<Db->picnicSize;i++){
        if(Db->picnicTableTable[i].tableTypeId==atoi(value))
            count++;
    }
    return count;
}

void sortByMember(char *memberName){
    for(int i=0;i<Db->picnicSize;i++){
        for(int j=i+1;j<Db->picnicSize;j++){
            if(Db->picnicTableTable[i].tableTypeId > Db->picnicTableTable[j].tableTypeId){
                PicnicTable temp = Db->picnicTableTable[i];
                Db->picnicTableTable[i]=Db->picnicTableTable[j];
                Db->picnicTableTable[j]=temp;
            }
        }
    }
}

void editTableEntry(int tableID,char *memberName,char *value){
    for(int i=0;i<Db->picnicSize;i++){
        if(Db->picnicTableTable[i].tableId==tableID){
            Db->picnicTableTable[i].tableTypeId = atoi(value);
        }
    }
}

void reportByNeighbourhood(){
    printf("Report by neighbourhood\n");
}

void reportByWard(){
    printf("Report by ward\n");
}

void freeDB(){
    for (int i = 0; i < Db->picnicSize; i++) {
    free(Db->picnicTableTable[i].streetAvenue);
    free(Db->picnicTableTable[i].ward);
    free(Db->picnicTableTable[i].latitude);
    free(Db->picnicTableTable[i].longitude);
    free(Db->picnicTableTable[i].location);
}
}