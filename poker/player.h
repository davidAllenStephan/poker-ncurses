#ifndef PLAYER_H_
#define PLAYER_H_
#include "card.h"
#include <sys/_types/_null.h>

struct Player {
    int player;
    struct Card hole[2];
    struct Card winning[5];
};

struct Player* create_players(int num, struct Card* deck);

#endif
