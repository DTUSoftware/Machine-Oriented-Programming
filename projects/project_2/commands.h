#ifndef MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_COMMANDS_H
#define MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_COMMANDS_H

// Command enum

// loads a deck of cards from a file, if no file is given, we load a new deck of cards
int LDCommand(char *fileName);

// [SW] function to print/draw the terminal window / GUI/CLI
int SWCommand();

// Sl, splits the card deck into to piles
int SlCommand(int split);

// SR command, shuffles the card deck
int SRCommand();

// SD saves the current deck of cards to a file
int SDCommand(char *fileName);

// QQ command, quits the program
int QQCommand();

// P command starts the game using the current card deck
int PCommand();

// Q command quits the game and goes back to startup
int QCommand();

// game moves, where you can move the card from one pile to another
int MCommand();
#endif //MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_COMMANDS_H
