#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "yukon.h"

CardColumn *columns[7];
CardFoundation *foundations[4];

int init() {
    for (int i = 0; i < 4; i++) {
        CardFoundation cardFoundation;
        cardFoundation.head = NULL;
        cardFoundation.tail = NULL;
    }
    for (int i = 0; i < 7; i++) {
        CardColumn cardColumn;
        cardColumn.head = NULL;
        cardColumn.tail = NULL;
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
        CardFoundation cardFoundation;
        cardFoundation.head = NULL;
        cardFoundation.tail = NULL;
        foundations[i] = &cardFoundation;
    }

    int i = 0;
    int columnNum = 0;
    int cardNum = 1;
    CardSuit cardSuit = CLUBS;
    CardColumn *cardColumn;
    while (true) {
        // if the column is filled up, make a new column
        if ((i > 6 && columnNum > 2) || (i > 7 && columnNum <= 2)) {
            columns[columnNum] = cardColumn;
            CardColumn *newColumn;
            newColumn->head = NULL;
            newColumn->tail = NULL;
            cardColumn = newColumn;
            columnNum++;
            i = 0;
        }

        // if we have reached the end of the suit cards
        if (cardNum > 13) {
            // if we were doing spades, then we're done
            if (cardSuit == SPADES) {
                break;
            }

            // else reset and switch suit
            cardNum = 1;
            switch (cardSuit) {
                case CLUBS:
                    cardSuit = DIAMONDS;
                    break;
                case DIAMONDS:
                    cardSuit = HEARTS;
                    break;
                case HEARTS:
                    cardSuit = SPADES;
                    break;
                default:
                    printf("ERROR!");
                    break;
            }
        }

        printf("i=%d; colN=%d; cardN=%d; suit:%d\n", i, columnNum, cardNum, cardSuit);

        // fill from the bottom up
        CardNode cardNode;
        Card card;
        card.suit = cardSuit;
        card.revealed = false;
        card.number = cardNum;
        cardNode.card = &card;
        cardNode.next = NULL;
        cardNode.prev = NULL;
        printf("Created cardNode! CardNum: %d, CardSuit: %d\n", card.number, card.suit);

        if (i == 0) {
            cardColumn->tail = &cardNode;
            cardColumn->head = &cardNode;
        }
        else {
            cardColumn->head->next = &cardNode;
            cardColumn->head = &cardNode;
        }
        printf("CardColumn head = CardNum: %d, CardSuit: %d\n", cardColumn->head->card->number, cardColumn->head->card->suit);
        printf("CardColumn tail = CardNum: %d, CardSuit: %d\n", cardColumn->tail->card->number, cardColumn->tail->card->suit);
        printf("\n");

        i++;
        cardNum++;
    }

//    for (int i = 0; i < 7; i++) {
//        CardColumn cardColumn;
//        cardColumn.head = NULL;
//        cardColumn.tail = NULL;
//        columns[i] = cardColumn;
//    }

    return 0;
}