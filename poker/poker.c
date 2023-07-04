#include "poker.h"
#include "card.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

struct Card* create_deck() {
    static struct Card deck[52];
    for (int i = 0; i < 52; i++) {
        struct Card current_card;
        current_card.player = -1;
        if (i < 13) {
            current_card.rank = i;
            current_card.suit = 'c';
            deck[i] = current_card;
        } else if (i < 26) {
            current_card.rank = i - 13;
            current_card.suit = 'd';
            deck[i] = current_card;
        } else if (i < 39) {
            current_card.rank = i - 26;
            current_card.suit = 'h';
            deck[i] = current_card;
        } else if (i < 52) {
            current_card.rank = i - 39;
            current_card.suit = 's';
            deck[i] = current_card;
        }
    }
    return deck;
}

struct Card* create_community(struct Card* deck) {
    static struct Card community[5];
    for (int i = 0; i < 5; i++) {
        community[i] = pull_card(deck, -2);
    }
    return community;
}
