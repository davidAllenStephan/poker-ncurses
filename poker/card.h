#ifndef CARD_H_
#define CARD_H_

struct Card {
    int rank;
    char suit;
    int player;
};

struct Card pull_card(struct Card* deck, int player);

#endif
