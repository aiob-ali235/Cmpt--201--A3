/* DB.h
 *
 * This file defines the public interface of the database.
 * It includes all data structures and function prototypes
 * used by the program.
 *
 * Authors: Almoatassem Namroush, Aiob Ali, Kunwar Mahajan
 * Lab instructor: Ardy
 */

#ifndef DB_H
#define DB_H

#define INIT_SIZE 5

/* =========================
   DEFINE STRUCTS FIRST
   ========================= */

typedef struct {
    int id;
    char *value;
} Table;

typedef struct {
    int id;
    char *name;
} NeighbourhoodTable;

typedef struct {
    int tableId;
    int siteId;

    int tableTypeId;
    int surfaceMaterialId;
    int structuralMaterialId;

    char *streetAvenue;

    int neighbourhoodId;
    char *ward;

    char *latitude;
    char *longitude;
    char *location;

} PicnicTable;

/* =========================
   DATABASE STRUCT
   ========================= */

typedef struct {

    Table *tableTypeTable;
    int tableTypeSize;

    Table *surfaceMaterialTable;
    int surfaceMaterialSize;

    Table *structuralMaterialTable;
    int structuralMaterialSize;

    NeighbourhoodTable *neighborhoodTable;
    int neighborhoodSize;

    PicnicTable *picnicTableTable;
    int picnicSize;

} DataBase;

/* =========================
   GLOBAL
   ========================= */

extern DataBase *Db;

/* =========================
   FUNCTIONS
   ========================= */

void importDB(char *fileName);
void exportDB(char *fileName);
int countEntries(char *memberName, char *value);
void sortByMember(char *memberName);
void editTableEntry(int tableID, char *memberName, char *value);
void reportByNeighbourhood();
void reportByWard();
void freeDB();

#endif