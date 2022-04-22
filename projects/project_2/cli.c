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

int drawCards(Node *_columns, Node *_foundations) {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");
    printf("\n");
    bool activeColumns[7] = {true, true, true, true, true, true, true};

    Node columnCards[7];
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