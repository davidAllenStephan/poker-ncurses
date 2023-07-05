#ifndef CARD_H_
#define CARD_H_
#include <stdbool.h>

struct Card {
    int rank;
    char suit;
    int player;
};

struct Card pull_card(struct Card* deck, int player);
bool is_equal(struct Card card_1, struct Card card_2);

#endif
