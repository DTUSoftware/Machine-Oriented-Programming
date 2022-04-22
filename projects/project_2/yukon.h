#ifndef MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_YUKON_H
#define MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_YUKON_H

#include <stdio.h>
#include <stdbool.h>

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
    bool revealed;
} Card;

//Double linked lst66
typedef struct CardNodeP CardNode;
typedef struct CardNodeP {
    CardNode *prev;
    CardNode *next;
    Card card;
} CardNode;

// Column and foundation arrays
extern CardNode columns[7];
extern CardNode foundations[4];

// Game phase enum (startup, etc.)

// function to check if card from one column can move onto other column
// - get other column, get tail/head of linked list, check requirements in rules


#endif //MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_YUKON_H
