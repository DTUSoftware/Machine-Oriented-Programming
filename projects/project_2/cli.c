#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "commands.h"
#include "yukon.h"
#include "cards.h"
#include <stdio.h>

int getCardName(Card *card, char *cardName, bool debug) {
    if (card && (card->revealed || debug)) {
        switch (card->number) {
            case 1:
                cardName[0] = 'A';
                break;
            case 10:
                cardName[0] = 'T';
                break;
            case 11:
                cardName[0] = 'J';
                break;
            case 12:
                cardName[0] = 'Q';
                break;
            case 13:
                cardName[0] = 'K';
                break;
            default:
                cardName[0] = card->number + '0';
                break;
        }
        switch (card->suit) {
            case CLUBS:
                cardName[1] = 'C';
                break;
            case DIAMONDS:
                cardName[1] = 'D';
                break;
            case HEARTS:
                cardName[1] = 'H';
                break;
            case SPADES:
                cardName[1] = 'S';
                break;
        }
    }
    return 0;
};

int drawCards() {
    bool debug = false;
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\n");
    bool activeColumns[7] = {true, true, true, true, true, true, true};

    CardNode *cardColumns[7];
    for (int i = 0; i < 7; i++) {
        cardColumns[i] = columns[i];
    }

    // keep looping until all columns are done printing
    int inactiveCount = 0;
    for (int i = 0; true; i++) {
        // loop through each column and foundation
        for (int j = 0; j < 7; j++) {
            // print the columns
            if (activeColumns[j]) {
                // check if the current item in the column is not null
                if (cardColumns[j] && cardColumns[j]->card) {
                    char cardName[] = "[]";
                    getCardName(cardColumns[j]->card, cardName, debug);
                    printf("%s\t", cardName);
                    if (cardColumns[j]->next != NULL) {
                        cardColumns[j] = cardColumns[j]->next;
                    } else {
                        activeColumns[j] = false;
                        inactiveCount++;
                    }
                } else {
                    activeColumns[j] = false;
                    inactiveCount++;
                    printf("  \t");
                }
            } else {
                printf("  \t");
            }
        }
        // print the foundations
        if (i < 4) {
            char foundationCard[] = "[]";
            if (foundations[i] && foundations[i]->card) {
                getCardName(foundations[i]->card, foundationCard, debug);
            }
            printf("\t%s\tF%d\n", foundationCard, i + 1);
        } else {
            printf("\n");
            if (inactiveCount >= 7) {
                break;
            }
        }

    }
    return 0;
};

int readCommand() {
    printf("\n");
    // mads please fix my retardedness
    // fixed, good old stackoverflow uWu https://stackoverflow.com/questions/32313150/array-type-char-is-not-assignable
    char lastCommand[11];
    switch (commandHistory->command) {
        case LD:
            strcpy(lastCommand, "LD");
            break;
        case SW:
            strcpy(lastCommand, "SW");
            break;
        case SI:
            strcpy(lastCommand, "SI");
            break;
        case SR:
            strcpy(lastCommand, "SR");
            break;
        case SD:
            strcpy(lastCommand, "SD");
            break;
        case QQ:
            strcpy(lastCommand, "QQ");
            break;
        case P:
            strcpy(lastCommand, "P");
            break;
        case Q:
            strcpy(lastCommand, "Q");
            break;
        case MOVE:
            // TODO: use move data instead
            strcpy(lastCommand, "MOVE");
            break;
        case U:
            strcpy(lastCommand, "U");
            break;
        case R:
            strcpy(lastCommand, "R");
            break;
        case S:
            strcpy(lastCommand, "S");
            break;
        case L:
            strcpy(lastCommand, "L");
            break;
        default:
            strcpy(lastCommand, "");
            break;
    }
    printf("Last Command: %s\n", lastCommand);
    char status[10];
    switch (commandHistory->status) {
        case 0:
            strcpy(status, "OK");
            break;
        case -1:
            strcpy(status, "ERROR");
            break;
        default:
            strcpy(status, "UNKNOWN");
            break;
    }
    printf("Message: %s\n", status);

    printf("INPUT > ");
    fflush(stdout);
    char command[50];
    scanf("%s", &command);
    printf("\n");
    CommandNode commandNode = {.command = NONE};
    int statusCode = -1;
    if (strcmp(command, "LD") == 0) {
        if (currentPhase == STARTUP) {
            commandNode.command = LD;
            if (strcmp(command, " ") == 0) {
                char *arg = strtok(command, " ");
                char path[40];
                while (arg != NULL) {

                    strcpy(path, arg);
                    arg = strtok(NULL, " ");
                }
                statusCode = LDCommand(path);
            } else { statusCode = LDCommand(NULL); }
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }

    } else if (strcmp(command, "SW") == 0) {
        commandNode.command = SW;
        statusCode = SWCommand();
    } else if (strcmp(command, "SI") == 0) {
        //TODO fix this at some point idk when, but please let anyone but me fix it :)

        if (currentPhase == STARTUP) {
            commandNode.command = SI;
            if (strcmp(command, " ") == 0) {
                char *arg = strtok(command, " ");
                int integer;
                while (arg != NULL) {

                    sscanf(arg, "%d", &integer);
                    arg = strtok(NULL, " ");
                }
                statusCode = SICommand(integer);
            } else { statusCode = SICommand(NULL); }

        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strcmp(command, "SR") == 0) {
        if (currentPhase == STARTUP) {
            commandNode.command = SR;
            statusCode = SRCommand();
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strcmp(command, "SD") == 0) {
        if (currentPhase == STARTUP) {
            commandNode.command = SD;
            char filename[20];
            scanf("%s", &filename);
            statusCode = SDCommand(filename);
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strcmp(command, "QQ") == 0) {
        if (currentPhase == STARTUP) {
            commandNode.command = QQ;
            statusCode = QQCommand();
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strcmp(command, "P") == 0) {
        if (currentPhase == STARTUP) {
            commandNode.command = P;
            statusCode = PCommand();
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strcmp(command, "Q") == 0) {
        if (currentPhase == PLAY) {
            commandNode.command = Q;
            statusCode = QCommand();
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strchr(command, ':') != NULL && strchr(command, '-') != NULL && strchr(command, '>') != NULL) {
        if (currentPhase == PLAY) {
            commandNode.command = MOVE;
            // TODO: add data to commandNode
            statusCode = MCommand(command);
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strcmp(command, "U") == 0) {
        if (currentPhase == PLAY) {
            commandNode.command = U;
            statusCode = UCommand();
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strcmp(command, "R") == 0) {
        if (currentPhase == PLAY) {
            commandNode.command = R;
            statusCode = RCommand();
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strcmp(command, "S") == 0) {
        if (currentPhase == PLAY) {
            commandNode.command = S;
            char filename[20];
            scanf("%s", &filename);
            statusCode = SCommand(filename);
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strcmp(command, "L") == 0) {
        if (currentPhase == PLAY) {
            commandNode.command = L;
            char filename[20];
            scanf("%s", &filename);
            statusCode = LCommand(filename);
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strcmp(command, "DEBUG") == 0) {
        switchCardStorage();
    }

    // Add command to command history
    if (commandNode.command != NONE) {
        commandNode.status = statusCode;
        commandNode.prev = commandHistory;
        commandHistory->next = &commandNode;
        commandHistory = &commandNode;
    }

    return statusCode;
};