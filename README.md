# C_cochon_game
Le Pig Game est un jeu de dés simple où les joueurs peuvent choisir de continuer à lancer les dés pour accumuler des points ou de "banquer" leurs points pour les sécuriser. Le premier joueur à atteindre 100 points gagne la partie.

## Fonctionnalités

- **Modes de Jeu** : Jouez contre des bots avec trois niveaux de difficulté : facile, moyen et difficile.
- **Interface Colorée** : Utilisation de couleurs et d'animations pour rendre le jeu plus attrayant.
- **Affichage du Score** : Suivez les scores des joueurs avec une barre de progression.
- **Célébration du Gagnant** : Animation spéciale pour célébrer le gagnant à la fin de la partie.

## Prérequis

- Compilateur GCC
- Make (pour la compilation avec le Makefile)

## Installation

1. Clonez ce dépôt sur votre machine locale :

   ```sh
   git clone <URL_DU_DEPOT>
   cd pig-game
   ```

2. Compilez le projet en utilisant Make :
```sh
make
```

3. Exécutez le jeu :

```sh
./pig_game <nombre_de_joueurs>
```

Remplacez <nombre_de_joueurs> par le nombre de joueurs souhaité (humains et bots).

## Structure du projet 


- main.c : Point d'entrée principal du programme.
- game.c et game.h : Gestion de la logique du jeu.
- player.c et player.h : Gestion des joueurs et des bots.
- interface.c et interface.h : Fonctions d'interface utilisateur pour l'affichage et les animations.
- Makefile : Fichier de compilation pour construire le projet.

## Utilisation


- Lancez le jeu en spécifiant le nombre de joueurs.
- Suivez les instructions à l'écran pour configurer les joueurs et choisir les niveaux de difficulté des bots.
- Profitez du jeu et essayez de battre vos adversaires !

## Nettoyage

Pour nettoyer les fichiers générés par la compilation, utilisez :
```sh
make clean
```

Pour supprimer tous les fichiers générés, y compris les fichiers temporaires, utilisez :
```sh
make mrproper
```