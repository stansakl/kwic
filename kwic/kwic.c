#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kwic.h"
#include "kwicconst.h"

int main(int argc, char* argv[]) {
	printf("Program started.\n");

    if (argc == 1) {
        showFileArgumentError();
        exit(EXIT_FAILURE);
    }

    /* 
    * If the -f flag exists in argv[1], assume the next position is the filepath
    * Check to make sure there actually is something in argv[2]
    */
    if ((strstr(argv[1], "-f") != NULL) && (argv[2] != NULL)) { 
        char* filename = argv[2];
        char* fulltext;
        char* line;

        FILE *file = NULL;

        line = (char*)malloc(MAX_LINE_SIZE);
        fulltext = (char*)malloc(MAX_FULL_TEXT_SIZE);
        memset(line, '\0', MAX_LINE_SIZE);
        memset(fulltext, '\0', MAX_FULL_TEXT_SIZE);

        printf("Attempting to parse file %s\n", filename);
        fopen_s(&file, filename, "r");

        short lineCount = 0;

        while (!feof(file)) {
           
            fgets(line, 1000, file);
            strcat_s(fulltext, MAX_LINE_SIZE, line);            
            lineCount++;

            /* Clear the line before the next loop*/
            memset(line, '\0', MAX_LINE_SIZE);
        }

        printf("\nfulltext:\n%s\n", fulltext);

        free(line);
        free(fulltext);       
        fclose(file);
    }
    else {
        showFileArgumentError();
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void showFileArgumentError() {
    printf("ERROR %d: A file name is required!\n", ERR_FILE_REQUIRED);
}