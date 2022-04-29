#include <string.h>
#include "commands.h"
#include "cli.h"
#include "cards.h"
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
        strcpy(fileName, "cards.txt");
    }

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
        strcpy(fileName, "gamestate.txt");
    }

    return saveState(fileName);
}

// L command loads a game from a file
int LCommand(char *fileName) {
    return loadState(fileName);
}
