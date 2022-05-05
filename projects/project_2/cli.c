#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "commands.h"
#include "yukon.h"
#include "cards.h"
#include <malloc.h>

int getCardName(Card *card, char *cardName, bool reveal) {
    if (card && (card->revealed || reveal)) {
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

int getCardFromName(char *cardName, Card *card) {
    if (cardName == NULL) {
        return -1;
    }

//    printf("%s\n", cardName);
//    printf("cardName[0]: %c\n", cardName[0]);

    switch (cardName[0]) {
        case 'A':
            card->number = 1;
            break;
        case 'T':
            card->number = 10;
            break;
        case 'J':
            card->number = 11;
            break;
        case 'Q':
            card->number = 12;
            break;
        case 'K':
            card->number = 13;
            break;
        default:
            if (cardName[0] >= '0' && cardName[0] <= '9') {
                card->number = atoi(&cardName[0]);
            }
            else {
                return -2;
            }
            break;
    }
//    printf("cardName[1]: %c\n", cardName[1]);

    switch (cardName[1]) {
        case 'C':
            card->suit = CLUBS;
            break;
        case 'D':
            card->suit = DIAMONDS;
            break;
        case 'H':
            card->suit = HEARTS;
            break;
        case 'S':
            card->suit = SPADES;
            break;
        default:
            return -3;
    }

    return 0;
}

int drawCards(bool reveal) {
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
                    getCardName(cardColumns[j]->card, cardName, reveal);
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
            if (currentPhase != STARTUP && foundations[i] && foundations[i]->card) {
                getCardName(foundations[i]->card, foundationCard, reveal);
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
    // mads please fix my retardedness
    // fixed, good old stackoverflow uWu https://stackoverflow.com/questions/32313150/array-type-char-is-not-assignable
    char lastCommandName[11];
    switch (lastCommand->command) {
        case LD:
            strcpy(lastCommandName, "LD");
            break;
        case SW:
            strcpy(lastCommandName, "SW");
            break;
        case SI:
            strcpy(lastCommandName, "SI");
            break;
        case SR:
            strcpy(lastCommandName, "SR");
            break;
        case SD:
            strcpy(lastCommandName, "SD");
            break;
        case QQ:
            strcpy(lastCommandName, "QQ");
            break;
        case P:
            strcpy(lastCommandName, "P");
            break;
        case Q:
            strcpy(lastCommandName, "Q");
            break;
        case MOVE:
            // TODO: use move data instead
            strcpy(lastCommandName, "MOVE");
            break;
        case U:
            strcpy(lastCommandName, "U");
            break;
        case R:
            strcpy(lastCommandName, "R");
            break;
        case S:
            strcpy(lastCommandName, "S");
            break;
        case L:
            strcpy(lastCommandName, "L");
            break;
        default:
            strcpy(lastCommandName, "");
            break;
    }

    if (lastCommand->command != SW) {
        drawCards(false);
    }
    printf("\n");

    printf("Last Command: %s\n", lastCommandName);
    char status[30];
    char unknownStatusFormat[] = "UNKNOWN ERROR (Code: %d)";
    switch (lastCommand->status) {
        case 0:
            strcpy(status, "OK");
            break;
        case -1:
            strcpy(status, "ERROR");
            break;
        case 400:
            // bad request
            strcpy(status, "Unknown Command");
            break;
        default:
            sprintf(status, unknownStatusFormat, lastCommand->status);
            break;
    }
    printf("Message: %s\n", status);

    printf("INPUT > ");
    fflush(stdout);
    char command[110];
    fgets(command, 110, stdin);
    printf("\n");

    // remove trailing newline, if existing
    if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')) {
        command[strlen(command) - 1] = '\0';
    }

    CommandNode commandNode = {.command = NONE};
    int statusCode = -1;
    if (strstr(command, "LD") != NULL) {
        if (currentPhase == STARTUP) {
            commandNode.command = LD;
            if (strstr(command, " ") != NULL) {
                char *arg = strtok(command, " ");
                char path[100];
                while (arg != NULL) {
                    strcpy(path, arg);
                    arg = strtok(NULL, " ");
                }
                statusCode = LDCommand(path);
            } else { statusCode = LDCommand(NULL); }
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }

    } else if (strstr(command, "SW") != NULL) {
        commandNode.command = SW;
        statusCode = SWCommand();
    } else if (strstr(command, "SI") != NULL) {
        //TODO fix this at some point idk when, but please let anyone but me fix it :)

        if (currentPhase == STARTUP) {
            commandNode.command = SI;
            if (strstr(command, " ") != NULL) {
                char *arg = strtok(command, " ");
                int integer;
                while (arg != NULL) {
                    sscanf(arg, "%d", &integer);
                    arg = strtok(NULL, " ");
                }
                statusCode = SICommand(integer);
            } else { statusCode = SICommand(52/2); }

        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strstr(command, "SR") != NULL) {
        if (currentPhase == STARTUP) {
            commandNode.command = SR;
            statusCode = SRCommand();
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strstr(command, "SD") != NULL) {
        if (currentPhase == STARTUP) {
            commandNode.command = SD;
            if (strstr(command, " ") != NULL) {
                char *arg = strtok(command, " ");
                char path[100];
                while (arg != NULL) {

                    strcpy(path, arg);
                    arg = strtok(NULL, " ");
                }
                statusCode = SDCommand(path);
            } else { statusCode = SDCommand(NULL); }
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strstr(command, "QQ") != NULL) {
        if (currentPhase == STARTUP) {
            commandNode.command = QQ;
            statusCode = QQCommand();
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strstr(command, "P") != NULL) {
        if (currentPhase == STARTUP) {
            commandNode.command = P;
            statusCode = PCommand();
        } else {
            printf("Command only available in the STARTUP phase!\n");
        }
    } else if (strstr(command, "Q") != NULL) {
        if (currentPhase == PLAY) {
            commandNode.command = Q;
            statusCode = QCommand();
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    // Move command
    } else if (strchr(command, '-') != NULL && strchr(command, '>') != NULL) {
        if (currentPhase == PLAY) {
            commandNode.command = MOVE;
            // TODO: add data to commandNode
            if (strchr(command, ':') != NULL) {
                statusCode = MCommand(command, false);
            }
            else {
                statusCode = MCommand(command, true);
            }
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strstr(command, "U") != NULL) {
        if (currentPhase == PLAY) {
            commandNode.command = U;
            statusCode = UCommand();
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strstr(command, "R") != NULL) {
        if (currentPhase == PLAY) {
            commandNode.command = R;
            statusCode = RCommand();
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strstr(command, "S") != NULL) {
        if (currentPhase == PLAY) {
            commandNode.command = S;
            if (strstr(command, " ") != NULL) {
                char *arg = strtok(command, " ");
                char path[100];
                while (arg != NULL) {
                    strcpy(path, arg);
                    arg = strtok(NULL, " ");
                }
                statusCode = SCommand(path);
            } else { statusCode = SCommand(NULL); }
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strstr(command, "L") != NULL) {
        if (currentPhase == PLAY) {
            commandNode.command = L;
            if (strstr(command, " ") != NULL) {
                char *arg = strtok(command, " ");
                char path[100];
                while (arg != NULL) {
                    strcpy(path, arg);
                    arg = strtok(NULL, " ");
                }
                statusCode = LCommand(path);
            }
        } else {
            printf("Command only available in the PLAY phase!\n");
        }
    } else if (strstr(command, "DEBUG") != NULL) {
        switchCardStorage();
    }
    else {
        statusCode = 400;
    }

    // Add command to command history
    if (commandNode.command != NONE) {
        commandNode.status = statusCode;
        if (commandNode.command == MOVE) {
            commandNode.prev = moveHistory;
            moveHistory->next = &commandNode;
            moveHistory = &commandNode;
        }
        lastCommand = &commandNode;
    }
    else {
        lastCommand->status = statusCode;
    }

    return statusCode;
};