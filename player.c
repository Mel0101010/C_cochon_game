#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "game.h"

char play_human(void) {
  char input;
  printf("Continue [r]olling, or [b]bank? ");
  scanf(" %c", &input);
  return input;
}

char play_random_bot(struct Player *p, struct Game *g) {
    return (rand() % 2 == 0) ? 'r' : 'b';
}

char play_medium_bot(struct Player *p, struct Game *g) {
    if (p->turn + p->bank >= 100 || p->turn > 15) {
        return 'b';
    }
    return 'r';
}

char play_hard_bot(struct Player *p, struct Game *g) {
    int max_bank = 0;
    for (int i = 0; i < g->number_of_players; i++) {
        if (g->players[i].bank > max_bank) {
            max_bank = g->players[i].bank;
        }
    }

    if (p->bank < max_bank - 20) {
        return 'r';
    }

    if (p->turn + p->bank >= 100 || p->turn > 10) {
        return 'b';
    }
    return 'r';
}