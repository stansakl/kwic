#include <stdio.h>
#include "kwicconst.h"

int main(int argc, char* argv[]) {
	printf("Program started.\n");

    if (argc == 1) {
        printf("A file name is required!\n");
        return ERR_FILE_REQUIRED;
    }

    return SUCCESS;
}