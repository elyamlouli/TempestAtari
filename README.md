# TEMPEST ATARI

## Introduction
Ce projet nous a amené à réaliser un remake du célèbre jeu Tempest de Atari, apparu en 1981 sur les bornes d'arcade. 

Ce jeu a été développé en C++, et l'affichage est géré par la librairie SDL2.

Le jeu est en anglais. Il aussi est possible de jouer avec la musique originale du jeu.

## Rappel des règles du jeu
Dans ce jeu, vous jouez seul, et votre objectif est de réaliser le maximum de points. Vous avez au total 5 vies. Des ennemies viennent vers vous, il s'agit de leur tirer dessus avant qu'ils arrivent à votre base. Vous gagnez des points à chaque ennemie détruit. Vous disposez aussi d'une arme puissante (le superzapper), utilisable une seule fois par niveau, qui détruit tous les ennemis présents d'un seul coup. Dans cette version du jeu, vous pourrez réaliser au maximum 4 niveaux. Dès que vous n'avez plus de vie ou que vous avez compléter les 4 niveaux, la partie est finie.

## Organisation du projet
Depuis la racine du projet, vous pouvez trouver:
- Le `Makefile` : permet de compiler le projet
- L'exécutable `tempest` (si le projet est compilé) : permet de jouer au jeu (fichiers binaires)
- The dossier `src` : ensemble des fichiers sources du projet (fichiers C++)
- Le dossier `obj` (si le projet est compilé) : ensemble des fichiers objets du projet (fichiers O)
- Le dossier `include` : ensemble des fichiers sources du projet (fichiers HPP)
- Le dossier `mp3` : ensemble des fichiers sons (fichiers MP3)
- Le dossier `font` : ensemble des fichiers de style de texte (fichiers TFF)
- Le fichier `README.md` : ce présent document, conenant des informations essentielles à la compréhension du projet

## Compilation et lancement du jeu
Afin de jouer à notre jeu Tempest, vous devez réaliser les étapes suivantes :
- Compiler le projet en utilisant la commande `make` depuis la racine du projet
- Lancer le jeu en utilisant la commande `./tempest` depuis la racine du projet

Vous pouvez aussi effacer les fichiers objets, le dossier `obj` et l'exécutable `tempest` en utilisant la commande `make clean`.

Pour naviguer dans le menu, il suffit de tapper sur les touches qui vous intéresse. Les règles sont expliquées dans la partie `Display Help`.

Si vous souhaitez quitter le jeu, appuyez sur la touche `echap`.


## Contributeurs
Ce projet a été réalisé par :
- Vagnona ANDRIANANDRASANA-DINA
- Théo BASTIEN
