#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kwic.h"
#include "kwicconst.h"

typedef int BOOL;
const BOOL TRUE = 1;
const BOOL FALSE = 0;

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
		char* destination;
		destination = (char*)malloc(MAX_LINE_SIZE);
		memset(destination, '\0', MAX_LINE_SIZE);
		
        while (!feof(file)) {
           
            fgets(line, 1000, file);
			sortLine(line, destination);
		//	printf("Line: %s\tDestination: %s\n", line, destination);
            strcat_s(fulltext, MAX_LINE_SIZE, destination); 
            lineCount++;

            /* Clear the line before the next loop*/
			line = (char*)realloc(line, MAX_LINE_SIZE);
			destination = (char*)realloc(destination, MAX_LINE_SIZE);
            memset(line, '\0', MAX_LINE_SIZE);
			memset(destination, '\0', MAX_LINE_SIZE);
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

sortLine(char* lineToSort, char* destination) {

	char* nextToken;
	nextToken = (char*)calloc(MAX_LINE_SIZE, sizeof(nextToken));
	char* tempArray[100];
	tempArray[0] = calloc(100, sizeof(tempArray));
	memset(nextToken, '\0', sizeof(*nextToken));		
	memset(tempArray, '\0', 100);

	int arrayCounter = 0;	
	tempArray[0] = (strtok_s(lineToSort, " ", &nextToken));
	printf("tempArray[%d]: %s\n", arrayCounter, tempArray[arrayCounter]);
	
	while(TRUE) {
		
		arrayCounter++;
		if (arrayCounter == 100) break;
		tempArray[arrayCounter] = (strtok_s(NULL, " ", &nextToken));
		
		if (tempArray[arrayCounter] == '\0') break;
		printf("tempArray[%d]: %s\n", arrayCounter, tempArray[arrayCounter]);

		if (*nextToken == '\0') break;
	}

	char* temp;
	int result = 0;
	BOOL sorted = FALSE;

	while (sorted == FALSE) {
		sorted = TRUE;
		
		for (int i = 0; i < arrayCounter; i++) {
			result = strcmp(tempArray[i], tempArray[i + 1]);

			printf("Result: %d\t tempArray[%d]: %s, tempArray[%d]: %s\n\n",
				result, i, tempArray[i], i + 1, tempArray[i + 1]);

			if (result > 0) {
				sorted = FALSE;
				temp = tempArray[i + 1];
				tempArray[i + 1] = tempArray[i];
				tempArray[i] = temp;

				printf("After Swap:\nResult: %d\t tempArray[%d]: %s, tempArray[%d]: %s\n",
					result, i, tempArray[i], i + 1, tempArray[i + 1]);
			}
			else {
				printf("No swap required!\n");
			}
		}
	}

	for (int i = 0; i <= arrayCounter; i++)
	{
		printf("Sorted tempArray[%d]: %s\n", i, tempArray[i]);
	}

	//This loop is for modifying the destination
	for (int i = 0; i <= arrayCounter; i++) {
		strcat_s(destination, MAX_LINE_SIZE, tempArray[i]);

		if (i != arrayCounter) { /* Prevent the first character of a line from being a space*/
			strcat_s(destination, MAX_LINE_SIZE, " ");
		}
		else
			strcat_s(destination, MAX_LINE_SIZE, "\n");
	}
}