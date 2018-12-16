#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kwicconst.h"

int main(int argc, char* argv[]) {
	printf("Program started.\n");

    if (argc == 1) {
        printf("ERROR %d: A file name is required!\n", ERR_FILE_REQUIRED);
        exit(EXIT_FAILURE);
    }

    printf("Parsing arguments.\n");

    if (strstr(argv[1], "-f") != NULL) {
        char* filename = argv[2];
        printf("Attempting to parse file %s\n", filename);

        FILE *file = NULL;
        
        fopen_s(&file, filename, "r");
        char line[100];
       
        while (!feof(file)) {
            if (fgets(line, (sizeof(line)), file)) {
                printf("%s", line);
            }
        }

        fclose(file);
    }

    return EXIT_SUCCESS;
}