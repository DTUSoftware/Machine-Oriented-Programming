//
// IO Operations - saving and loading
//

#ifndef MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_IO_H
#define MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_IO_H

#include "yukon.h"

typedef enum {
    CARDS,
    STATE
} FileType;

int validateFile(char *fileName, char *fileMode, FileType fileType, FILE *file);

int saveCards(char *filename);
int loadCards(char *filename, Card *cards);
int saveState(char *filename);
int loadState(char *filename);

#endif //MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_IO_H
