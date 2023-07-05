#include "poker.h"
#include "card.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void determine_winner(struct Player* players, int player_count, struct Card* comm) {
    for (int i = 0; i < player_count; i++) {
        struct Card* is_pair = check_pair(players[i], comm);
        struct Card foo[2] = {is_pair[0], is_pair[1]};
        players[i].winning = foo;
    }
}

struct Card* check_pair(struct Player player, struct Card* comm) {
    static struct Card highest_pair[2];
    if (player.hole[0].rank == player.hole[1].rank) {
        highest_pair[0] = player.hole[0];
        highest_pair[1] = player.hole[1];
        return highest_pair;
    }
    for (int i = 0; i < 5; i++) {
        if (player.hole[0].rank == comm[i].rank) {
            if (highest_pair[0].rank < player.hole[0].rank) {
                highest_pair[0] = player.hole[0];
                highest_pair[1] = comm[i];
            }
        }
        if (player.hole[1].rank == comm[i].rank) {
            if (highest_pair[0].rank < player.hole[1].rank) {
                highest_pair[0] = player.hole[1];
                highest_pair[1] = comm[i];
            }
        }
    }
    return highest_pair;
}
