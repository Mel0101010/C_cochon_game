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
    printf(RED "Usage: %s <nombre de joueurs>\n" RESET, argv[0]);
    return 1;
  }

  srand(time(NULL)); 

  display_title();
  usleep(1000000); 

  struct Game game;
  game.number_of_players = atoi(argv[1]);

  if (game.number_of_players == 0) {
    printf(RED "Le nombre de joueurs doit être supérieur à 0\n" RESET);
    return 1;
  }

  printf(BOLD CYAN "Bienvenue au jeu du cochon avec %d joueurs!\n\n" RESET, game.number_of_players);

  struct Player players[game.number_of_players];
  for (int i = 0; i < game.number_of_players; i++) {
    printf(BOLD "Entrez le nom du joueur %d: " RESET, i + 1);
    scanf("%99s", players[i].name);
    players[i].bank = 0;
    players[i].turn = 0;
    players[i].n = 0;
    strcpy(players[i].color, colors[i % 6]); 

    printf("%sEst-ce que %s est un humain [1] ou un ordinateur [0]? %s",
           players[i].color, players[i].name, RESET);
    scanf("%d", &players[i].is_human);

    if (!players[i].is_human) {
        printf("Choose the bot level for %s (1: Easy, 2: Medium, 3: Hard): ", players[i].name);
        scanf("%d", &players[i].bot_level);
    }

    printf(GREEN "Joueur %s ajouté avec succès!\n\n" RESET, players[i].name);
  }

  printf(BOLD "\nPréparation du jeu" RESET);
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
