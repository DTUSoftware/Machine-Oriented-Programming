//
// IO Operations - saving and loading
//

#include <sys/stat.h>
#include <malloc.h>
#include "io.h"

// validate whether the file is open
// file is the output of function
int validateFile(char *fileName, char *fileMode, FileType fileType, FILE *file) {
    file = fopen(fileName, fileMode);
    if (!file) {
        return -1;
    }

    struct stat sb;
    if (stat(fileName, &sb) == -1) {
        return -2;
    }

    // validate the file if the mode is not write
    if (!strcmp(fileMode, "w")) {
        char *file_contents = malloc(sb.st_size);
        switch (fileType) {
            case CARDS:
                while (fscanf(file, "%[^\n] ", file_contents) != EOF) {
                    Card *card = NULL;
                    // validate if the line is a card
                    if (card == NULL) {
                        return -3;
                    }
                }
                break;
            case STATE:

                break;
            default:
                printf("what the fuck is this filetype??\n");
                return -1;
        }
        free(file_contents);
    }
    rewind(file);

    return 0;
}

int saveCards(char *filename) {
    // get and validate file
    FILE *file = NULL;
    int fileValid = validateFile(filename, "w", CARDS, file);
    if (fileValid != 0) {
        return fileValid;
    }
    fclose(file);
    return 0;
}

int loadCards(char *filename, Card *cards) {
    // get and validate file
    FILE *file = NULL;
    int fileValid = validateFile(filename, "r", CARDS, file);
    if (fileValid != 0) {
        return fileValid;
    }

    // load cards from file into cards array

    fclose(file);
    return 0;
}

int saveState(char *filename) {
    // get and validate file
    FILE *file = NULL;
    int fileValid = validateFile(filename, "w", STATE, file);
    if (fileValid != 0) {
        return fileValid;
    }

    fclose(file);
    return 0;
}

int loadState(char *filename) {
    // get and validate file
    FILE *file = NULL;
    int fileValid = validateFile(filename, "r", STATE, file);
    if (fileValid != 0) {
        return fileValid;
    }

    // load state from state file into the columns and foundations
    fclose(file);
    return 0;
}
