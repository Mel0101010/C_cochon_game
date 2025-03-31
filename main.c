#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "interface.h"
#include "game.h"

int main(int argc, char **argv) {
  char *colors[] = {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN};

  if (argc != 2) {
    printf(RED "Usage: %s <number of players>\n" RESET, argv[0]);
    return 1;
  }

  srand(time(NULL)); 

  display_title();
  usleep(1000000); 

  struct Game game;
  game.number_of_players = atoi(argv[1]);

  if (game.number_of_players == 0) {
    printf(RED "The amount of players should be higher than 0\n" RESET);
    return 1;
  }

  printf(BOLD CYAN "Welcome to PigGame with %d players!\n\n" RESET, game.number_of_players);

  struct Player players[game.number_of_players];
  for (int i = 0; i < game.number_of_players; i++) {
    printf(BOLD "Type the name of the player %d: " RESET, i + 1);
    scanf("%99s", players[i].name);
    players[i].bank = 0;
    players[i].turn = 0;
    players[i].n = 0;
    strcpy(players[i].color, colors[i % 6]); 

    printf("%sIs %s a human [1] or a bot [0]? %s",
           players[i].color, players[i].name, RESET);
    scanf("%d", &players[i].is_human);

    if (!players[i].is_human) {
        printf("Choose the bot level for %s (1: Easy, 2: Medium): ", players[i].name);
        scanf("%d", &players[i].bot_level);
        if (players[i].bot_level != 1 && players[i].bot_level != 2) {
            players[i].bot_level = 2;
        }
    }

    printf(GREEN "Player %s successfully added!\n\n" RESET, players[i].name);
  }

  printf(BOLD "\nGame loading..." RESET);
  for (int i = 0; i < 5; i++) {
    printf(".");
    fflush(stdout);
    usleep(300000);
  }
  printf("\n\n");

  clear_screen();
  play_a_round(players, game);

  return 0;
}
