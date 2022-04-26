#include "commands.h"
#include "cli.h"

CommandNode *commandHistory;

// Command enum



// loads a deck of cards from a file, if no file is given, we load a new deck of cards
int LDCommand(char *fileName) {
    if (fileName == NULL) {
        // load unshuffled deck of cards
        return getUnshuffledDeck();
    }
    else {
        // validate filename

        // validate cards
    }
    return 0;
}

// [SW] function to print/draw the terminal window / GUI/CLI
int SWCommand() {
    drawCards();
    return 0;
}

// SI, splits the card deck into to piles
int SICommand(int split) {
    return 0;
}

// SR command, shuffles the card deck
int SRCommand() {
    return 0;
}

// SD saves the current deck of cards to a file
int SDCommand(char *fileName) {
    return 0;
}

// QQ command, quits the program
int QQCommand() {
    return 0;
}

// P command starts the game using the current card deck
int PCommand() {
    return 0;
}

// Q command quits the game and goes back to startup
int QCommand() {
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
    return 0;
}

// L command loads a game from a file
int LCommand(char *fileName) {
    return 0;
}
