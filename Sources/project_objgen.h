/**
 * @file project_objgen.h
 * @brief
 * Générateurs d'objets.
 *
 * @details
 * Ce sont les fonctions utilisées pour générer de nouveaux objets sur le plateau. Une fonction génératrice d'objets
 * prend en entrée le jeu et remplit son plateau avec un ou plusieurs objets.
 *
 * @details
 * Pour générer un nombre aléatoire, utilisez la fonction "int rand(void)" de la bibliothèque standard. Pour obtenir un nombre aléatoire
 * entre 0 et N, utilisez "rand() % (N+1)".
 *
 * @remark
 * Vous devez écrire les fonctions génératrices. En revanche, vous ne devez PAS les appeler vous-même. En effet,
 * les stratégies sont appelées dans la boucle de jeu qui est déjà écrite. Chaque tour de la boucle de jeu consiste
 * en les quatre étapes suivantes :
 * 1. Utiliser une fonction de génération pour générer de nouveaux objets (la fonction est choisie lors de la création du jeu).
 * 2. Mettre à jour les directions de déplacement des serpents contrôlés par les joueurs en fonction des entrées du clavier.
 * 3. Appliquer la fonction de stratégie pour mettre à jour les directions de déplacement des serpents contrôlés par l'IA (les fonctions sont choisies lors de la création du jeu).
 * 4. Implémenter le tour pour tous les serpents en appelant la fonction "implement_turn_all_snakes".
 */

#ifndef _PROJECT_OBJGEN_H_
#define _PROJECT_OBJGEN_H_

 /*   ___  _     _           _                                     _                  */
 /*  / _ \| |__ (_) ___  ___| |_    __ _  ___ _ __   ___ _ __ __ _| |_ ___  _ __ ___  */
 /* | | | | '_ \| |/ _ \/ __| __|  / _` |/ _ \ '_ \ / _ \ '__/ _` | __/ _ \| '__/ __| */
 /* | |_| | |_) | |  __/ (__| |_  | (_| |  __/ | | |  __/ | | (_| | || (_) | |  \__ \ */
 /*  \___/|_.__// |\___|\___|\__|  \__, |\___|_| |_|\___|_|  \__,_|\__\___/|_|  |___/ */
 /*           |__/                 |___/                                              */

#include <stdlib.h>
#include <stdbool.h>
#include "project_game.h"
#include "project_tools.h"

/**
 * @brief
 * Noms internes des générateurs d'objets disponibles.
 *
 * @details
 * Pour ajouter un nouveau générateur, vous devez ajouter un nouveau nom ici, à la fin avant OGEN_SIZE.
 * Ensuite, vous devez compléter les trois étapes suivantes :
 * - Écrire la fonction génératrice correspondante.
 * - Ajouter la fonction à la fin du tableau generator_funs dans project_objgen.c (il contient toutes les fonctions génératrices).
 * - Ajouter le nom à la fin du tableau generator_names dans project_objgen.c (il contient tous les noms des générateurs). Cela est
 *  utilisé pour afficher le nom du générateur dans l'interface.
 */
typedef enum {
  OGEN_EMPTY, //!< Générateur vide.
  OGEN_BASIC, //!< Générateur aléatoire de base.
  OGEN_SAPPLE, //!< Générateur assurant qu'une seule pomme est toujours présente sur le plateau.
  OGEN_TENPE, //!< Générateur assurant que dix pour cent des cellules vides sont
              //!< toujours remplies d'objets aléatoires.
  OGEN_STINV, //!< Générateur qui remplit le plateau uniquement avec des étudiants.
  OGEN_SIZE,  //!< Nombre de générateurs.
} generator;

/**
 * @brief Tableau de fonctions génératrices.
 */
extern void (*generator_funs[OGEN_SIZE]) (game*);

/**
 * @brief Tableau de noms de stratégies.
 */
extern const char* generator_names[OGEN_SIZE];

/****************************/
/*+ Fonctions génératrices +*/
/****************************/

/**
 * @brief
 * Générateur vide.
 *
 * @details
 * Ne fait rien (aucun objet n'est généré).
 */
void gen_empty(game* g //!< Le plateau.
);

/**
 * @brief
 * Générateur d'objets de base.
 *
 * @details
 * Tous les LENGTH_CELL tours, ce générateur choisit une cellule vide aléatoire et la remplit avec un objet aléatoire.
 */
void gen_basic(game* g //!< Le plateau.
);

/**
 * @brief
 * Générateur de pomme unique.
 *
 * @details
 * Assure qu'une seule pomme est toujours présente sur le plateau. Si la pomme est mangée, une nouvelle est générée.
 */
void gen_single_apple(game* g //!< Le plateau.
);

/**
 * @brief
 * Générateur de dix pour cent.
 *
 * @details
 * Assure que dix pour cent des cellules vides sont toujours remplies d'objets aléatoires. Si le pourcentage
 * de cellules remplies tombe en dessous de dix pour cent, le générateur remplit des cellules vides choisies
 * aléatoirement avec des objets aléatoires jusqu'à ce que le pourcentage soit de dix pour cent.
 */
void gen_ten_percent(game* g //!< Le plateau.
);

/**
 * @brief
 * Générateur d'invasion des étudiants.
 *
 * @details
 * Assure que vingt pour cent des cellules vides sont toujours remplies d'étudiants. Si le pourcentage
 * de cellules remplies tombe en dessous de vingt pour cent, le générateur remplit des cellules vides
 * choisies aléatoirement avec des étudiants jusqu'à ce que le pourcentage soit de vingt pour cent.
 *
 * @attention
 * Lorsqu'ils sont mangés, les étudiants peuvent augmenter considérablement la longueur des serpents. Avant d'utiliser ce générateur,
 * assurez-vous que la fonction utilisée pour consommer la nourriture gère l'erreur qui peut survenir lorsque la longueur totale
 * du serpent devient "trop élevée".
 */
void gen_student_invasion(game* g //!< Le plateau.
);

#endif // _PROJECT_OBJGEN_H_
