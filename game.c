#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int roll_dice(void) {
  int dice = 6;
  return rand() % dice + 1;
}

void play_a_round(struct Player *players, struct Game game) {
    int stop = 0;
    do {
        for (int i = 0; i < game.number_of_players; i++) {
            printf("\nIt's %s's turn, bank points %d\n", players[i].name, players[i].bank);
            players[i].turn = 0;

            char choice;
            while (1) {
                if (players[i].is_human) {
                    choice = play_human();
                } else {
                    switch (players[i].bot_level) { 
                        case 1:
                            choice = play_random_bot(&players[i], &game);
                            break;
                        case 2:
                            choice = play_medium_bot(&players[i], &game);
                            break;
                        case 3:
                            choice = play_hard_bot(&players[i], &game);
                            break;
                        default:
                            choice = play_medium_bot(&players[i], &game);
                            break;
                    }
                }

                if (choice == 'b') {
                    players[i].bank += players[i].turn;
                    printf("%s banks %d points. Total: %d\n", players[i].name, players[i].turn, players[i].bank);
                    break;
                }

                players[i].n = roll_dice();
                if (players[i].is_human){
                    printf("%s rolled a %d\n", players[i].name, players[i].n);
                }

                if (players[i].n == 1) {
                    printf("%s rolled a 1 and loses their turn points.\n", players[i].name);
                    players[i].turn = 0;
                    break;
                }

                players[i].turn += players[i].n;
                if (players[i].is_human){
                    printf("%s has %d points this turn and %d in total\n", players[i].name, players[i].turn, players[i].bank);
                }
            }

            if (players[i].bank >= 100) {
                printf("%s wins with %d points in %d rounds!\n", players[i].name, players[i].bank, game.number_of_rounds);
                stop = 1;
                break;
            }
        }
        game.number_of_rounds++;
    } while (stop == 0);
}

