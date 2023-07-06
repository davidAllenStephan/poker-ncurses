#include "card.h"
#include <stdlib.h>
#include <stdbool.h>

struct Card pull_card(struct Card* deck, int player) {
    int r;
    r = rand() % 52;
    struct Card current_card = deck[r];
    if (current_card.player != -1) {
        return pull_card(deck, player);
    }
    deck[r].player = player;
    return current_card;
}

bool is_equal(struct Card card_1, struct Card card_2) {
    if (card_1.rank == card_2.rank && card_1.player == card_2.player && card_1.suit == card_2.suit) {
        return true;
    }
    return false;
}

struct Card get_empty_card() {
    struct Card empty_card;
    empty_card.player = -3;
    empty_card.rank = -1;
    empty_card.suit = 'x';
    return empty_card;
}
