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

    if (fileName == NULL) {
        // load unshuffled deck of cards
        return getUnshuffledDeck();
    }
    else {
        // load cards from file
        Card cards[52];
        int loadStatus = loadCards(fileName, cards);
        if (loadStatus != 0) {
            return loadStatus;
        }

        // add cards to deck
    }
    return 0;
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
int MCommand(char *command) {
    char pile = command[0];
    char toPile = command[7];
    int column = (int) command[1];
    int toColumn = (int) command[8];
    char cardName[2];
    cardName[0] = command[3];
    cardName[1] = command[4];
    // husk at free din bisse
    Card *card = malloc(sizeof(Card));
    getCardFromName(cardName, card);
    switch (pile) {
        case 'C':
            if (column < 8 && column > 0) {
                CardNode *currentCard = columns[column - 1];
                while (currentCard) {
                    if (currentCard->card->number == card->number && currentCard->card->suit == card->suit &&
                        card->revealed) {
                        switch (toPile) {
                            case 'C':
                                if (toColumn < 8 && toColumn > 0) {
                                    CardNode *toCard = columns[toColumn - 1];
                                    if (toCard == NULL) {
                                        if (currentCard->card->number == 13) {
                                            // TODO might not work :) someone can maybe fix if they are giga chad aka Marcus
                                            currentCard->prev->next = NULL;
                                            toCard = currentCard;
                                            currentCard->prev = NULL;
                                        } else return -1;
                                    } else {}
                                    while (toCard->next) {
                                        toCard = toCard->next;
                                    }
                                    if (toCard->card->suit != currentCard->card->suit &&
                                        toCard->card->number - 1 == currentCard->card->number) {
                                        currentCard->prev->next = NULL;
                                        currentCard->prev = toCard;
                                        toCard->next = currentCard;
                                    } else return -1;
                                }
                                break;
                            case 'F':
                                if (toColumn < 5 && toColumn > 0) {
                                    CardNode *toCard = foundations[toColumn - 1];
                                    if (toCard == NULL) {
                                        if (currentCard->card->number == 1 && currentCard->next == NULL) {
                                            // TODO might not work :) someone can maybe fix if they are giga chad aka Marcus
                                            currentCard->prev->next = NULL;
                                            toCard = currentCard;
                                            currentCard->prev = NULL;
                                        } else return -1;
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
                                        }
                                    }

                                }
                                break;
                            default:
                                printf("You're not smart :)");
                        }
                    }
                    currentCard = currentCard->next;
                }
            } else return -1;
            break;
        case 'F':
            if (column < 5 && column > 0) {
                CardNode *currentCard = columns[column - 1];
                while (currentCard->next == NULL) {
                    if (currentCard->card->number == card->number && currentCard->card->suit == card->suit &&
                        card->revealed) {
                        switch (toPile) {
                            case 'C':
                                if (toColumn < 8 && toColumn > 0) {
                                    CardNode *toCard = columns[toColumn - 1];
                                    if (toCard == NULL) {
                                        if (currentCard->card->number == 13) {
                                            // TODO might not work :) someone can maybe fix if they are giga chad aka Marcus
                                            currentCard->prev->next = NULL;
                                            toCard = currentCard;
                                            currentCard->prev = NULL;
                                        } else return -1;
                                    } else {}
                                    while (toCard->next) {
                                        toCard = toCard->next;
                                    }
                                    if (toCard->card->suit != currentCard->card->suit &&
                                        toCard->card->number - 1 == currentCard->card->number) {
                                        currentCard->prev->next = NULL;
                                        currentCard->prev = toCard;
                                        toCard->next = currentCard;
                                    } else return -1;
                                }
                                break;
                            case 'F':
                                if (toColumn < 5 && toColumn > 0) {
                                    CardNode *toCard = foundations[toColumn - 1];
                                    if (toCard == NULL) {
                                        if (currentCard->card->number == 1 && currentCard->next == NULL) {
                                            // TODO might not work :) someone can maybe fix if they are giga chad aka Marcus
                                            currentCard->prev->next = NULL;
                                            toCard = currentCard;
                                            currentCard->prev = NULL;
                                        } else return -1;
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
                                        }
                                    }

                                }
                                break;
                            default:
                                printf("You're not smart :)");
                        }
                    }
                    currentCard = currentCard->next;
                }
            } else return -1;
            break;
        default:
            return -1;
    }
    // gør læreren glad :)
    free(card);

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
