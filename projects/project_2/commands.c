#include <malloc.h>
#include <string.h>
#include "commands.h"
#include "cli.h"
#include "cards.h"
#include "yukon.h"
#include "io.h"

CommandNode *commandHistory;

// Command enum



// loads a deck of cards from a file, if no file is given, we load a new deck of cards
int LDCommand(char *fileName) {
    // clear card storage, in case there is something
    clearCardStorage();
    // clear the deck as well
    clearDeck();

    if (fileName == NULL) {
        // load unshuffled deck of cards
        return getUnshuffledDeck();
    }
    else {
        // load cards from file
        Card *cards = malloc(sizeof(Card)*52);
        int loadStatus = loadCards(fileName, cards);
        if (loadStatus != 0) {
            return loadStatus;
        }

        // add cards to deck
        return addCardsToDeck(cards);
    }
}

// [SW] function to print/draw the terminal window / GUI/CLI
int SWCommand() {
    drawCards(true);
    return 0;
}

// SI, splits the card deck into to piles
int SICommand(int split) {
    // clear card storage, in case there is something
    clearCardStorage();

    return 0;
}

// SR command, shuffles the card deck
int SRCommand() {
    // clear card storage, in case there is something
    clearCardStorage();

    return 0;
}

// SD saves the current deck of cards to a file
int SDCommand(char *fileName) {
    // belive that filename is allocated by caller, but is set to null
    if (fileName == NULL) {
        fileName = malloc(sizeof(char)*10);
        strcpy(fileName, "cards.txt");
    }

    printf("saving to %s", fileName);
    saveCards(fileName);

    return 0;
}

// QQ command, quits the program
int QQCommand() {
    return 0;
}

// P command starts the game using the current card deck
int PCommand() {
    currentPhase = PLAY;
    // TODO: check if we're just continuing a game that we just paused
    convertStartupToPlay();
    return 0;
}

// Q command quits the game and goes back to startup
int QCommand() {
    currentPhase = STARTUP;
    switchCardStorage();
    return 0;
}

// game moves, where you can move the card from one pile to another
int MCommand(char *command, bool fromBottom) {
    char pile = command[0];
    int column = atol(&command[1]);
    if (((column > 7 && pile == 'C') || (column > 4 && pile == 'F')) || column < 1) {
        return -1;
    }
    char toPile;
    int toColumn;
    char cardName[2];

    Card *card;

    if (fromBottom) {
        toPile = command[4];
        toColumn = atol(&command[5]);

        CardNode *bottomNode = columns[column - 1];
        while (bottomNode->next) {
            bottomNode = bottomNode->next;
        }
        card = bottomNode->card;
    }
    else {
        toPile = command[7];
        toColumn = atol(&command[8]);
        cardName[0] = command[3];
        cardName[1] = command[4];

        // husk at free din bisse
        card = malloc(sizeof(Card));
        getCardFromName(cardName, card);
    }

    if (((toColumn > 7 && toPile == 'C') || (toColumn > 4 && toPile == 'F')) || toColumn < 1) {
        if (!fromBottom) free(card);
        return -1;
    }

    CardNode *currentCard;
    switch (pile) {
        case 'C':
            currentCard = columns[column - 1];
            break;
        case 'F':
            currentCard = foundations[column - 1];
            break;
        default:
            if (!fromBottom) free(card);
            return -2;
    }
    while (currentCard->card->number != card->number || currentCard->card->suit != card->suit) {
        if (!currentCard->next) {
            if (!fromBottom) free(card);
            return -3;
        }
        currentCard = currentCard->next;
    }
    if (!currentCard->card->revealed) {
        if (!fromBottom) free(card);
        return -4;
    }

    CardNode *toCard;
    switch (toPile) {
        case 'C':
            toCard = columns[toColumn - 1];

            if (toCard == NULL) {
                if (currentCard->card->number == 13) {
                    currentCard->prev->next = NULL;
                    columns[toColumn - 1] = currentCard;
                    currentCard->prev = NULL;
                } else {
                    if (!fromBottom) free(card);
                    return -5;
                }
            } else {
                while (toCard->next) {
                    toCard = toCard->next;
                }
                if (toCard->card->suit != currentCard->card->suit &&
                    toCard->card->number - 1 == currentCard->card->number) {
                    currentCard->prev->next = NULL;
                    currentCard->prev = toCard;
                    toCard->next = currentCard;
                } else {
                    if (!fromBottom) free(card);
                    return -6;
                }
            }

            break;
        case 'F':
            toCard = foundations[toColumn - 1];

            if (toCard == NULL) {
                if (currentCard->card->number == 1 && currentCard->next == NULL) {
                    // TODO might not work :) someone can maybe fix if they are giga chad aka Marcus
                    currentCard->prev->next = NULL;
                    foundations[toColumn - 1] = currentCard;
                    currentCard->prev = NULL;
                } else {
                    if (!fromBottom) free(card);
                    return -5;
                }
            } else {
                while (toCard->next) {
                    toCard = toCard->next;
                }
                if (currentCard->card->suit == toCard->card->suit &&
                    currentCard->card->number - 1 == toCard->card->number &&
                    currentCard->next == NULL) {
                    currentCard->prev->next = NULL;
                    currentCard->prev = toCard;
                    toCard->next = currentCard;

                    if (currentCard->card->number == 13){
                        bool notking;
                        for (int i=0; i>4; i++){
                            CardNode *cardNode = foundations[i];
                            while (cardNode->next) {cardNode = cardNode->next;}

                            if (cardNode->next == NULL && cardNode->card->number != 13){
                                notking = true;
                                break;
                            }
                        }
                        if (notking == false){
                            printf("You have won the Yukon Solitaire \n");
                            printf("Please write the command: LD to play again");
                        }
                    }

                } else {
                    if (!fromBottom) free(card);
                    return -6;
                }
            }

            break;
        default:
            if (!fromBottom) free(card);
            return -2;
    }

    if (!fromBottom) {
        // gør læreren glad :)
        free(card); 
    }

    return 0;
}

// extra stuff if time is found
// U command, undo the last move
int UCommand() {
    return 0;
}

// R command, redo the last move
int RCommand() {
    return 0;
}

// S command saves the current game to a file
int SCommand(char *fileName) {
    // belive that filename is allocated by caller, but is set to null
    if (fileName == NULL) {
        fileName = malloc(sizeof(char)*14);
        strcpy(fileName, "gamestate.txt");
    }

    return saveState(fileName);
}

// L command loads a game from a file
int LCommand(char *fileName) {
    return loadState(fileName);
}
