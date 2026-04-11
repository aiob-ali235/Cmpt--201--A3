#include <stdio.h>
#include "../DB.h"

int main(){

    printf("Running test...\n");

    importDB("PicnicTableSmall.csv");

    int count = countEntries("tt", "1");
    printf("Count result: %d\n", count);

    sortByMember("tt");

    exportDB("test_output.csv");

    freeDB();

    printf("Test finished\n");

    return 0;
}