#include <stdio.h>
#include <stdbool.h>
#include "commands.h"  // Import the commands
#include "funcdcl.h"   // Import the function declarations


//Double linked lst66
typedef struct card {
    struct node *prev;
    struct node *next;
    char data[2];
    bool revealed;
    int key;
};



// Card struct - bool value for face up or down
typedef enum {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} CardSuit;

typedef enum {
    RED,
    BLACK
} CardColor;

typedef struct {
    int number;
    CardSuit suit;
} Card;


// Game phase enum (startup, etc.)

// function to check if card from one column can move onto other column
// - get other column, get tail/head of linked list, check requirements in rules


int main() {
    Card card;
    card.number = 10;
    card.suit = CLUBS;


    // the moves/executed commands can be stored in a linked list
    // in order to be able to undo commands

    // the commands that have been undone can be stored in a linked list
    // in order to be able to redo commands

    // the 7 columns can be represented as an array of linked lists

    // the four foundations can be represented as an array of linked lists
    return 0;
}
