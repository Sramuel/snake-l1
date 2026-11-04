/**
 * @file tools.h
 *
 * @brief
 * Outils.
 *
 * @details
 * Quelques macros que vous pouvez utiliser dans votre projet. Contient également la fonction get_time_counter.
 * Elle retourne le temps écoulé depuis le début d'un jeu en cours (en millisecondes). C'est la
 * fonction que vous devez utiliser pour calculer le temps qu'un serpent a passé en vie lors du remplissage
 * d'une entrée dans le tableau des scores.
 *
 * @remark
 * Vous ne devez PAS modifier ce fichier.
 */

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

 /*  _____           _      */
 /* |_   _|__   ___ | |___  */
 /*   | |/ _ \ / _ \| / __| */
 /*   | | (_) | (_) | \__ \ */
 /*   |_|\___/ \___/|_|___/ */

 /**
  * @brief
  * Macro pour obtenir la valeur maximale de deux valeurs.
  */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

  /**
   * @brief
   * Macro pour obtenir la valeur minimale de deux valeurs.
   */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

   /**
    * @brief
    * Macro pour échanger deux valeurs.
    */
#define SWAP(a, b) { typeof(a) temp = a; a = b; b = temp; }

    /**
     * @brief
     * Initialise le compteur de temps.
     *
     * @remark
     * Cette fonction est appelée par l'interface. Vous ne devez PAS l'appeler vous-même.
     */
void init_time_counter(void);

/**
 * @brief
 * Met en pause le compteur de temps.
 *
 * @remark
 * Cette fonction est appelée par l'interface. Vous ne devez PAS l'appeler vous-même.
 */
void pause_time_counter(void);

/**
 * @brief
 * Reprend le compteur de temps.
 *
 * @remark
 * Cette fonction est appelée par l'interface. Vous ne devez PAS l'appeler vous-même.
 */
void resume_time_counter(void);

/**
 * @brief
 * Obtient le compteur de temps.
 *
 * @return
 * Le compteur de temps en millisecondes.
 *
 * @remark
 * C'est la fonction que vous pouvez appeler pour récupérer le temps qu'un serpent a passé en vie pour remplir un tableau de scores.
 */
int get_time_counter(void);

#endif
