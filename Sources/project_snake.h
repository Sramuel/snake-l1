/**
 * @file project_snake.h
 *
 * @brief
 * Serpents.
 *
 * @details
 * Type utilisé pour représenter un seul serpent et fonctions associées.
 */

#ifndef _SNAKE_H_
#define _SNAKE_H_

 /*  ____              _              */
 /* / ___| _ __   __ _| | _____  ___  */
 /* \___ \| '_ \ / _` | |/ / _ \/ __| */
 /*  ___) | | | | (_| |   <  __/\__ \ */
 /* |____/|_| |_|\__,_|_|\_\___||___/ */

#include <stdlib.h>
#include <stdbool.h>
#include "project_masks.h"
#include "project_board.h"

/**
 * @brief
 * Le nombre de mouvements nécessaires à un serpent pour traverser une seule cellule.
 *
 * @details
 * UTILISEZ CETTE VALEUR MAIS NE LA CHANGEZ PAS (cela casserait tout le jeu).
 */
#define LENGTH_CELL 64

 /**
  * @brief
  * Noms internes des vitesses disponibles pour un serpent.
  *
  * @details
  * La vitesse d'un serpent détermine le nombre de mouvements que le serpent effectue
  * en un tour. Ces nombres de mouvements sont déjà définis dans le tableau global
  * speed_values déclaré ci-dessous (le tableau lui-même est défini et
  * initialisé dans project_snake.c).
  */
typedef enum {
  SLOWER,    //!< Vitesse plus lente : 1 mouvement
  SLOW,      //!< Vitesse lente : 2 mouvements
  MEDIUM,    //!< Vitesse moyenne : 4 mouvements
  FAST,      //!< Vitesse rapide : 8 mouvements
  FASTER,    //!< Vitesse plus rapide : 16 mouvements
  LUDICROUS, //!< Vitesse ridicule : 32 mouvements
  SPEED_SIZE //!< Nombre de vitesses
} speed;

/**
 * @brief
 * Le nombre de mouvements effectués en un seul tour par un serpent allant à la vitesse SLOWER.
 *
 * @details
 * UTILISEZ CETTE VALEUR MAIS NE LA CHANGEZ PAS (cela casserait tout le jeu).
 */
#define SLOWER_VAL 1

/**
* @brief
* Le nombre de mouvements effectués en un seul tour par un serpent allant à la vitesse SLOW.
*
* @details
* UTILISEZ CETTE VALEUR MAIS NE LA CHANGEZ PAS (cela casserait tout le jeu).
*/
#define SLOW_VAL 2

/**
 * @brief
 * Le nombre de mouvements effectués en un seul tour par un serpent allant à la vitesse MEDIUM.
 *
 * @details
 * UTILISEZ CETTE VALEUR MAIS NE LA CHANGEZ PAS (cela casserait tout le jeu).
 */
#define MEDIUM_VAL 4

/**
 * @brief
 * Le nombre de mouvements effectués en un seul tour par un serpent allant à la vitesse FAST.
 *
 * @details
 * UTILISEZ CETTE VALEUR MAIS NE LA CHANGEZ PAS (cela casserait tout le jeu).
 */
#define FAST_VAL 8

/**
 * @brief
 * Le nombre de mouvements effectués en un seul tour par un serpent allant à la vitesse FASTER.
 *
 * @details
 * UTILISEZ CETTE VALEUR MAIS NE LA CHANGEZ PAS (cela casserait tout le jeu).
 */
#define FASTER_VAL 16

/**
 * @brief
 * Le nombre de mouvements effectués en un seul tour par un serpent allant à la vitesse LUDICROUS.
 *
 * @details
 * UTILISEZ CETTE VALEUR MAIS NE LA CHANGEZ PAS (cela casserait tout le jeu).
 */
#define LUDICROUS_VAL 32

/**
 * @brief
 * Pour chaque nom de vitesse, associe le nombre de mouvements effectués en un seul tour par un serpent allant à cette vitesse.
 *
 * @return
 * Le nombre de mouvements effectués en un seul tour par un serpent allant à la vitesse donnée.
 */
int speed_to_value(speed s //!< La vitesse.
);

/**
 * @brief
 * Le type représentant un seul serpent dans le jeu.
 */
typedef struct {
  bool alive; //!< Vrai si le serpent est vivant, faux si le serpent est mort.

  int head; //!< La cellule dans laquelle la tête du serpent se déplace
            //!< actuellement.
  int tail; //!< La cellule que la queue du serpent occupe actuellement (pouvant
            //!< éventuellement sortir si le serpent est à pleine longueur).
  int length; //!< La longueur actuelle du serpent (augmente (de 1) chaque fois
              //!< que le serpent entre dans une nouvelle cellule jusqu'à ce
              //!< qu'elle soit égale à la longueur totale).
  int full_length; //!< La longueur totale du serpent (augmente uniquement
                   //!< lorsque le serpent mange de la nourriture).

  int progress;   //!< La progression du serpent dans la cellule actuelle de la
                  //!< tête : nombre de mouvements déjà effectués dans cette
                  //!< cellule (va de 0 à LENGTH_CELL-1).
  direction move; //!< La direction dans laquelle le serpent se déplace.
                  //!< Détermine la prochaine cellule de tête que le serpent
                  //!< entrera après celle-ci.
  speed speed;    //!< La vitesse actuelle du serpent.

  int score;    //!< Le score actuel du serpent.
  int distance; //!< Le nombre de cellules que le serpent a visitées depuis le
                //!< début du jeu.
  int students; //!< Le nombre d'étudiants que le serpent a mangés depuis le
                //!< début du jeu.
} snake;

/**
 * @brief
 * Alloue un nouveau serpent sur le tas.
 *
 * @details
 * Un nouveau serpent commence toujours à la longueur 2 :
 * - La cellule de la tête est occupée par la tête du serpent : c'est la cellule dans laquelle le serpent se déplace.
 * - La cellule de la queue est occupée par la queue du serpent : c'est la cellule que le serpent quitte (si elle est à pleine longueur).
 * Ces deux cellules sont choisies aléatoirement sur le plateau (appelez la fonction "rand()" qui renvoie un entier aléatoire positif) à partir
 * de la liste des cellules vides. Naturellement, elles doivent être contiguës.
 *
 * @details
 * Pour générer un nombre aléatoire, utilisez la fonction "int rand(void)" de la bibliothèque standard. Pour obtenir un nombre aléatoire
 * entre 0 et N, utilisez "rand() % (N+1)".
 *
 * @remark
 * Si la fonction échoue à créer le nouveau serpent (par exemple, si deux cellules vides contiguës ne peuvent pas être trouvées), elle renvoie NULL.
 *
 * @attention
 * N'oubliez pas de mettre à jour les tableaux du plateau puisque les cellules de la queue et de la tête sont maintenant occupées par le serpent (cela inclut les
 * tableaux indir et outdir).
 *
 * @return
 * Un pointeur vers le nouveau serpent.
 */
snake *new_snake(board *b, //!< Le plateau sur lequel le serpent sera créé.
                 speed sp, //!< La vitesse initiale du serpent.
                 int flen  //!< La longueur totale initiale du serpent.
);

/**
 * @brief
 * Supprime un serpent.
 */
void delete_snake(snake *s //!< Le serpent à supprimer.
);

/**
 * @brief
 * Fait consommer un objet à un serpent.
 *
 * @remark
 * Consommer un objet consiste à mettre à jour le serpent en fonction de l'objet. La fonction ne fait rien si le
 * serpent est mort.
 *
 * @details
 * Modifications correspondant à chaque objet :
 * - APPLE : La longueur totale du serpent augmente de un. Le score du serpent est augmenté de 10.
 * - CHERRY : La longueur totale du serpent augmente de un. Le score du serpent est augmenté de 20.
 * - BANANA : La longueur totale du serpent augmente de deux. Le score du serpent est augmenté de 30.
 * - GRAPES : La longueur totale du serpent augmente de deux. Le score du serpent est augmenté de 40.
 * - PINEAPPLE : La longueur totale du serpent augmente de trois. Le score du serpent est augmenté de 50.
 * - STUDENT : La longueur totale du serpent est doublée. Le score du serpent est augmenté de 100 (cela augmente également le nombre d'étudiants mangés par le serpent).
 * - MUSHROOM : La vitesse du serpent est diminuée d'un niveau (si elle n'est pas déjà à la vitesse minimale).
 * - CHILI : La vitesse du serpent est augmentée d'un niveau (si elle n'est pas déjà à la vitesse maximale).
 *
 * @attention
 * Si l'objet passé est EMPTY ou SNAKE, la fonction ne fait rien (ce ne sont pas des objets consommables
 * et les fonctions ne doivent PAS être appelées avec ces objets).
 */
void consume_object_snake(snake *s,  //!< Le serpent.
                          object obj //!< L'objet.
);

/**
 * @brief
 * La fonction déplace le serpent en fonction de sa direction et de sa vitesse actuelles. Le serpent ne peut se déplacer que s'il est vivant.
 *
 * @details
 * Cette fonction avance la valeur de progression du serpent en fonction de sa vitesse (elle ajoute le nombre de mouvements correspondant
 * à cette vitesse à la valeur de progression).
 *
 * @details
 * Si la valeur de progression devient égale à LENGTH_CELL (le serpent a terminé la cellule actuelle), la fonction déplace la tête
 * du serpent vers la cellule suivante (déterminée par la cellule actuelle de la tête et la direction). Dans ce cas, la fonction doit :
 * - Réinitialiser la valeur de progression du serpent (elle devient 0).
 * - Mettre à jour la longueur du serpent (elle augmente de un si le serpent n'est pas encore à pleine longueur).
 * - Mettre à jour la queue du serpent si nécessaire (elle perd une cellule si le serpent est déjà à pleine longueur).
 * - Mettre à jour la direction de sortie du serpent sur le plateau pour la cellule dégagée (vers la direction prise par le serpent).
 * - Si la cellule suivante n'existe pas, si elle est occupée par un serpent ou si elle est masquée, le serpent meurt.
 *
 * Si le serpent reste en vie, la fonction doit également :
 * - Mettre à jour le serpent en fonction de l'objet contenu dans la cellule suivante (s'il y en a un).
 * - Mettre à jour la tête du serpent (elle se déplace vers la cellule suivante).
 * - Mettre à jour le tableau des objets du plateau (la cellule suivante est maintenant occupée par le serpent).
 * - Mettre à jour la direction d'entrée du serpent dans la cellule suivante (le contraire de la direction dans laquelle le serpent est sorti de la cellule précédente).
 *
 * @remark
 * Si le serpent est mort, la fonction ne fait rien.
 *
 * @attention
 * Cette fonction doit mettre à jour à la fois les serpents et le plateau selon les règles du jeu.
 *
 * @return
 * Vrai si la fonction a tué le serpent, faux sinon (le serpent est toujours vivant ou était déjà mort). Cette information
 * est utile dans la fonction qui appelle implement_turn_snake (à savoir, implement_turn_all_snakes dans project_game.h).
 */
bool implement_turn_snake(snake *s, //!< Le serpent.
                          board *b  //!< Le plateau.
);

#endif // _SNAKE_H_
