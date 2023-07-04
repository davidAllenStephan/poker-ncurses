#include "image.h"
#include <stdlib.h>
#include <stdio.h>

void read_image(char file[]) {
  FILE* ptr;
  char ch[300];

  ptr = fopen(file, "r");
  while(fgets(ch, sizeof(ch), ptr) != NULL) {
    printf("%s", ch);
    printf("\n\r");
  }

  fclose(ptr);
}
