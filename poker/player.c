#include "player.h"
#include "card.h"
#include <stdlib.h>
#include <sys/_types/_null.h>

struct Player* create_players(int num, struct Card* deck) {
    struct Player* players;
    struct Card empty_card;
    empty_card.player = -3;
    empty_card.rank = -1;
    empty_card.suit = 'x';
    players = malloc(num * sizeof(struct Player));
    for (int i = 0; i < num; i++) {
        struct Player current_player;
        current_player.player = i;
        players[i] = current_player;
        players[i].hole[0] = pull_card(deck, i);
        players[i].hole[1] = pull_card(deck, i);
        players[i].winning[0] = empty_card;
        players[i].winning[1] = empty_card;
        players[i].winning[2] = empty_card;
        players[i].winning[3] = empty_card;
        players[i].winning[4] = empty_card;
        players[i].winning_type = 'x';
    }
    return players;
}
