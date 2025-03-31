#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.h"
#include "game.h"
#include "interface.h"

char play_human(void) {
  char input;
  printf(CYAN "Continue [" BOLD "r" RESET CYAN "]olling, or [" BOLD "b" RESET CYAN "]ank? " RESET);
  fflush(stdout);
  scanf(" %c", &input);
  return input;
}

char play_random_bot(struct Player *p) {
    printf("%s%s is thinking", p->color, p->name);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        usleep(200000);
    }
    
    char choice = (rand() % 2 == 0) ? 'r' : 'b';
    printf("\n%s%s (Easy Bot) chooses to %s%s\n", 
           p->color, p->name, 
           choice == 'r' ? GREEN "continue rolling" RESET : YELLOW "bank" RESET, 
           RESET);
    fflush(stdout);
    return choice;
}

char play_medium_bot(struct Player *p) {
    printf("%s%s is analyzing", p->color, p->name);
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        usleep(300000);
    }
    
    char choice;
    if (p->turn + p->bank >= 100 || p->turn > 15) {
        choice = 'b';
    } else {
        choice = 'r';
    }
    
    printf("\n%s%s (Medium Bot) chooses to %s%s\n", 
           p->color, p->name,
           choice == 'r' ? GREEN "continue rolling" RESET : YELLOW "bank" RESET, 
           RESET);
    fflush(stdout);
    return choice;
}