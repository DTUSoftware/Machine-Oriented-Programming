#include <stdio.h>
#include <stdbool.h>
#include "commands.h"  // Import the commands
#include "cli.h"  // The command-line interface
#include "yukon.h"  // The game

int main() {

    for (int i = 0; i < 7; i++) {
        Node n;

        Card card;
        card.number = 9;
        card.suit = CLUBS;
        card.revealed = true;
        n.card = card;

        n.next = NULL;

        columns[i] = n;
    }

    for (int i = 0; i < 4; i++) {
        Node n;

        Card card;
        card.number = 13;
        card.suit = HEARTS;
        card.revealed = true;
        n.card = card;

        n.next = NULL;

        foundations[i] = n;
    }

    SWCommand();

    // the moves/executed commands can be stored in a linked list
    // in order to be able to undo commands

    // the commands that have been undone can be stored in a linked list
    // in order to be able to redo commands

    // the 7 columns can be represented as an array of linked lists

    // the four foundations can be represented as an array of linked lists
    return 0;
}
