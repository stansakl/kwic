#include <stdio.h>
#include <string.h>
#include "kwicconst.h"

int main(int argc, char* argv[]) {
	printf("Program started.\n");

    if (argc == 1) {
        printf("A file name is required!\n");
        return ERR_FILE_REQUIRED;
    }

    printf("Parsing arguments.\n");

    if (strstr(argv[1], "-f") != NULL) {
        printf("Found file argument flag");
        char* filename = argv[2];
        printf("Parsing file %s\n", filename);
    }

    return SUCCESS;
}