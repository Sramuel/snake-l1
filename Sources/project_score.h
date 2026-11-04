/**
 * @file project_score.h
 * @brief
 * Scores.
 *
 * @details
 * Type utilisé pour représenter les scores d'un jeu.
 */


#ifndef _PROJECT_SCORE_H_
#define _PROJECT_SCORE_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "project_snake.h"
#include "project_tools.h"


 /*  ____                           */
 /* / ___|  ___ ___  _ __ ___  ___  */
 /* \___ \ / __/ _ \| '__/ _ \/ __| */
 /*  ___) | (_| (_) | | |  __/\__ \ */
 /* |____/ \___\___/|_|  \___||___/ */

/**
 * @brief
 * Type utilisé pour représenter les différents scores.
 */
typedef enum {
    SC_MAIN, //!< Le score principal du serpent.
    SC_STUDENTS, //!< Le nombre d'étudiants que le serpent a mangés.
    SC_LENGTH, //!< La longueur du serpent lorsqu'il est mort.
    SC_VISITED, //!< Le nombre de cellules que le serpent a visitées avant de mourir.
    SC_TIME, //!< Le temps que le serpent a passé en vie (donné en secondes).
    SC_SIZE //!< Le nombre de types de scores.
} score_type;



/**
 * @brief
 * Type utilisé pour représenter les valeurs de score d'un seul serpent après un seul jeu.
 */
typedef struct {
    bool filled; //!< Vrai si le score a été rempli (faux sinon).
    score_type vals[SC_SIZE]; //!< Tableau de taille SC_SIZE qui contient les valeurs des différents scores.
} single_score;


/**
 * @brief Type utilisé pour représenter les scores de chaque jeu dans une série de jeux.
 *
 * @details
 * Dans l'interface, il est possible de créer une série de plusieurs jeux consécutifs. Ce type est utilisé pour
 * stocker les scores de chaque serpent dans chaque jeu de la série ainsi que les scores finaux de chaque serpent (la
 * somme des scores du serpent dans chaque jeu).
 *
 * @details
 * Le tableau des scores est un tableau à deux dimensions de taille nb_snakes x (nb_games + 1). Si i est l'index d'un
 * serpent (dans le tableau des scores) et j < nb_game est l'index d'un jeu, alors scores[i][j] contient un pointeur vers
 * le score du serpent i dans le jeu j (qui sont remplis après que ce jeu soit joué). De plus, scores[i][nb_game]
 * contient un pointeur vers le score final du serpent i : la somme des scores du serpent dans chaque jeu (qui
 * est rempli après que tous les jeux soient joués).
 *
 * @remark
 * Les serpents ne sont pas nécessairement stockés dans le même ordre que dans le jeu (cela est dû au fait qu'il est possible de
 * trier les tableaux de scores selon l'un des types de scores). La correspondance avec les indices des serpents
 * dans le jeu est donnée par les tableaux game_to_score et score_to_game.
 */
typedef struct {
  int nb_snakes; //!< Nombre total de serpents.
  int nb_games;  //!< Le nombre total de jeux dans cette série.
  int cu_game;   //!< Le numéro du jeu actuellement en cours.
  single_score ***scores; 
               //!< Tableau à deux dimensions. Taille nb_snakes x (nb_games +
               //!< 1). Contient les scores de chaque serpent dans chaque jeu,
               //!< ainsi que le score final de chaque serpent.

  int *game_to_score; //!< Tableau de taille nb_snakes. Si k est l'index d'un
                      //!< serpent dans le jeu, alors game_to_score[k] est
                      //!< l'index du même serpent dans le tableau des scores.
  int *score_to_game; //!< Tableau de taille nb_snakes. Si i est l'index d'un
                      //!< serpent dans le tableau des scores, alors
                      //!< score_to_game[i] est l'index du même serpent dans le
                      //!< jeu.
} score_table;

/**
 * @brief
 * Alloue un nouveau score_table sur le tas.
 *
 * @remark
 * Les scores des serpents ne sont pas initialisés (la valeur booléenne filled est définie sur false
 * pour chaque score). Les scores seront remplis après chaque jeu joué.
 *
 * @return
 * Un pointeur vers le nouveau score_table.
 */
score_table *new_score_table(int n_g, //!< Le nombre de jeux.
                             int n_s  //!< Le nombre total de serpents.
);

/**
 * @brief
 * Supprime un score_table.
 */
void delete_score_table(
    score_table* st //!< Le score_table.
);

/**
 * @brief
 * Passe au jeu suivant dans la série.
 *
 * @details
 * Incrémente le champ cu_game du score_table.
 *
 * @remark
 * Cette fonction est appelée automatiquement par l'interface.
 */
void move_to_next_game(score_table *st //!< Le score_table.
);

/**
 * @brief
 * Met à jour le score d'un seul serpent dans le jeu.
 *
 * @details
 * Le score du serpent est mis à jour après que le serpent meurt dans le jeu.
 *
 * @remark
 * Vous devez appeler cette fonction dans implement_turn_all_snakes défini dans project_game.h
 * après qu'un serpent meurt.
 */
void update_single_score(
    score_table *st, //!< Le score_table.
    int i,           //!< L'index du serpent dans le jeu (dans le plateau).
    snake *s,        //!< Le serpent qui est mort.
    int t //!< Le temps que le serpent est resté en vie avant de mourir (donné
          //!< en secondes).
);

/**
 * @brief
 * Calcule les scores finaux du jeu après que tous les jeux ont été joués.
 *
 * @remark
 * Cette fonction est appelée automatiquement par l'interface.
 */
void compute_final_scores(score_table *st //!< Le score_table.
);

/**
 * @brief
 * Trie les serpents dans un score_table selon un type de score particulier pour un jeu particulier de la série
 * (ou le score final).
 *
 * @details
 * Le tableau des scores dans le score_table doit être trié par ordre décroissant du type de score donné
 * en paramètre.
 *
 *
 * @remark
 * Cette fonction est appelée automatiquement par l'interface.
 */
void sort_scores(score_table *st, //!< Le score_table.
                 int n_g, //!< Le jeu selon lequel le tri doit être effectué (ou
                          //!< nb_games pour le score final).
                 score_type type //!< Le type de score selon lequel le tri doit
                                 //!< être effectué.
);

#endif
