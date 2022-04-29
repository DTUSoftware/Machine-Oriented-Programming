//
// IO Operations - saving and loading
//

#include "io.h"


int validateFilename(char *filename) {
    return 0;
}

int saveCards(char *filename) {
    return 0;
}
int loadCards(char *filename, Card *cards) {
    // validate filename
    int filenameValid = validateFilename(filename);
    if (filenameValid != 0) {
        return filenameValid;
    }

    // load cards from file into cards array

    return 0;
}
int saveState(char *filename) {
    return 0;
}
int loadState(char *filename) {
    // validate filename
    int filenameValid = validateFilename(filename);
    if (filenameValid != 0) {
        return filenameValid;
    }

    // load state from state file into the columns and foundations
    return 0;
}
