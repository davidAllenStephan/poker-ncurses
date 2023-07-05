#ifndef POKER_H_
#define POKER_H_
#include <stdbool.h>
#include "card.h"
#include "player.h"

struct Card* create_deck();
struct Card* create_community(struct Card* deck);
void determine_winner(struct Player* players, int player_count, struct Card* comm);
struct Card* check_pair(struct Player player, struct Card* comm);


#endif
