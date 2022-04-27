//
// The CLI (command-line interface) for the program
//

#ifndef MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_CLI_H
#define MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_CLI_H

#include "yukon.h"

int getCardName(Card *card, char *cardName, bool debug);

int drawCards();

// read the user input
int readCommand();

#endif //MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_CLI_H
