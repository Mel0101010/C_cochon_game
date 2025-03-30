#ifndef GAME_H
#define GAME_H

#include "player.h"

struct Game {
  struct Player *players;
  int number_of_players;
  int number_of_rounds;
};

int roll_dice(void);
void play_a_round(struct Player *players, struct Game game);

#endif
