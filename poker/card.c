#include "card.h"
#include <stdlib.h>

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
