#ifndef INTERFACE_H
#define INTERFACE_H

#include "player.h"
#include "game.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

void clear_screen();
void animate_dice_roll(int result);
void display_progress_bar(int points, int max_points, char *color);
void display_title();
void display_scoreboard(struct Player *players, int num_players);
void celebrate_winner(char *name, char *color, int score);

#endif
