#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "commands.h"

int drawCards() {
    return 0;
};

int readCommand() {
    char command[11];
    scanf("%s", &command);
    if (strcmp(command, "LD") == 0) {
        char filename[20];
        scanf("%s", &filename);
        return LDCommand(filename);
    }
    else if (strcmp(command, "SI") == 0) {
        return SWCommand();
    }
    else if (strcmp(command, "SR") == 0) {
        return SRCommand();
    }
    else if (strcmp(command, "SD") == 0) {
        char filename[20];
        scanf("%s", &filename);
        return SDCommand(filename);
    }
    else if (strcmp(command, "QQ") == 0) {
        return QQCommand();
    }
    else if (strcmp(command, "P") == 0) {
        return PCommand();
    }
    else if (strcmp(command, "Q") == 0) {
        return QCommand();
    }
    else if (strchr(command, ':') != NULL && strchr(command, '-') != NULL && strchr(command, '>') != NULL) {
        return MCommand(command);
    }
    else if (strcmp(command, "U") == 0) {
        return UCommand();
    }
    else if (strcmp(command, "R") == 0) {
        return RCommand();
    }
    else if (strcmp(command, "S") == 0) {
        char filename[20];
        scanf("%s", &filename);
        return SCommand(filename);
    }
    else if (strcmp(command, "L") == 0) {
        char filename[20];
        scanf("%s", &filename);
        return LDCommand(filename);
    }
    else return -1;
};