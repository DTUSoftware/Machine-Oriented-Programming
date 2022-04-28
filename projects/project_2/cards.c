#include <malloc.h>
#include "cards.h"
#include "yukon.h"

Card allCards[] = {
        {.number = 1, .suit = CLUBS, .revealed = false},
        {.number = 2, .suit = CLUBS, .revealed = false},
        {.number = 3, .suit = CLUBS, .revealed = false},
        {.number = 4, .suit = CLUBS, .revealed = false},
        {.number = 5, .suit = CLUBS, .revealed = false},
        {.number = 6, .suit = CLUBS, .revealed = false},
        {.number = 7, .suit = CLUBS, .revealed = false},
        {.number = 8, .suit = CLUBS, .revealed = false},
        {.number = 9, .suit = CLUBS, .revealed = false},
        {.number = 10, .suit = CLUBS, .revealed = false},
        {.number = 11, .suit = CLUBS, .revealed = false},
        {.number = 12, .suit = CLUBS, .revealed = false},
        {.number = 13, .suit = CLUBS, .revealed = false},
        {.number = 1, .suit = DIAMONDS, .revealed = false},
        {.number = 2, .suit = DIAMONDS, .revealed = false},
        {.number = 3, .suit = DIAMONDS, .revealed = false},
        {.number = 4, .suit = DIAMONDS, .revealed = false},
        {.number = 5, .suit = DIAMONDS, .revealed = false},
        {.number = 6, .suit = DIAMONDS, .revealed = false},
        {.number = 7, .suit = DIAMONDS, .revealed = false},
        {.number = 8, .suit = DIAMONDS, .revealed = false},
        {.number = 9, .suit = DIAMONDS, .revealed = false},
        {.number = 10, .suit = DIAMONDS, .revealed = false},
        {.number = 11, .suit = DIAMONDS, .revealed = false},
        {.number = 12, .suit = DIAMONDS, .revealed = false},
        {.number = 13, .suit = DIAMONDS, .revealed = false},
        {.number = 1, .suit = HEARTS, .revealed = false},
        {.number = 2, .suit = HEARTS, .revealed = false},
        {.number = 3, .suit = HEARTS, .revealed = false},
        {.number = 4, .suit = HEARTS, .revealed = false},
        {.number = 5, .suit = HEARTS, .revealed = false},
        {.number = 6, .suit = HEARTS, .revealed = false},
        {.number = 7, .suit = HEARTS, .revealed = false},
        {.number = 8, .suit = HEARTS, .revealed = false},
        {.number = 9, .suit = HEARTS, .revealed = false},
        {.number = 10, .suit = HEARTS, .revealed = false},
        {.number = 11, .suit = HEARTS, .revealed = false},
        {.number = 12, .suit = HEARTS, .revealed = false},
        {.number = 13, .suit = HEARTS, .revealed = false},
        {.number = 1, .suit = SPADES, .revealed = false},
        {.number = 2, .suit = SPADES, .revealed = false},
        {.number = 3, .suit = SPADES, .revealed = false},
        {.number = 4, .suit = SPADES, .revealed = false},
        {.number = 5, .suit = SPADES, .revealed = false},
        {.number = 6, .suit = SPADES, .revealed = false},
        {.number = 7, .suit = SPADES, .revealed = false},
        {.number = 8, .suit = SPADES, .revealed = false},
        {.number = 9, .suit = SPADES, .revealed = false},
        {.number = 10, .suit = SPADES, .revealed = false},
        {.number = 11, .suit = SPADES, .revealed = false},
        {.number = 12, .suit = SPADES, .revealed = false},
        {.number = 13, .suit = SPADES, .revealed = false}
};

// convert the startup deck to a playing deck
int convertStartupToPlay() {
    CardNode *tempColumnStorage[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };
    for (int i = 0; i < 7; i++) {
        tempColumnStorage[i] = columns[i];
        columns[i] = NULL;
    }
    int rowCounts[7] = { 0, 0, 0, 0, 0, 0, 0 };
    int emptyCount = 0;
    int tempColCounter = 0;
    while (emptyCount < 7) {
        emptyCount = 0;
        for (int j = 0; j < 7; j++) {
            if (tempColumnStorage[j] == NULL || tempColumnStorage[j]->card == NULL) {
                emptyCount++;
            }
        }
        if (emptyCount >= 7) {
            break;
        }

        // loop through columns
        for (int i = 0; i < 7; i++) {
            // add to the first column that accepts more stuff
            if ((i == 0 && rowCounts[i] < 1) || (i > 0 && rowCounts[i] < 5+i)) {
                emptyCount = 0;
                while (true) {
                    int j = tempColCounter%7;
                    tempColCounter++;
                    if (tempColumnStorage[j] == NULL || tempColumnStorage[j]->card == NULL) {
                        emptyCount++;
                        if (emptyCount >= 7) {
                            break;
                        }
                    }
                    else {
                        // append to column
                        if (columns[i] && columns[i]->card != NULL) {
//                            printf("add from tempcol %d to column %d\n", j, i);
//                            printf("card = N:%d S:%d\n", tempColumnStorage[j]->card->number, tempColumnStorage[j]->card->suit);
                            CardNode *parent = columns[i];
                            while (parent->next) {
                                parent = parent->next;
                            }
                            parent->next = tempColumnStorage[j];
                        }
                        // start a new column
                        else {
//                            printf("add from tempcol %d to column %d [NEW]\n", j, i);
//                            printf("card = N:%d S:%d\n", tempColumnStorage[j]->card->number, tempColumnStorage[j]->card->suit);
                            columns[i] = tempColumnStorage[j];
                        }
                        rowCounts[i]++;

                        // move temp col one down
                        tempColumnStorage[j] = tempColumnStorage[j]->next;
                        if (tempColumnStorage[j]) {
                            if (tempColumnStorage[j]->prev) {
                                tempColumnStorage[j]->prev->next = NULL;
                            }
                            tempColumnStorage[j]->prev = NULL;
                        }
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

// save cards from current game to memory
// takes stored cards and restores them
int switchCardStorage() {
    for (int i = 0; i < 7; i++) {
        CardNode *tempColumnPointer = columns[i];
        columns[i] = columnStorage[i];
        columnStorage[i] = tempColumnPointer;
    }
    return 0;
}