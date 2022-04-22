#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "commands.h"
#include "yukon.h"
#include <stdio.h>

int getCardName(Card card, char *cardName) {
    if (card.revealed) {
        switch (card.number) {
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
                cardName[0] = card.number+'0';
                break;
        }
        switch (card.suit) {
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

int drawCards(CardNode *_columns, CardNode *_foundations) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\n");
    bool activeColumns[7] = {true, true, true, true, true, true, true};

    CardNode columnCards[7];
    for (int i = 0; i < 7; i++) {
        columnCards[i] = _columns[i];
    }

    // keep looping until all columns are done printing
    int inactiveCount = 0;
    for (int i = 0; true; i++) {
        // loop through each column and foundation
        for (int j = 0; j < 7; j++) {
            // print the columns
            if (activeColumns[j]) {
                // check if the current item in the column is not null
                if (&columnCards[j] != NULL) {
                    char cardName[] = "[]";
                    getCardName(columnCards[j].card, cardName);
                    printf("%s\t", cardName);

                    if (columnCards[j].next != NULL) {
                        columnCards[j] = *columnCards[j].next;
                    }
                    else {
                        activeColumns[j] = false;
                        inactiveCount++;
                    }
                }
                else {
                    activeColumns[j] = false;
                    inactiveCount++;
                    printf("  \t");
                }
            }
            else {
                printf("  \t");
            }
        }
        // print the foundations
        if (i < 4) {
            char foundationCard[] = "[]";
            if (&_foundations[i] != NULL) {
                getCardName(_foundations[i].card, foundationCard);
            }
            printf("\t%s\tF%d\n", foundationCard, i+1);
        }
        else {
            printf("\n");
            if (inactiveCount >= 7) {
                break;
            }
        }

    }
    return 0;
};

int readCommand() {
    // TODO: mads please fix my retardedness
    char lastCommand[] = "           ";
    switch (commandHistory->command) {
        case LD:
            lastCommand[0] = 'L';
            lastCommand[1] = 'D';
            break;
        case SW:
            lastCommand[0] = 'S';
            lastCommand[1] = 'W';
            break;
        case SI:
            lastCommand[0] = 'S';
            lastCommand[1] = 'I';
            break;
        case SR:
            lastCommand[0] = 'S';
            lastCommand[1] = 'R';
            break;
        case SD:
            lastCommand[0] = 'S';
            lastCommand[1] = 'D';
            break;
        case QQ:
            lastCommand[0] = 'Q';
            lastCommand[1] = 'Q';
            break;
        case P:
            lastCommand[0] = 'P';
            break;
        case Q:
            lastCommand[0] = 'Q';
            break;
        case MOVE:
            // TODO: use move data instead
            lastCommand[0] = 'M';
            lastCommand[1] = 'O';
            lastCommand[2] = 'V';
            lastCommand[3] = 'E';
            break;
        case U:
            lastCommand[0] = 'U';
            break;
        case R:
            lastCommand[0] = 'R';
            break;
        case S:
            lastCommand[0] = 'S';
            break;
        case L:
            lastCommand[0] = 'L';
            break;
        default:
            break;
    }
    printf("Last Command: %s\n", lastCommand);
    char status[] = "          ";
    switch (commandHistory->status) {
        case 0:
            status[0] = 'O';
            status[1] = 'K';
            break;
        case -1:
            status[0] = 'E';
            status[1] = 'R';
            status[2] = 'R';
            status[3] = 'O';
            status[4] = 'R';
            break;
        default:
            status[0] = 'U';
            status[1] = 'N';
            status[2] = 'K';
            status[3] = 'N';
            status[4] = 'O';
            status[5] = 'W';
            status[6] = 'N';
            break;
    }
    printf("Message: %s\n", status);

    printf("INPUT >");
    fflush(stdout);
    char command[11];
    scanf("%s", &command);
    CommandNode commandNode;
    int statusCode = -1;
    if (strcmp(command, "LD") == 0) {
        commandNode.command = LD;
        char filename[20];
        scanf("%s", &filename);
        statusCode = LDCommand(filename);
    }
    else if (strcmp(command, "SW") == 0) {
        commandNode.command = SW;
        statusCode = SWCommand();
    }
    else if (strcmp(command, "SI") == 0) {
        commandNode.command = SI;
        int integer;
        scanf("%d", &integer);
        statusCode = SICommand(integer);
    }
    else if (strcmp(command, "SR") == 0) {
        commandNode.command = SR;
        statusCode = SRCommand();
    }
    else if (strcmp(command, "SD") == 0) {
        commandNode.command = SD;
        char filename[20];
        scanf("%s", &filename);
        statusCode = SDCommand(filename);
    }
    else if (strcmp(command, "QQ") == 0) {
        commandNode.command = QQ;
        statusCode = QQCommand();
    }
    else if (strcmp(command, "P") == 0) {
        commandNode.command = P;
        statusCode = PCommand();
    }
    else if (strcmp(command, "Q") == 0) {
        commandNode.command = Q;
        statusCode = QCommand();
    }
    else if (strchr(command, ':') != NULL && strchr(command, '-') != NULL && strchr(command, '>') != NULL) {
        commandNode.command = MOVE;
        // TODO: add data to commandNode
        statusCode = MCommand(command);
    }
    else if (strcmp(command, "U") == 0) {
        commandNode.command = U;
        statusCode = UCommand();
    }
    else if (strcmp(command, "R") == 0) {
        commandNode.command = R;
        statusCode = RCommand();
    }
    else if (strcmp(command, "S") == 0) {
        commandNode.command = S;
        char filename[20];
        scanf("%s", &filename);
        statusCode = SCommand(filename);
    }
    else if (strcmp(command, "L") == 0) {
        commandNode.command = L;
        char filename[20];
        scanf("%s", &filename);
        statusCode = LCommand(filename);
    }
    commandNode.status = statusCode;
    commandNode.prev = commandHistory;
    commandHistory->next = &commandNode;
    commandHistory = &commandNode;
    return statusCode;
};