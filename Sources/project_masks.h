/**
 * @file project_masks.h
 * @brief
 * Masques.
 *
 * @details
 * Contient la définition du type utilisé pour représenter un masque ainsi que les fonctions de base
 * que nous utiliserons pour manipuler ce type.
 */
#ifndef _PROJECT_MASKS_H_
#define _PROJECT_MASKS_H_

 /*  __  __    _    ____  _  ______   */
 /* |  \/  |  / \  / ___|| |/ / ___|  */
 /* | |\/| | / _ \ \___ \| ' /\___ \  */
 /* | |  | |/ ___ \ ___) | . \ ___) | */
 /* |_|  |_/_/   \_\____/|_|\_\____/  */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief
 * Type utilisé pour représenter un masque.
 *
 * @remark
 * Les cellules sont indexées par des entiers allant de 0 à hsize*vsize-1. Elles sont ordonnées ligne par ligne de haut en bas.
 * La cellule d'index 0 est dans le coin supérieur gauche. Les cellules allant de 0 à hsize-1 constituent la première ligne en
 * haut de la grille, les cellules allant de hsize à 2*hsize-1 constituent la deuxième ligne, et ainsi de suite.
 *
 * @attention
 * Nous supposons toujours qu'un masque contient au moins une cellule non masquée (cette propriété doit être vérifiée lors de la
 * lecture d'un fichier de masque).
 */
typedef struct {
  int hsize;    //!< Taille horizontale.
  int vsize;    //!< Taille verticale.
  int nbmasked; //!< Nombre de cellules masquées. Toujours strictement inférieur
                //!< au nombre total de cellules (au moins une cellule doit être
                //!< non masquée).
  bool *grid; //!< Tableau booléen indiquant les cellules masquées. La cellule i
              //!< est dans le i-ème cas du tableau (true : masquée, false : non
              //!< masquée).
} mask;

/**
 * @brief
 * Allocation d'un masque vide sur le tas : aucune cellule n'est masquée.
 *
 * @return
 * Le masque créé.
 */
mask *create_empty_mask(int hsize, //!< Taille horizontale.
                        int vsize //!< Taille verticale.
);

/**
 * @brief
 * Libération de la mémoire allouée pour un masque.
 */
void delete_mask(mask* m //!< Le masque.
);

/**
 * @brief
 * Redimensionnement d'un masque.
 *
 * @details
 * Conversion d'un masque dont les dimensions sont arbitraires pour lui donner les dimensions souhaitées.
 *
 * @attention
 * Le masque doit être redimensionné aux nouvelles dimensions. Le nombre de cellules masquées doit être mis à jour.
 * Au moins une cellule doit être non masquée.
 */
void resize_mask(mask *m,    //!< Le masque à redimensionner.
                 int nhsize, //!< Nouvelle taille horizontale.
                 int nvsize  //!< Nouvelle taille verticale.
);

/**
 * @brief
 * Affichage d'un masque sur le terminal (utile uniquement pour les tests).
 */
void print_mask(mask *m //!< Le masque à afficher.
);

/**
 * @brief
 * Génération d'un masque à partir d'un fichier.
 *
 * @attention
 * Le fichier doit contenir une représentation ASCII de la grille :
 * - Le caractère X correspond à une cellule masquée.
 * - Tout autre caractère indique une cellule non masquée.
 *
 * @remark
 * Des exemples de tels fichiers sont donnés dans le répertoire "Masks".
 *
 * @attention
 * Le fichier doit contenir un rectangle parfait (toutes les lignes doivent avoir la même longueur).
 * Le masque doit contenir au moins une cellule non masquée. Si le fichier ne respecte pas ces conditions, la fonction retourne NULL.
 *
 * @return
 * Le masque lu dans le fichier.
 */
mask *read_mask(const char *path//!< Chaîne contenant le chemin vers le fichier.
);

#endif // _PROJECT_MASKS_H_
