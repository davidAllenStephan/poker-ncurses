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
        struct Card is_highest = check_highest(players[i]);
        if (is_highest.player != -3) {
            players[i].winning[0] = is_highest;
        }
        struct Card* is_pair = check_pair(players[i], comm, -1);
        if (is_pair[0].player != -3) {
            players[i].winning[0] = is_pair[0];
            players[i].winning[1] = is_pair[1];
        }
        struct Card* is_tpair = check_tpair(players[i], comm);
        if (is_tpair[3].player != -3) {
            players[i].winning[0] = is_tpair[0];
            players[i].winning[1] = is_tpair[1];
            players[i].winning[2] = is_tpair[2];
            players[i].winning[3] = is_tpair[3];
        }
    }
}

struct Card check_highest(struct Player player) {
  if (player.hole[0].rank >= player.hole[1].rank) {
    return player.hole[0];
  } else if (player.hole[0].rank < player.hole[1].rank) {
    return player.hole[1];
  }
  struct Card empty_card;
  empty_card.suit = 'x';
  empty_card.rank = -1;
  empty_card.player = -3;
  return empty_card;
}

struct Card* check_pair(struct Player player, struct Card* comm, int rank_ignore) {
    static struct Card highest_pair[2];
    highest_pair[0] = get_empty_card();
    highest_pair[1] = get_empty_card();
    if(player.hole[0].rank != rank_ignore && player.hole[1].rank != rank_ignore) {
    if (player.hole[0].rank == player.hole[1].rank) {
        highest_pair[0] = player.hole[0];
        highest_pair[1] = player.hole[1];
        return highest_pair;
    }
    for (int i = 0; i < 5; i++) {
        if (player.hole[0].rank == comm[i].rank) {
            if (highest_pair[0].rank < player.hole[0].rank || highest_pair[0].player == -3) {
                highest_pair[0] = player.hole[0];
                highest_pair[1] = comm[i];
            }
        }
        if (player.hole[1].rank == comm[i].rank) {
            if (highest_pair[0].rank < player.hole[1].rank || highest_pair[0].player == -3) {
                highest_pair[0] = player.hole[1];
                highest_pair[1] = comm[i];
            }
        }
    }
    }
    for (int i = 0; i < 5; i++) {
      if (comm[i].rank != rank_ignore) {
      for (int k = 0; k < 5; k++) {
            if (i != k) {
                if (comm[i].rank == comm[k].rank) {
                    if (highest_pair[0].rank < comm[i].rank || highest_pair[0].player == -3) {
                        highest_pair[0] = comm[i];
                        highest_pair[1] = comm[k];
                    }
                }
            }
        }
      }

    }
    return highest_pair;
}

struct Card* check_tpair(struct Player player, struct Card* comm) {
    static struct Card highest_tpair[4];
    highest_tpair[0] = get_empty_card();
    highest_tpair[1] = get_empty_card();
    highest_tpair[2] = get_empty_card();
    highest_tpair[3] = get_empty_card();
    struct Card* pair_one = check_pair(player, comm, -1);
    if (pair_one[0].player != -3) {
        struct Card* pair_two = check_pair(player, comm, pair_one[0].rank);
        if (pair_two[0].player != -3) {
            highest_tpair[0] = pair_one[0];
            highest_tpair[1] = pair_one[1];
            highest_tpair[2] = pair_two[0];
            highest_tpair[3] = pair_two[1];
        }
    }
    return highest_tpair;
}
