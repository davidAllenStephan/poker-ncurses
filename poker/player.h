#ifndef PLAYER_H_
#define PLAYER_H_
#include "card.h"

struct Player {
    int player;
    struct Card hole[2];
    struct Card winning[2];
};

struct Player* create_players(int num, struct Card* deck);

#endif
