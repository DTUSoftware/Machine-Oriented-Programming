#include <stdio.h>
#include <malloc.h>
#include "yukon.h"
#include "cards.h"
#include "io.h"
#include "commands.h"

CardNode *columns[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };
CardNode *columnStorage[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };
CardNode *foundations[4] = { NULL, NULL, NULL, NULL };

Phase currentPhase = STARTUP;

// clear the deck
int clearDeck() {
    for (int i = 0; i < 4; i++) {
        CardNode *cardNode = foundations[i];
        while (cardNode) {
            CardNode *next = cardNode->next;
            free(cardNode->card);
            free(cardNode);
            cardNode = next;
        }
        foundations[i] = NULL;
    }
    for (int i = 0; i < 7; i++) {
        CardNode *cardNode = columns[i];
        while (cardNode) {
            CardNode *next = cardNode->next;
            // TODO: fix so this free of card doesn't break the code
//            free(cardNode->card);
            free(cardNode);
            cardNode = next;
        }
        columns[i] = NULL;
    }
    return 0;
}

// Card struct - bool value for face up or down


// Game phase enum (startup, etc.)


int addCardsToDeck(Card *cards) {
    int cardNum = 0;
    while (cardNum < 52) {
        for (int i = 0; i < 7; i++) {
            if (cardNum < 52) {
                CardNode *cardNode = malloc(sizeof(CardNode));
                if (cardNode == NULL) {
                    return -1;
                }
                cardNode->next = NULL;
                cardNode->prev = NULL;
                cardNode->card = &cards[cardNum];
                if (!columns[i]) {
                    columns[i] = cardNode;
                }
                else {
                    CardNode *next = columns[i]->next;
                    CardNode *prev = columns[i];
                    while (next) {
                        prev = next;
                        next = next->next;
                    }
                    prev->next = cardNode;
                    cardNode->prev = prev;
                }
//                printf("Added card to column %d!\n"
//                       "Cardnum: %d\n"
//                       "Head = Num: %d - Suit: %d\n"
//                       "Newcard = Num: %d - Suit: %d\n\n",
//                       i+1, cardNum+1,
//                       columns[i]->card->number, columns[i]->card->suit,
//                       cardNode->card->number, cardNode->card->suit);
                cardNum++;
            }
            else {
                break;
            }
        }
    }

    return 0;
}


// function to check if card from one column can move onto other column
// - get other column, get tail/head of linked list, check requirements in rules

int getUnshuffledDeck() {
    return LDCommand("examples/decks/unshuffled.txt");
}
