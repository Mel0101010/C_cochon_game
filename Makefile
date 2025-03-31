CC = gcc

CFLAGS = -Wall -Wextra -pedantic

TARGET = pig_game

SRCS = main.c game.c player.c interface.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

mrproper: clean
	rm -f *~ \#*

help:
	@echo "Makefile pour le jeu Pig"
	@echo "Règles disponibles :"
	@echo "  all     : Compile le programme"
	@echo "  clean   : Supprime les fichiers objets et l'exécutable"
	@echo "  mrproper: Supprime tous les fichiers générés"
	@echo "  help    : Affiche cet écran d'aide"

