#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For usleep
#include "game.h"
#include "interface.h" // For colors and animations

int roll_dice(void) {
  int dice = 6;
  int result = rand() % dice + 1;
  animate_dice_roll(result); // Add dice roll animation
  return result;
}

void play_a_round(struct Player *players, struct Game game) {
    game.players = players;
    game.number_of_rounds = 0;
    
    int stop = 0;
    int winner_index = -1;
    
    do {
        for (int i = 0; i < game.number_of_players; i++) {
            printf("\n%sIt's %s%s%s's turn, banked points: %s%d%s\n", 
                   BOLD, players[i].color, players[i].name, RESET, 
                   BOLD, players[i].bank, RESET);
            
            // Display progress bar
            display_progress_bar(players[i].bank, 100, players[i].color);
            
            players[i].turn = 0;

            char choice;
            while (1) {
                if (players[i].is_human) {
                    choice = play_human();
                } else {
                    switch (players[i].bot_level) { 
                        case 1:
                            choice = play_random_bot(&players[i]);
                            break;
                        case 2:
                        default:
                            choice = play_medium_bot(&players[i]);
                            break;
                    }
                }

                if (choice == 'b') {
                    players[i].bank += players[i].turn;
                    printf("%s%s banks %d points. Total: %s%d%s\n", 
                           players[i].color, players[i].name, players[i].turn, 
                           BOLD, players[i].bank, RESET);
                    fflush(stdout);
                    break;
                }

                players[i].n = roll_dice();
                if (players[i].is_human) {
                    printf("%s%s rolled a %s%d%s\n", 
                           players[i].color, players[i].name, 
                           BOLD, players[i].n, RESET);
                }

                if (players[i].n == 1) {
                    printf(RED BOLD "%s rolled a 1 and loses turn points.%s\n", 
                           players[i].name, RESET);
                    players[i].turn = 0;
                    fflush(stdout);
                    usleep(1000000); // Dramatic pause
                    break;
                }

                players[i].turn += players[i].n;
                if (players[i].is_human){
                    printf("%s has %s%d%s points this turn and %s%d%s in total\n", 
                           players[i].name, BOLD, players[i].turn, RESET, 
                           BOLD, players[i].bank, RESET);
                }
            }

            if (players[i].bank >= 100) {
                printf(BOLD GREEN "\n%s wins with %d points in %d rounds!\n" RESET, 
                       players[i].name, players[i].bank, game.number_of_rounds);
                fflush(stdout);
                winner_index = i;
                stop = 1;
                break;
            }
        }
        game.number_of_rounds++;
    } while (stop == 0);
    
    // Display results at the end of the game
    if (winner_index >= 0) {
        printf("\n%sPress Enter to see final results...%s", BOLD, RESET);
        getchar(); // Consume previous newline character
        getchar(); // Wait for Enter
        
        // Display scoreboard
        display_scoreboard(players, game.number_of_players);
        
        // Celebrate winner
        celebrate_winner(players[winner_index].name, 
                         players[winner_index].color, 
                         players[winner_index].bank);
    }
}

