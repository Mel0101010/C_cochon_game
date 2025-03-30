#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

struct Player {
  char name[100];
  int bank;
  int turn;
  int n;
  int is_human;
  int rank;
  int bot_level;
  char color[20];
};

struct Game;

char play_human(void);
char play_random_bot(struct Player *p, struct Game *g);
char play_medium_bot(struct Player *p, struct Game *g);
char play_hard_bot(struct Player *p, struct Game *g);


#endif
