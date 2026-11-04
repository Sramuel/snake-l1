/**
 * @file project_game.h
 * @brief
 * Jeu.
 *
 * @details
 * Type utilisé pour représenter un jeu unique et fonctions associées.
 */

#ifndef _GAME_H_
#define _GAME_H_

 /*   ____    _    __  __ _____ ____   */
 /*  / ___|  / \  |  \/  | ____/ ___|  */
 /* | |  _  / _ \ | |\/| |  _| \___ \  */
 /* | |_| |/ ___ \| |  | | |___ ___) | */
 /*  \____/_/   \_\_|  |_|_____|____/  */

#include <stdbool.h>
#include <stdlib.h>
#include "project_snake.h"
#include "project_board.h"
#include "project_score.h"
#include "project_tools.h"

/**
 * @brief
 * Type utilisé pour représenter un seul jeu.
 *
 * @remark
 * Dans le tableau snakes_array, les pointeurs vers les serpents sont stockés dans l'ordre suivant :
 * - Les cellules 0 à nb_ais-1 contiennent les pointeurs vers les serpents contrôlés par l'ordinateur.
 * - Les cellules nb_ais et nb_ais + 1 contiennent les pointeurs vers les deux joueurs (s'ils sont dans le jeu).
 */
typedef struct game {
  board *b; //!< Le plateau de jeu.

  int nb_ais; //!< Le nombre de serpents contrôlés par l'ordinateur dans le jeu
              //!< (0 ou plus).
  int nb_players; //!< Le nombre de joueurs dans le jeu (0, 1 ou 2).
  int nb_alive;   //!< Le nombre de serpents encore en vie (au plus nb_players +
                  //!< nb_ais).
  int nb_turns;   //!< Le nombre de tours joués dans le jeu depuis le début.

  snake **snakes_array; //!< Le tableau contenant tous les serpents du jeu
                        //!< (taille "nb_ais + nb_players"). Les joueurs (le cas
                        //!< échéant) sont stockés à la fin du tableau.
} game;

/**
 * @brief
 * Alloue un nouveau jeu sur le tas.
 *
 * @return
 * Un pointeur vers le nouveau jeu.
 */
game *new_game(
    int hsize,    //!< Taille horizontale du plateau.
    int vsize,    //!< Taille verticale du plateau.
    mask *m,   //!< Masque utilisé pour créer le plateau (NULL si pas de masque).
    int nh,    //!< Nombre de joueurs humains (0, 1 ou 2)
    int ns,    //!< Nombre de serpents contrôlés par l'ordinateur.
    int vs,    //!< Vitesse initiale commune des serpents.
    int ls     //!< Longueur initiale commune des serpents.
);

/**
 * @brief
 * Supprime un jeu.
 */
void delete_game(game *g //!< Le jeu.
);

/**
 * @brief
 * Met à jour la direction de déplacement du premier joueur (s'il existe).
 *
 * @remark
 * La direction n'est PAS mise à jour si l'une des deux conditions suivantes est remplie :
 * - Le serpent est mort, ou,
 * - La nouvelle direction est celle que le serpent a utilisée pour entrer dans sa cellule actuelle (le serpent ne peut pas faire demi-tour).
 */
void set_direction_player1(game *g,      //!< Le jeu.
                           direction dir //!< La nouvelle direction.
);

/**
 * @brief
 * Met à jour la direction de déplacement du deuxième joueur (s'il existe).
 *
 * @remark
 * La direction n'est PAS mise à jour si l'une des deux conditions suivantes est remplie :
 * - Le serpent est mort, ou,
 * - La nouvelle direction est celle que le serpent a utilisée pour entrer dans sa cellule actuelle (le serpent ne peut pas faire demi-tour).
 */
void set_direction_player2(game *g,      //!< Le jeu.
                           direction dir //!< La nouvelle direction.
);

/**
 * @brief
 * Déplace tous les serpents dans un jeu et met à jour l'état du jeu.
 *
 * @remark
 * Un pointeur vers un score_table est également donné en paramètre. Si un serpent meurt à la suite
 * du mouvement, ses valeurs de score doivent être remplies dans ce score_table (pour le jeu en cours).
 * Voir le fichier project_score.h pour plus d'informations sur les scores.
 *
 * @remark
 * Pour récupérer le temps qu'un serpent a passé en vie avant de mourir (pour son score), vous pouvez
 * utiliser la fonction get_time_counter() définie dans project_tools.h qui retourne le temps écoulé depuis le
 * début du jeu en millisecondes. Notez que le temps doit être rempli en secondes dans le
 * score_table.
 *
 * @remark
 * Si un pointeur NULL est donné pour le score_table, les scores ne sont pas mis à jour.
 */
void implement_turn_all_snakes(game *g,        //!< Le jeu.
                               score_table *st //!< Les scores du jeu.
);

#endif
