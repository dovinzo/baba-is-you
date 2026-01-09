# Baba Is You

## Présentation

Ce projet a été réalisé dans le cadre du projet du cours de Programmation Objet Avancée (POO) du M1 d’Informatique de l’Université Paris Cité.

C'est une implémentation du jeu *Baba Is You*, un jeu de réflexion basé sur la manipulation de règles. Le joueur peut modifier les règles du monde en déplaçant des blocs de texte, ce qui change dynamiquement le comportement des objets.

L’objectif est d’atteindre la condition de victoire en réécrivant les règles plutôt qu’en se contentant de déplacer un personnage.

---

## Principe du jeu

Dans *Baba Is You*, les règles sont représentées sous forme de phrases construites avec des blocs de mots :

- `BABA IS YOU`

- `FLAG IS WIN`

- `WALL IS STOP`

Ces règles peuvent être **cassées, déplacées ou recomposées** pour :

- changer qui est contrôlable (`IS YOU`)

- modifier les collisions (`IS STOP`, `IS PUSH`)

- définir la condition de victoire (`IS WIN`)

Le gameplay repose entièrement sur cette mécanique.

---

## Compilation et exécution

### Prérequis

- Un système compatible avec `make`

- Un compilateur C/C++ installé (selon votre environnement)

- SFML 2.5.1

### Compilation & lancement

La compilation et l’exécution se font simplement avec :

```bash
make
```

Cette commande compile le projet **et lance automatiquement l’application**.

---

## Commandes lors du menu

| Touche              | Explication                            |
|:-------------------:|:--------------------------------------:|
| Flèche vers le haut | Se positionner sur le niveau précédent |
| Flèche vers le bas  | Se positionner sur le niveau suivant   |
| Q                   | Quitter l’application                  |
| Entrée              | Sélectionner le niveau                 |

---

## Commandes lors d'un niveau

| Touche                | Explication                             |
|:---------------------:|:---------------------------------------:|
| Flèche vers le haut   | Effectuer un déplacement vers le haut   |
| Flèche vers le bas    | Effectuer un déplacement vers le bas    |
| Flèche vers la gauche | Effectuer un déplacement vers la gauche |
| Flèche vers la droite | Effectuer un déplacement vers la droite |
| Q                     | Quitter l’application                   |
| P (Previous)          | Undo                                    |
| N (Next)              | Redo                                    |

---

Bon jeu !
