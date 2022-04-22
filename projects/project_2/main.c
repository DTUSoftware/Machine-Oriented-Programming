#include <stdio.h>
#include <stdbool.h>
#include "commands.h"  // Import the commands
#include "cli.h"  // The command-line interface
#include "yukon.h"  // The game

int main() {
    Card card;
    card.number = 10;
    card.suit = CLUBS;

    Node n;
    Node h;
    n.next = &h;

    // the moves/executed commands can be stored in a linked list
    // in order to be able to undo commands

    // the commands that have been undone can be stored in a linked list
    // in order to be able to redo commands

    // the 7 columns can be represented as an array of linked lists

    // the four foundations can be represented as an array of linked lists
    return 0;
}
