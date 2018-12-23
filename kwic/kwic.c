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

    /****************************************************************************** 
     * If the -f flag exists in argv[1], assume the next position is the filepath *
     * Check to make sure there actually is something in argv[2]                  *
     * If there is, open the file, read it, and store the input locally.          * 
     ******************************************************************************/
    if ((strstr(argv[1], "-f") != NULL) && (argv[2] != NULL)) { 
        char* filename = argv[2];
        char* fulltext;
        char* line;
        int error = 0;
        FILE *file = NULL;

        line = (char*)malloc(MAX_LINE_SIZE);
        fulltext = (char*)malloc(MAX_FULL_TEXT_SIZE);
        memset(line, '\0', MAX_LINE_SIZE);
        memset(fulltext, '\0', MAX_FULL_TEXT_SIZE);

        printf("Attempting to parse file %s\n", filename);
        error = fopen_s(&file, filename, "r");
        if (error != 0) {
            printf("Error %d. File %s was not found. Exiting.\n", ERR_FILE_NOT_FOUND, filename);
            exit(EXIT_FAILURE);
        }

        short lineCount = 0;

        while (!feof(file)) {
           
            fgets(line, 1000, file);
			sortLine(line);
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

char* sortLine(char* lineToSort) {

	char* temp = (char*)malloc(MAX_LINE_SIZE);
	char* nextToken = (char*)malloc(MAX_LINE_SIZE);
	memset(nextToken, '\0', sizeof(*nextToken));
	char* tokens = malloc(sizeof(*tokens));
	memset(tokens, '\0', sizeof(*tokens));
	char* tempArray[100];
	memset(tempArray, '\0', 100);
	int arrayCounter = 0;
	//for(;;) {
	//*(tokens = strtok_s(lineToSort, " ", &nextToken));
	tempArray[0] = (strtok_s(lineToSort, " ", &nextToken));
	printf("tempArray[%d]: %s\n", arrayCounter, tempArray[arrayCounter]);

	while(1) {
		
		/*printf("Token: %s\n", tokens);
		printf("Context: %s\n", nextToken);*/
		arrayCounter++;
		if (arrayCounter == 100) break;
		tempArray[arrayCounter] = (strtok_s(NULL, " ", &nextToken));

		/*if (nextToken != '\0') {
			printf("Token: %s\n", tokens);
			printf("Next Token: %s\n", nextToken);
		}*/

	//	for (int i = 0; i < arrayCounter; i++) {
			printf("tempArray[%d]: %s\n", arrayCounter, tempArray[arrayCounter]);
	//	}
		if (*nextToken == '\0') break;

	}
	//TODO: The actual sorting
	
	return *tempArray;

}