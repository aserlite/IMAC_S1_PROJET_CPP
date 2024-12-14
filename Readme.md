# Tic Tac Toe - Projet C++

### Prérequis
1. **Système d'exploitation** : Le programme a été testé sous Linux (Ubuntu 24.04.1 LTS).
2. **Compilateur** : Le programme a été testé avec GCC 13.2.0.
3. **Librairies** : Ce projet ne dépend d'aucune librairie externe.

## Organisation du code

- **main.cpp** : Point d'entrée du programme. Propose un menu pour choisir entre le mode solo (contre l'IA) et le mode 1 contre 1.
- **play.hpp / play.cpp** : Gère la logique principale du jeu, comme la gestion des tours, des joueurs et des conditions de victoire.
- **genBoard.hpp / genBoard.cpp** : Implémente la classe `GenBoard` pour créer et manipuler la grille du jeu.
- **ai.hpp / ai.cpp** : Contient la logique de l'IA pour jouer contre un joueur humain en mode solo.

## Problèmes rencontrés et solutions

1. **Validation des entrées utilisateur** :
   - *Problème* : Entrer un texte au lieu de coordonnées causait un plantage.
   - *Solution* : Ajout de la vérification de l'entrée avec `std::cin.clear()` et `std::cin.ignore()`.

2. **Core dumps sur les index hors limites** :
   - *Problème* : Accès à une cellule en dehors des limites de la grille.
   - *Solution* : Vérification des bornes (à l'aide de `getSize()`) avant tout accès à la grille.

3. **Manque d'intelligence de l'IA** :
   - *Problème* : L'IA jouait des coups aléatoires sans stratégie.
   - *Solution* : Implémentation d'un minimax.

4. **Premier joueur fixe :**
    - *Problème* : Le premier joueur était toujours X, rendant les parties peu variées.
    - *Solution* : Utilisation d’un générateur aléatoire (rand() ou <random>) pour choisir aléatoirement le premier joueur. 

5. **Gestion des coups invalides par l'IA :**

    - *Problème* : L'IA pouvait retourner des coups invalides, causant des comportements imprévus.
    - *Solution* : Vérification des coordonnées retournées par l'IA avant de les appliquer au plateau.

## Fonctionnalités supplémentaires

- **IA Minimax** :
    - Implémentation de l'algorithme Minimax pour évaluer les meilleurs coups possibles.
    - Prise en compte des scénarios de victoire, défaite et égalité pour anticiper les mouvements adverses.

## Idées pour des améliorations futures
- Support pour des grilles plus grandes (4x4, 5x5).
- Interface graphique pour une meilleure expérience utilisateur.