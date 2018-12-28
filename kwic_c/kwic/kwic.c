/*
BSD 2 - Clause License

Copyright(c) 2018, Stan Sakl
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met :

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kwic.h"
#include "kwicconst.h"

typedef int BOOL;
const BOOL TRUE = 1;
const BOOL FALSE = 0;

int main(int argc, char* argv[]) {

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
			printf("Input line: %s\n", line);
			sortLine(line, destination);
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

/* Performs a Bubble Sort on lineToSort and stores the results in destination. */
void sortLine(char* lineToSort, char* destination) {

	char* nextToken;
	nextToken = (char*)calloc(MAX_LINE_SIZE, sizeof(nextToken));
	char* tempArray[100];
	tempArray[0] = calloc(100, sizeof(tempArray));
	memset(nextToken, '\0', sizeof(*nextToken));		
	memset(tempArray, '\0', MAX_LINE_SIZE);

	short arrayCounter = 0;	
	tempArray[0] = (strtok_s(lineToSort, " ", &nextToken));
	
	while(*nextToken != '\0') {
		arrayCounter++;
		tempArray[arrayCounter] = (strtok_s(NULL, " ", &nextToken));
	}

	char* temp;
	short result = 0;
	BOOL sorted = FALSE;

	while (sorted == FALSE) {
		sorted = TRUE;
		
		for (short i = 0; i < arrayCounter; i++) {
			result = strcmp(tempArray[i], tempArray[i + 1]);

			if (result > 0) {
				sorted = FALSE;
				temp = tempArray[i + 1];
				tempArray[i + 1] = tempArray[i];
				tempArray[i] = temp;
			}
		}
	}

	//This loop is for modifying the destination
	for (int i = 0; i <= arrayCounter; i++) {
		
		char* newLine = (strstr(tempArray[i], "\n"));

		if (newLine != NULL) {
			int length = (int)strlen(tempArray[i]);

			for (int j = 0; j < length; j++) {

				if (tempArray[i][j] == '\n') {
					tempArray[i][j] = '\0';
				}
			}
		}
		strcat_s(destination, MAX_LINE_SIZE, tempArray[i]);

		if (i != arrayCounter) { /* Prevent the first character of a line from being a space*/
			strcat_s(destination, MAX_LINE_SIZE, " ");
		}
		else
			strcat_s(destination, MAX_LINE_SIZE, "\n");
	}
}