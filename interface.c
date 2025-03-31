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
  char *dice_faces[] = {"⚀", "⚁", "⚂", "⚃", "⚄", "⚅"};
  char *colors[] = {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN};
  
  printf(BOLD "\nRolling the dice " RESET);
  for (int i = 0; i < 3; i++) {
    printf(".");
    fflush(stdout);
    usleep(100000);  // Réduit de 200000 à 100000 (0.1 seconde)
  }
  printf("\n");
  
  for (int i = 0; i < 8; i++) {
    int temp = (rand() % 6);
    printf("%s\r%s %s" RESET, colors[i % 6], dice_faces[temp], i % 2 == 0 ? "      " : "...   ");
    fflush(stdout);
    usleep(75000);   // Réduit de 150000 à 75000 (0.075 seconde)
  }
  
  printf(BOLD YELLOW "\r%s Result: %d " RESET, dice_faces[result-1], result);
  printf("\n");
  fflush(stdout);
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
  clear_screen();
  printf(BOLD BLUE "\n╔═══════════════════ SCOREBOARD ═══════════════════╗\n" RESET);
  fflush(stdout);
  
  struct Player sorted_players[num_players];
  for (int i = 0; i < num_players; i++) {
    sorted_players[i] = players[i];
  }
  
  for (int i = 0; i < num_players - 1; i++) {
    for (int j = 0; j < num_players - i - 1; j++) {
      if (sorted_players[j].bank < sorted_players[j+1].bank) {
        struct Player temp = sorted_players[j];
        sorted_players[j] = sorted_players[j+1];
        sorted_players[j+1] = temp;
      }
    }
  }
  
  for (int i = 0; i < num_players; i++) {
    usleep(300000);
    printf(BLUE "║ " RESET);
    
    char *rank_marker = "";
    if (i == 0) rank_marker = BOLD YELLOW "🥇 " RESET;
    else if (i == 1) rank_marker = BOLD WHITE "🥈 " RESET;
    else if (i == 2) rank_marker = BOLD RED "🥉 " RESET;
    
    printf("%s%s%-15s%s : ", rank_marker, sorted_players[i].color, sorted_players[i].name, RESET);
    printf("%3d points ", sorted_players[i].bank);
    printf(BLUE "║\n" RESET);
    fflush(stdout);
  }
  
  printf(BOLD BLUE "╚═════════════════════════════════════════════════════════╝\n\n" RESET);
  fflush(stdout);
  usleep(500000);
}

void celebrate_winner(char *name, char *color, int score) {
  clear_screen();
  
  for (int frame = 0; frame < 3; frame++) {
    clear_screen();
    printf("%s\n", color);
    if (frame == 0 || frame == 2) {
      printf("  🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 \n");
      printf("  🎊                                       🎊 \n");
      printf("  🎉       CONGRATULATIONS %-15s    🎉 \n", name);
      printf("  🎊       YOU WON WITH %3d POINTS!       🎊 \n", score);
      printf("  🎉                                       🎉 \n");
      printf("  🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 🎊 🎉 \n");
    } else {
      printf("  ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ \n");
      printf("  ⭐                                       ⭐ \n");
      printf("  ✨       CONGRATULATIONS %-15s    ✨ \n", name);
      printf("  ⭐       YOU WON WITH %3d POINTS!       ⭐ \n", score);
      printf("  ✨                                       ✨ \n");
      printf("  ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ ⭐ ✨ \n");
    }
    printf(RESET);
    fflush(stdout);
    usleep(500000);
  }

  for (int i = 0; i < 5; i++) {
    printf("\r🎲 ");
    fflush(stdout);
    usleep(300000);
    printf("\r🎯 ");
    fflush(stdout);
    usleep(300000);
  }
  printf("\n\n");
  fflush(stdout);
}
