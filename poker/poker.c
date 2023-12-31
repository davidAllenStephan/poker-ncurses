#include "poker.h"
#include "card.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool exists1d(struct Card* array, int array_size, int search);
int exists2d(struct Card** array, int search);

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

struct Card* create_collection(struct Player player, struct Card* community) {
  static struct Card collection[7];
  for (int i = 0, j = 0; i < 7; i++) {
    if (i < 2) {
      collection[i] = player.hole[i];
    } else {
      collection[i] = community[j];
      j++;
    }
  }
  return collection;
}

struct Card* check_all(struct Card* community) {
  sort_cards(community);
  static struct Card hand[5];
  for (int i = 0; i < 7; i++) {

  }
  return hand;
}

bool exists1d(struct Card* array, int array_size, int search) {
  for (int i = 0; i < array_size; i++) {
    if (array[i].rank == search) {
      return true;
    }
  }
  return false;
}
int exists2d(struct Card** array, int search) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 4; j++) {
      if (i != j) {
        if (array[i][j].rank == search) {
          return i;
        }
      }
    }
  }
  return -1;
}

void determine_winner(struct Player* players, int player_count, struct Card* comm) {

    for (int i = 0; i < player_count; i++) {
        struct Card is_highest = check_highest(players[i]);

        if (is_highest.player != -3) {
            players[i].winning[0] = is_highest;
            players[i].winning_type = 'h';
        }
        struct Card* is_pair = check_pair(players[i], comm, -1);
        if (is_pair[0].player != -3) {
            players[i].winning[0] = is_pair[0];
            players[i].winning[1] = is_pair[1];
            players[i].winning_type = 'p';
        }
        struct Card* is_tpair = check_tpair(players[i], comm);
        if (is_tpair[0].player != -3) {
            players[i].winning[0] = is_tpair[0];
            players[i].winning[1] = is_tpair[1];
            players[i].winning[2] = is_tpair[2];
            players[i].winning[3] = is_tpair[3];
            players[i].winning_type = 't';
        }
        struct Card* is_triple = check_triple(players[i], comm);
        if (is_triple[0].player != -3) {
            players[i].winning[0] = is_triple[0];
            players[i].winning[1] = is_triple[1];
            players[i].winning[2] = is_triple[2];
            players[i].winning[3] = get_empty_card();
            players[i].winning_type = 'r';
        }
        struct Card* is_straight = check_straight(players[i], comm);
        if (is_straight[0].player != -3) {
            players[i].winning[0] = is_straight[0];
            players[i].winning[1] = is_straight[1];
            players[i].winning[2] = is_straight[2];
            players[i].winning[3] = is_straight[3];
            players[i].winning[4] = is_straight[4];
            players[i].winning_type = 's';
        }
        struct Card* is_flush = check_flush(players[i], comm);
        if (is_flush[0].player != -3) {
            players[i].winning[0] = is_flush[0];
            players[i].winning[1] = is_flush[1];
            players[i].winning[2] = is_flush[2];
            players[i].winning[3] = is_flush[3];
            players[i].winning[4] = is_flush[4];
            players[i].winning_type = 'f';
        }
        struct Card* is_full = check_full(players[i], comm);
        if (is_full[0].player != -3) {
            players[i].winning[0] = is_full[0];
            players[i].winning[1] = is_full[1];
            players[i].winning[2] = is_full[2];
            players[i].winning[3] = is_full[3];
            players[i].winning[4] = is_full[4];
            players[i].winning_type = 'u';

        }
        struct Card* is_straight_flush = check_straight_flush(players[i], comm);
        if (is_straight_flush[0].player != -3) {
            players[i].winning[0] = is_straight_flush[0];
            players[i].winning[1] = is_straight_flush[1];
            players[i].winning[2] = is_straight_flush[2];
            players[i].winning[3] = is_straight_flush[3];
            players[i].winning[4] = is_straight_flush[4];
            players[i].winning_type = 'a';
        }
    }
}

struct Card check_highest(struct Player player) {
  if (player.hole[0].rank >= player.hole[1].rank) {
    return player.hole[0];
  } else if (player.hole[0].rank < player.hole[1].rank) {
    return player.hole[1];
  }
  return get_empty_card();
}

struct Card* check_pair(struct Player player, struct Card* comm, int rank_ignore) {
    static struct Card highest_pair[2];
    static struct Card cc[7];
    highest_pair[0] = get_empty_card();
    highest_pair[1] = get_empty_card();
    cc[0] = player.hole[0];
    cc[1] = player.hole[1];
    cc[2] = comm[0];
    cc[3] = comm[1];
    cc[4] = comm[2];
    cc[5] = comm[3];
    cc[6] = comm[4];
    if(player.hole[0].rank != rank_ignore) {
        if (player.hole[0].rank == player.hole[1].rank) {
            highest_pair[0] = player.hole[0];
            highest_pair[1] = player.hole[1];
        }
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (j != i) {
                if (cc[i].rank == cc[j].rank && cc[i].rank != rank_ignore) {
                    if (highest_pair[0].rank < cc[i].rank || highest_pair[0].player == -3) {
                        highest_pair[0] = cc[i];
                        highest_pair[1] = cc[j];
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
    /* note: having these if statments below nested within each other caused
     * lots of problems, pair_two would always equal pair_one for some
     * reason even when finding a second pair
     */
    struct Card* pair_one = check_pair(player, comm, -1);
    if (pair_one[0].player != -3) {
        highest_tpair[0] = pair_one[0];
        highest_tpair[1] = pair_one[1];
    }
    struct Card* pair_two = check_pair(player, comm, pair_one[0].rank);
    if (pair_two[0].player != -3) {
        highest_tpair[2] = pair_two[0];
        highest_tpair[3] = pair_two[1];
    }
    return highest_tpair;
}

struct Card* check_triple(struct Player player, struct Card* comm) {
    static struct Card highest_triple[3];
    static struct Card cc[7];
    highest_triple[0] = get_empty_card();
    highest_triple[1] = get_empty_card();
    highest_triple[2] = get_empty_card();
    cc[0] = player.hole[0];
    cc[1] = player.hole[1];
    cc[2] = comm[0];
    cc[3] = comm[1];
    cc[4] = comm[2];
    cc[5] = comm[3];
    cc[6] = comm[4];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 7; k++) {
                if (i != j && j != k && i != k) {
                    if (cc[i].rank == cc[j].rank && cc[j].rank == cc[k].rank && cc[i].rank == cc[j].rank) {
                        if (cc[i].rank > highest_triple[0].rank || highest_triple[0].player == -3) {
                            highest_triple[0] = cc[i];
                            highest_triple[1] = cc[j];
                            highest_triple[2] = cc[k];
                        }
                    }
                }
            }
        }
    }
    return highest_triple;
}
/*
 * TODO: make sure its actually the highest straight and replace the returning array if there is a higher one
 */
struct Card* check_straight(struct Player player, struct Card* comm) {
    static struct Card highest_straight[5];
    static struct Card cc[7];
    for (int i = 0; i < 5; i++) {
        highest_straight[i] = get_empty_card();
    }
    cc[0] = player.hole[0];
    cc[1] = player.hole[1];
    cc[2] = comm[0];
    cc[3] = comm[1];
    cc[4] = comm[2];
    cc[5] = comm[3];
    cc[6] = comm[4];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i != j) {
                if (cc[i].rank == cc[j].rank) {
                    cc[i] = get_empty_card();
                }
                if (cc[i].rank <= cc[j].rank) {
                    struct Card temp = cc[i];
                    cc[i] = cc[j];
                    cc[j] = temp;
                }
            }
        }
    }
        for (int i = 1, j = 0; i < 7; i++) {
            if (cc[i].rank != cc[i - 1].rank + 1) {
                for (int k = 0; k < 5; k++) {
                    highest_straight[k] = get_empty_card();
                }
                break;
            }
            highest_straight[j] = cc[i];
            j++;
        }

    return highest_straight;
}

struct Card* check_flush(struct Player player, struct Card* comm) {
    static struct Card highest_flush[5];
    static struct Card cc[7];
    for (int i = 0; i < 5; i++) {
        highest_flush[i] = get_empty_card();
    }
    cc[0] = player.hole[0];
    cc[1] = player.hole[1];
    cc[2] = comm[0];
    cc[3] = comm[1];
    cc[4] = comm[2];
    cc[5] = comm[3];
    cc[6] = comm[4];
    int heart_count = 0;
    int spade_count = 0;
    int jack_count = 0;
    int diamond_count = 0;
    for (int i = 0; i < 7; i++) {
        switch(cc[i].suit) {
            case 'h': heart_count++;
                      break;
            case 's': spade_count++;
                      break;
            case 'j': jack_count++;
                      break;
            case 'd': diamond_count++;
                      break;
        }
    }
    char flush_suit;
    if (heart_count >= 5) {
        flush_suit = 'h';
    } else if (spade_count >= 5) {
        flush_suit = 's';
    } else if (jack_count >= 5) {
        flush_suit = 'j';
    } else if (diamond_count >= 5) {
        flush_suit = 'd';
    } else {
        return highest_flush;
    }
    for (int i = 0, j = 0; i < 7; i++) {
        if (cc[i].suit == flush_suit) {
           highest_flush[j] = cc[i];
           j++;
        }
    }
    return highest_flush;
}

struct Card* check_full(struct Player player, struct Card* comm) {
    static struct Card highest_full[5];
    for (int i = 0; i < 5; i++) {
        highest_full[i] = get_empty_card();
    }
    struct Card* is_triple = check_triple(player, comm);
    struct Card* is_pair;
    if (is_triple[0].player != -3) {
        is_pair = check_pair(player, comm, is_triple[0].rank);
        if (is_pair[0].player != -3) {
            highest_full[0] = is_triple[0];
            highest_full[1] = is_triple[1];
            highest_full[2] = is_triple[2];
            highest_full[3] = is_pair[0];
            highest_full[4] = is_pair[1];
        }
    }
    return highest_full;
}

struct Card* check_straight_flush(struct Player player, struct Card* comm) {
    static struct Card highest_straight_flush[5];
    for (int i = 0; i < 5; i++) {
        highest_straight_flush[i] = get_empty_card();
    }
    struct Card* is_flush= check_flush(player, comm);
    struct Card* is_straight;
    if (is_flush[0].player != -3) {
      is_straight = check_straight(player, comm);
      if (is_straight[0].player != -3) {
        highest_straight_flush[0] = is_flush[0];
        highest_straight_flush[1] = is_flush[1];
        highest_straight_flush[2] = is_flush[2];
        highest_straight_flush[3] = is_flush[3];
        highest_straight_flush[4] = is_flush[4];
      }
    }
    return highest_straight_flush;
}

