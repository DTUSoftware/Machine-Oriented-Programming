#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "yukon.h"
#include "cards.h"

CardColumn *columns[7];
CardFoundation *foundations[4];

int init() {
    for (int i = 0; i < 4; i++) {
        CardNode cardNode = { .card = NULL, .prev = NULL, .next = NULL };
        CardFoundation cardFoundation = { .head = &cardNode, .tail = &cardNode };
        foundations[i] = &cardFoundation;
    }
    for (int i = 0; i < 7; i++) {
        CardNode cardNode = { .card = NULL, .prev = NULL, .next = NULL };
        CardColumn cardColumn = { .head = &cardNode, .tail = &cardNode };
        columns[i] = &cardColumn;
    }
    return 0;
}

//Double linked lst66

// Card struct - bool value for face up or down


// Game phase enum (startup, etc.)

// function to check if card from one column can move onto other column
// - get other column, get tail/head of linked list, check requirements in rules

int getUnshuffledDeck() {
    for (int i = 0; i < 4; i++) {
        CardFoundation cardFoundation = { .head = NULL, .tail = NULL };
        foundations[i] = &cardFoundation;
    }

    int cardNum = 0;
    for (int i = 0; i < 7; i++) {
        CardColumn cardColumn = { .head = NULL, .tail = NULL };
        int limit = (i+1)*8;
        if (i > 2) {
            limit = (3*8)+((i-2)*7);
        }
        while (cardNum < limit) {
            CardNode cardNode = { .next = NULL, .prev = NULL };
            cardNode.card = &allCards[cardNum];
            if (cardColumn.head == NULL) {
                cardColumn.head = &cardNode;
                cardColumn.tail = &cardNode;
            }
            else {
                cardColumn.head->next = &cardNode;
                cardNode.prev = cardColumn.head;
                cardColumn.head = &cardNode;
            }
            printf("Added card to column %d!\n"
                   "Cardnum: %d\n"
                   "Head = Num: %d - Suit: %d\n"
                   "Tail = Num: %d - Suit: %d\n\n",
                   i+1, cardNum+1,
                   cardColumn.head->card->number, cardColumn.head->card->suit,
                   cardColumn.tail->card->number, cardColumn.tail->card->suit);
            cardNum++;
        }
    }

    return 0;
}