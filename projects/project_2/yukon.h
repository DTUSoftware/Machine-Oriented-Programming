#ifndef MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_YUKON_H
#define MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_YUKON_H

#include <stdio.h>
#include <stdbool.h>

//Double linked lst66
typedef struct NodeP Node;
typedef struct NodeP {
    Node *prev;
    Node *next;
    char data[2];
    bool revealed;
    int key;
} Node;

// Card struct - bool value for face up or down
typedef enum CardSuitP CardSuit;
typedef enum CardSuitP {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} CardSuit;

typedef enum CardColorP CardColor;
typedef enum CardColorP {
    RED,
    BLACK
} CardColor;

typedef struct CardP Card;
typedef struct CardP {
    int number;
    CardSuit suit;
} Card;


// Game phase enum (startup, etc.)

// function to check if card from one column can move onto other column
// - get other column, get tail/head of linked list, check requirements in rules


#endif //MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_YUKON_H
