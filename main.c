#include <curses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "poker/poker.h"

#define COUNT 52
#define SUITS 4
#define RANKS 13

void create_image();
void read_image();

int main(int argc, char *argv[]) {

  int DECK[4][13] = {{1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4,5,6,7,8,9,10,11,12}};

  initscr();
  cbreak();
  noecho();
  start_color();
  refresh();
  read_image();
  refresh();
  getch();
  endwin();

  return 0;
}
void read_image() {
  FILE* ptr;
  char ch[300];

  ptr = fopen("image2.txt", "r");
  while(fgets(ch, sizeof(ch), ptr) != NULL) {
    printf("%s", ch);
    printf("\n\r");
  }

  fclose(ptr);
}

void create_image() {
  attron(COLOR_PAIR(1));
  mvwprintw(stdscr, 1, 1, "%s", "  ");
  attroff(COLOR_PAIR(1));
  refresh();
}
