#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>
#include <time.h>
#include <stdlib.h>

#include "poker/poker.h"
#include "image/image.h"
#include "poker/player.h"
#include "poker/card.h"

void create_image();
void run_game();
void print_hands(struct Player* players, int player_count);
void print_community(struct Card* community);
void print_players(struct Player* players, int player_count);

int main(int argc, char *argv[]) {
    srand(time(NULL));

  /*initscr();
  cbreak();
  noecho();
  start_color();
  refresh();
  read_image("image2.txt");
  refresh();
  getch();
  endwin();*/

    run_game();

    return 0;
}

void run_game() {
    struct Card* deck_ptr;
    struct Player* player_ptr;
    struct Card* comm_ptr;
    int num_players = 4;
    deck_ptr = create_deck();
    player_ptr = create_players(num_players, deck_ptr);
    print_hands(player_ptr, num_players);
    comm_ptr = create_community(deck_ptr);
    print_community(comm_ptr);
    determine_winner(player_ptr, num_players, comm_ptr);
    print_players(player_ptr, num_players);
}

void print_players(struct Player* players, int player_count) {
    for (int i = 0; i < player_count; i++) {
        if (players[i].winning[0].player != -3) {
            printf("player %d WINNING: [%c%d", players[i].player, players[i].winning[0].suit, players[i].winning[0].rank);
            for (int k = 1; k < 5; k++) {
                if (players[i].winning[k].player == -3) {
                    printf(", X");
                } else {
                    printf(", %c%d", players[i].winning[k].suit, players[i].winning[k].rank);
                }
            }
            printf("]\n");
        }
    }
}

void print_hands(struct Player* players, int player_count) {
   for (int i = 0; i < player_count; i++) {
        printf("player %d [%c%d, %c%d]\n", players[i].player, players[i].hole[0].suit, players[i].hole[0].rank, players[i].hole[1].suit, players[i].hole[1].rank);
    }
}

void print_community(struct Card* community) {
    for (int i = 0; i < 5; i++) {
        printf("%c%d\n", community[i].suit, community[i].rank);
    }
}

void create_image() {
  attron(COLOR_PAIR(1));
  mvwprintw(stdscr, 1, 1, "%s", "  ");
  attroff(COLOR_PAIR(1));
  refresh();
}
