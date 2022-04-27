#ifndef MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_CARDS_H
#define MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_CARDS_H

#include "yukon.h"

extern Card allCards[53];

int shuffleCards(CardNode *cards);

// takes from cards to deck
int importCards(Card *cards);

// takes from deck to cards
int exportCards(Card *cards);

#endif //MACHINE_ORIENTED_PROGRAMMING_PROJECT_2_CARDS_H
