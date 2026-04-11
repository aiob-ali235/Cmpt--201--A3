/* dashboard.c
 *
 * This file contains the main program.
 * It provides a menu interface for the user
 * to interact with the database.
 *
 * Authors: Almoatassem Namroush, Aiob Ali, Kunwar Mahajan
 * Lab instructor: Ardy
 */


#include <stdio.h>
#include <string.h>
#include "DB.h"

int main(int argc, char *argv[]) {
    int option;

    if (argc < 3) {
        printf("Usage: ./dashboard -c file.csv\n");
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        importDB(argv[2]);

        if (Db == NULL) {
            printf("Could not open file\n");
            return 1;
        }
    }
    else if (strcmp(argv[1], "-b") == 0) {
        importDB(argv[2]);

        if (Db == NULL) {
            printf("Could not open file\n");
            return 1;
        }
    }
    else {
        printf("Invalid option\n");
        return 1;
    }

    while (1) {
        printf("1 Export\n");
        printf("2 Count\n");
        printf("3 Sort\n");
        printf("4 Exit\n");

        scanf("%d", &option);

        if (option == 1) {
            exportDB("out.csv");
        }
        else if (option == 2) {
            printf("%d\n", countEntries("tt", "1"));
        }
        else if (option == 3) {
            sortByMember("tt");
        }
        else if (option == 4) {
            break;
        }
    }

    freeDB();
    return 0;
}