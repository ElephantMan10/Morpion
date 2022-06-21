# Introduction

## Tic-Tac-Toe

Le *tic-tac-toe*, aussi appelé « *morpion* » est un jeu de réflexion se pratiquant à deux joueurs au tour par tour dont le but est de créer le premier un alignement.
Les joueurs s'affrontent sur une grille de 3x3 et ont comme symbole **o** ou **x**. Normalement le joueur **x** commence mais j'ai decidé que c'est l'inverse.

## Variantes

### 10x10

Dans cette variante, les joueurs s'affrontent dans une grille de taille 10x10 (comme son nom l'indique) et doivent créer un alignement de 5 symboles (les mêmes que pour le Tic-Tac-Toe).

### 15x15

Dans cette variante, les joueurs s'affrontent dans une grille de taille 15x15 (comme son nom l'indique) et doivent créer un alignement de 6 symboles (les mêmes que pour le Tic-Tac-Toe).

## 7x6

Dans cette variante, les joueurs s'affrontent dans une grille de taille 7x6 (comme son nom l'indique) et doivent créer un alignement de 4 symboles (les mêmes que pour le Tic-Tac-Toe).
Pour cette variante, je me suis tout simplement inspiré d'un *Puissance 4* (que j'ai egalement codé).

# Installation

Tout d'abord, verifiez que vous avez bien les bibliothèques sdl et sdl_ttf installées.
Sinon tapez les commandes : `sudo apt-get install libsdl1.2-dev` et `sudo apt-get install libsdl-ttf1.2-dev`.
Puis à la racine du projet tapez : `make && make jeu`.
Enfin executez le fichier *morpion*.