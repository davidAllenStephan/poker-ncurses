#include "player.h"
#include "card.h"
#include <stdlib.h>

struct Player* create_players(int num, struct Card* deck) {
    struct Player* players;
    players = malloc(num * sizeof(struct Player));
    for (int i = 0; i < num; i++) {
        struct Player current_player;
        current_player.player = i;
        players[i] = current_player;
        players[i].hole[0] = pull_card(deck, i);
        players[i].hole[1] = pull_card(deck, i);
    }
    return players;
}
