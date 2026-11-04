/**
 * @file project_board.h
 * @brief
 * Plateau de jeu.
 *
 * @details
 * Type utilisé pour représenter un plateau de jeu et fonctions associées.
 */

#ifndef _BOARD_H_
#define _BOARD_H_

 /*  ____   ___    _    ____  ____  ____   */
 /* | __ ) / _ \  / \  |  _ \|  _ \/ ___|  */
 /* |  _ \| | | |/ _ \ | |_) | | | \___ \  */
 /* | |_) | |_| / ___ \|  _ <| |_| |___) | */
 /* |____/ \___/_/   \_\_| \_\____/|____/  */

#include <stdlib.h>
#include <stdbool.h>
#include "project_masks.h"
#include "project_tools.h"

/**
 * @brief
 * Type énuméré utilisé pour représenter les quatre directions possibles à l'intérieur d'un plateau.
 */
typedef enum {
  UP,             //!< Haut
  RIGHT,          //!< Droite
  DOWN,           //!< Bas
  LEFT,           //!< Gauche
  DIRECTION_SIZE, //!< Nombre de directions
} direction;

/**
 * @brief
 * Retourne la direction opposée d'une direction donnée.
 *
 * @return
 * La direction opposée.
 */
direction opposite(direction dir //!< La direction.
);


/**
 * @brief
 * Type énuméré utilisé pour représenter tous les objets pouvant être placés dans une cellule du plateau.
 *
 * @remark
 * Le premier objet est EMPTY, qui représente une cellule vide. Le deuxième objet est SNAKE,
 * qui représente une cellule occupée par une section de serpent. Les autres objets représentent les
 * différents types de nourriture pouvant être placés dans une cellule pour que les serpents les ramassent.
 */
typedef enum {
  EMPTY,       //!< Cellule vide
  SNAKE,       //!< Section de serpent
  APPLE,       //!< Pomme (1 point + 1 longueur)
  CHERRY,      //!< Cerise (2 points + 2 longueurs)
  BANANA,      //!< Banane (3 points + 3 longueurs)
  GRAPES,      //!< Raisins (4 points + 4 longueurs)
  PINEAPPLE,   //!< Ananas (5 points + 5 longueurs)
  STUDENT,     //!< Étudiant (20 points + double longueur)
  CHILI,       //!< Piment (augmente la vitesse, si pas au maximum)
  MUSHROOM,    //!< Champignon (diminue la vitesse, si pas au minimum)
  OBJECT_SIZE, //!< Nombre d'objets
} object;

/**
 * @brief
 * Le type utilisé pour représenter un plateau.
 *
 * @details
 * Un plateau est une grille rectangulaire de cellules. Les cellules du plateau sont indexées linéairement ligne par ligne,
 * de gauche à droite et de haut en bas. Si le plateau a hsize colonnes et vsize rangées, la première cellule
 * (dans le coin supérieur gauche) a l'index 0, la cellule à sa droite a l'index 1, et ainsi de suite. La dernière
 * cellule (dans le coin inférieur droit) a l'index (hsize * vsize - 1).
 *
 * @details
 * Chaque cellule du plateau peut être masquée (c'est-à-dire qu'elle ne peut pas être occupée par des serpents ou des objets). Les cellules masquées
 * sont indiquées par le tableau masked. Si la cellule avec l'index i est masquée, alors masked[i] est vrai; sinon,
 * masked[i] est faux.
 *
 * @details
 * Le plateau contient également un tableau d'objets qui indique le contenu de chaque cellule non masquée. Pour chaque i,
 * objects[i] est l'objet contenu dans la cellule avec l'index i. L'objet peut être EMPTY (cette valeur spéciale
 * indique que la cellule est vide), SNAKE (cette valeur spéciale indique que la cellule est occupée par une section de serpent),
 * ou l'un des autres objets définis dans l'énumération object. Si la cellule avec l'index i est masquée,
 * alors objects[i] est indéfini (sa valeur est sans importance).
 *
 * @details
 * Le plateau contient également deux tableaux de directions qui indiquent les directions que les serpents ont utilisées pour entrer et
 * sortir des cellules. Pour chaque i, si la cellule avec l'index i contient une section de serpent (comme indiqué par objects[i]),
 * alors indirs[i] est la direction que le serpent a utilisée pour entrer dans la cellule, et outdirs[i] est la direction que le serpent
 * a utilisée pour sortir de la cellule. Si la cellule avec l'index i ne contient pas de section de serpent, alors indirs[i] et outdirs[i]
 * sont indéfinis (leurs valeurs sont sans importance).
 *
 * @details
 * Enfin, le plateau maintient également une liste de cellules vides pour un accès rapide (ce sont les cellules non masquées d'index
 * i où objects[i] est EMPTY). La variable empty_cells_count indique le nombre de cellules vides. Toutes les cellules vides
 * sont listées dans le tableau empty_cells_listing aux indices 0, 1, 2, ..., empty_cells_count - 1 dans un ordre arbitraire
 * (le tableau lui-même est de taille hsize * vsize). Le tableau empty_cells_indices est indexé par les indices des cellules
 * (0, 1, 2, ..., hsize * vsize - 1), pour chaque i, si la cellule avec l'index i est vide, alors empty_cells_indices[i] est
 * l'index de la cellule dans le tableau empty_cells_listing qui contient i; sinon, empty_cells_indices[i] est -1.
*/
typedef struct {
  int hsize;   //!< Taille horizontale.
  int vsize;   //!< Taille verticale.
  int size;    //!< Nombre total de cellules (hsize * vsize).
  int nb_food; //!< Nombre d'objets consommables (Fruits, étudiants,
               //!< champignons, piments).

  bool *masked; //!< Pour chaque index de cellule i, masked[i] est vrai si la
                //!< cellule est masquée et faux sinon.

  object *objects;    //!< Tableau d'objets.
  direction *indirs;  //!< Tableau des directions d'entrée des serpents.
  direction *outdirs; //!< Tableau des directions de sortie des serpents.

  int empty_cells_count;    //!< Nombre de cellules vides.
  int *empty_cells_listing; //!< Tableau qui liste les cellules vides.
  int *empty_cells_indices; //!< Tableau des indices des cellules vides dans
                            //!< empty_cells_listing.
} board;

/**
 * @brief
 * Calcule l'index de la cellule adjacente à une cellule donnée dans une direction donnée.
 *
 * @return
 * L'index de la cellule adjacente, ou -1 si la cellule adjacente n'existe pas.
 */
int get_adj_cell(board *b,     //!< Le plateau.
                 int cell,     //!< L'index de la cellule.
                 direction dir //!< La direction.
);

/**
 * @brief
 * Alloue un nouveau plateau sur le tas. Variante sans masque.
 *
 * @return
 * Un pointeur vers le nouveau plateau.
 */
board *new_board_nomask(int hsize, //!< La taille horizontale.
                        int vsize  //!< La taille verticale.
);

/**
 * @brief
 * Alloue un nouveau plateau sur le tas. Variante avec masque.
 *
 * @remark
 * Les dimensions du plateau sont déterminées par les dimensions du masque.
 *
 * @return
 * Un pointeur vers le nouveau plateau.
 */
board *new_board_mask(mask *m //!< Le masque.
);

/**
 * @brief
 * Libère la mémoire allouée pour un plateau.
 */
void delete_board(board *b //!< Le plateau.
);

/**
 * @brief
 * Échange les positions de deux cellules vides dans le tableau empty_cells_listing qui liste les cellules vides.
 *
 * @remark
 * Cette fonction ne modifie pas le plateau représenté. Elle ne fait que changer l'ordre dans lequel les cellules vides
 * sont listées. Cela est parfois nécessaire pour modifier le tableau empty_cells_listing. Par exemple,
 * retirer une cellule de la liste des cellules vides se fait en échangeant la cellule avec la dernière cellule du
 * tableau puis en décrémentant empty_cells_count.
 */
void swap_empty_cells(
    board *b, //!< Le plateau.
    int i1,   //!< L'index de la première cellule dans empty_cells_listing.
    int i2    //!< L'index de la deuxième cellule dans empty_cells_listing.
);

/**
 * @brief
 * Remplit une cellule du plateau avec un objet.
 *
 * @details
 * Si la cellule contient déjà un objet, la fonction ne fait rien.
 * Si la cellule était vide, elle doit être retirée de la liste des cellules vides. Dans ce
 * cas, empty_cells_count, le tableau empty_cells_listing et le tableau empty_cells_indices
 * doivent être mis à jour en conséquence.
 *
 * @remark
 * La fonction génère une erreur si l'objet est EMPTY (on ne peut pas remplir une cellule avec un objet vide
 * car il sert à indiquer une cellule vide).
 */
void fill_cell_board(board *b,  //!< Le plateau.
                     int i,     //!< L'index de la cellule.
                     object obj //!< L'objet.
);

/**
 * @brief
 * Vide une cellule du plateau.
 *
 * @details
 * Si la cellule était vide, la fonction ne fait rien. Si la cellule contenait un objet, elle est
 * vidée dans le tableau objects du plateau. La cellule doit être ajoutée à la liste des cellules vides.
 * Dans ce cas, empty_cells_count, le tableau empty_cells_listing et le tableau empty_cells_indices
 * doivent être mis à jour en conséquence.
 */
void empty_cell_board(board *b, //!< Le plateau.
                      int i     //!< L'index de la cellule.
);

#endif // _BOARD_H_
