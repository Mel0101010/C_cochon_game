#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "interface.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

void clear_screen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void animate_dice_roll(int result) {
  int temp;
  for (int i = 0; i < 10; i++) {
    temp = (rand() % 6) + 1;
    printf(YELLOW "\r⚄ Lancement du dé: %d " RESET, temp);
    fflush(stdout);
    usleep(100000); 
  }
  printf(BOLD YELLOW "\r⚄ Résultat du dé: %d " RESET, result);
  printf("\n");
}

void display_progress_bar(int points, int max_points, char *color) {
  int bar_width = 40;
  int progress = (int)((float)points / max_points * bar_width);

  printf("%s[", color);
  for (int i = 0; i < bar_width; i++) {
    if (i < progress)
      printf("█");
    else
      printf(" ");
  }
  printf("] %d/100%s\n", points, RESET);
}

void display_title() {
  clear_screen();
  printf(BOLD MAGENTA);
  printf("\n");
  printf(" ██████╗ ██╗ ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗\n");
  printf(" ██╔══██╗██║██╔════╝     ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n");
  printf(" ██████╔╝██║██║  ███╗    ██║  ███╗███████║██╔████╔██║█████╗  \n");
  printf(" ██╔═══╝ ██║██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
  printf(" ██║     ██║╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n");
  printf(" ╚═╝     ╚═╝ ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n");
  printf(RESET);
  printf("\n");
}

void display_scoreboard(struct Player *players, int num_players) {
  printf(BOLD BLUE "\n╔═══════════════════ TABLEAU DES SCORES ═══════════════════╗\n" RESET);
  for (int i = 0; i < num_players; i++) {
    printf(BLUE "║ " RESET);
    printf("%s%-15s%s : ", players[i].color, players[i].name, RESET);
    printf("%3d points ", players[i].bank);
    printf(BLUE "║\n" RESET);
  }
  printf(BOLD BLUE "╚═════════════════════════════════════════════════════════╝\n\n" RESET);
}

void celebrate_winner(char *name, char *color, int score) {
  clear_screen();
  printf("%s\n", color);
  printf("  🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 \n");
  printf("  🎊                                       🎊 \n");
  printf("  🎉       FÉLICITATIONS %-15s    🎉 \n", name);
  printf("  🎊       VOUS AVEZ GAGNÉ AVEC %3d POINTS!  🎊 \n", score);
  printf("  🎉                                       🎉 \n");
  printf("  🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 \n");
  printf(RESET);

  for (int i = 0; i < 5; i++) {
    printf("\r🎲 ");
    fflush(stdout);
    usleep(300000);
    printf("\r🎯 ");
    fflush(stdout);
    usleep(300000);
  }
  printf("\n\n");
}
