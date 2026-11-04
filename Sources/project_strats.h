/**
 * @file project_strats.h
 * @brief
 * Fonctions de stratégie pour les IA.
 *
 * @details
 * Ce sont les fonctions utilisées pour déterminer les mouvements des serpents contrôlés par l'IA. Une fonction de stratégie
 * prend en entrée le jeu et l'index du serpent à modifier. Elle choisit la direction que le serpent
 * utilisera pour sortir de la cellule actuelle et assigne cette direction au champ "move" du serpent.
 *
 * @attention
 * Un serpent ne peut pas sortir d'une cellule en revenant à la cellule d'où il vient. Par conséquent, la fonction de stratégie doit
 * choisir parmi au maximum trois directions (la quatrième direction indisponible est celle d'où vient le serpent).
 *
 * @remark
 * Vous devez écrire les fonctions de stratégie. En revanche, vous ne devez PAS les appeler vous-même. En effet,
 * les stratégies sont appelées dans la boucle de jeu qui est déjà écrite. Chaque tour de la boucle de jeu consiste
 * en les quatre étapes suivantes :
 * 1. Utiliser une fonction de génération pour générer de nouveaux objets (la fonction est choisie lors de la création du jeu).
 * 2. Mettre à jour les directions de déplacement des serpents contrôlés par les joueurs en fonction des entrées du clavier.
 * 3. Appliquer la fonction de stratégie pour mettre à jour les directions de déplacement des serpents contrôlés par l'IA (les fonctions sont choisies lors de la création du jeu).
 * 4. Implémenter le tour pour tous les serpents en appelant la fonction "implement_turn_all_snakes".
 */

#ifndef _PROJECT_STRATS_H_
#define _PROJECT_STRATS_H_

 /*  ____  _             _             _              __              _   _               _    ___      */
 /* / ___|| |_ _ __ __ _| |_ ___  __ _(_) ___  ___   / _| ___  _ __  | |_| |__   ___     / \  |_ _|___  */
 /* \___ \| __| '__/ _` | __/ _ \/ _` | |/ _ \/ __| | |_ / _ \| '__| | __| '_ \ / _ \   / _ \  | |/ __| */
 /*  ___) | |_| | | (_| | ||  __/ (_| | |  __/\__ \ |  _| (_) | |    | |_| | | |  __/  / ___ \ | |\__ \ */
 /* |____/ \__|_|  \__,_|\__\___|\__, |_|\___||___/ |_|  \___/|_|     \__|_| |_|\___| /_/   \_\___|___/ */
 /*                              |___/                                                                  */

#include <stdlib.h>
#include <stdbool.h>
#include "project_game.h"
#include "project_tools.h"

/**
 * @brief
 * Noms internes des stratégies disponibles.
 *
 * @details
 * Pour ajouter une nouvelle fonction de stratégie, vous devez ajouter un nouveau nom interne pour cette stratégie,
 * à la fin de la liste (avant STRAT_SIZE). Ensuite, vous devez compléter les trois étapes suivantes :
 * 1) Écrire la fonction de stratégie.
 * 2) Ajouter le nom de la fonction à la fin du tableau strategy_funs dans project_objgen.c (ce tableau contient toutes les fonctions de stratégie).
 * 3) Ajouter une chaîne décrivant la stratégie à la fin du tableau strategy_names dans project_objgen.c (cette chaîne sera affichée dans l'interface).
 */
typedef enum {
    STRAT_EMPTY,        //!< Ne fait rien
    STRAT_CLOSESTFRUIT, //!< Essaie d'atteindre le fruit le plus proche.
    STRAT_SCORE,        //!< Essaie de maximiser le score.
    STRAT_STUDENTS,     //!< Essaie de maximiser le nombre d'étudiants mangés.
    STRAT_DISTANCE,     //!< Essaie de maximiser la distance parcourue.
    STRAT_TIME,         //!< Essaie de maximiser le temps de survie.
    STRAT_SIZE,         //!< Nombre de stratégies
} strat;

/**
 * @brief Tableau de fonctions de stratégie.
 */
extern void (*strat_funs[STRAT_SIZE]) (game*, int);

/**
 * @brief Tableau de noms de stratégies.
 */
extern const char* strat_names[STRAT_SIZE];

/****************************/
/*+ Fonctions de stratégie +*/
/****************************/

/**
 * @brief
 * Une stratégie qui ne fait rien.
 */
void empty_strategy(game *g, // Le jeu.
                    int i    // L'index du serpent.
);

/**
 * @brief
 * La stratégie qui essaie toujours d'atteindre le fruit le plus proche.
 */
void closest_fruit_strategy(game *g, // Le jeu.
                            int i    // L'index du serpent.
);

/**
 * @brief
 * La stratégie qui essaie de maximiser le score avant tout.
 */
void score_strategy(game *g, // Le jeu.
                    int i    // L'index du serpent.
);

/**
 * @brief
 * La stratégie qui essaie de maximiser le nombre d'étudiants mangés avant tout.
 */
void students_strategy(game *g, // Le jeu.
                       int i    // L'index du serpent.
);

/**
 * @brief
 * La stratégie qui essaie de maximiser la distance parcourue avant tout.
 */
void distance_strategy(game *g, // Le jeu.
                       int i    // L'index du serpent.
);

/**
 * @brief
 * La stratégie qui essaie de maximiser le temps de survie avant tout.
 */
void time_strategy(game *g, // Le jeu.
                   int i    // L'index du serpent.
);

#endif // _PROJECT_STRATS_H_
