/**
 * @file project_parameters.h
 * @brief Paramètres.
 *
 * @details Macros pour les paramètres suivants :
 * - Activation de certaines fonctionnalités de débogage.
 * - Dimensions de la fenêtre.
 * - Paramètres par défaut pour les jeux. Ce sont les paramètres utilisés si un jeu rapide est lancé.
 */

#ifndef _PROJECT_PARAMETERS_H_
#define _PROJECT_PARAMETERS_H_

 /*  ____                                _                 */
 /* |  _ \ __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___  */
 /* | |_) / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __| */
 /* |  __/ (_| | | (_| | | | | | | |  __/ ||  __/ |  \__ \ */
 /* |_|   \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/ */


/***************/
/*+ Débogage +*/
/***************/

/**
 * @brief Supprime le message à l'écran lors de la mise en pause du jeu. Décommentez pour activer.
 *
 * @details
 * Si cette macro est définie, le message à l'écran qui apparaît lorsque le jeu est en pause sera supprimé.
 * Cela donne un meilleur aperçu du plateau de jeu à des fins de débogage.
 */
 // #define HIDEPAUSE

/**
 * @brief Active le débogage des serpents. Décommentez pour activer.
 *
 * @details
 * Si cette macro est définie, les cellules marquées comme remplies par un serpent seront surlignées
 * en blanc dans l'application.
 */
 //#define DEBUGSNAKES

/**
 * @brief Active le premier débogage pour les cellules vides. Décommentez pour activer.
 *
 * @details
 * Si cette macro est définie, les cellules listées comme vides dans le tableau empty_cell_listing seront
 * surlignées en jaune dans l'application.
 */
// #define DEBUGEMPTYLIST

/**
 * @brief Active le deuxième débogage pour les cellules vides. Décommentez pour activer.
 *
 * @details
 * Si cette macro est définie, les cellules marquées comme vides dans le tableau empty_cell_indices seront
 * surlignées en bleu dans l'application.
 */
//#define DEBUGEMPTYINDICES

/**
 * @brief Active le débogage des masques. Décommentez pour activer.
 *
 * @details
 * Si cette macro est définie, le masque sélectionné sera affiché sur le terminal (en appelant la
 * fonction print_mask que vous devez écrire) avant le lancement du jeu.
 */
//#define DEBUGMASK

/******************************/
/*+ Dimensions de la fenêtre +*/
/******************************/

/**
 * @brief Dimension horizontale de l'application en pixels (par défaut = 1820).
 */
#define WINDOW_SCREENWIDTH 1820

/**
 * @brief Dimension verticale de l'application en pixels (par défaut = 980).
 */
#define WINDOW_SCREENHEIGHT 980

/***************************/
/*+ Paramètres par défaut +*/
/***************************/

/**
 * @brief Nombre de jeux à jouer pour la commande de jeu rapide.
 */
#define QUICK_NBGAMES 2

/**
 * @brief Dimension horizontale du plateau en cellules pour les jeux rapides.
 */
#define QUICK_HSIZE 25

/**
* @brief Dimension verticale du plateau en cellules pour les jeux rapides.
*/
#define QUICK_VSIZE 25

/**
* @brief Masque utilisé dans les jeux rapides : une chaîne contenant le nom du fichier tel que "loveC.msk" (NULL si aucun masque n'est souhaité).
*/
#define QUICK_MASK NULL

/**
* @brief Nombre de joueurs dans les jeux rapides (0, 1 ou 2).
*/
#define QUICK_PLAYERS 1

/**
 * @brief Nombre d'IA dans les jeux rapides.
 */
#define QUICK_IA 2

/**
 * @brief Longueur maximale initiale des serpents dans les jeux rapides.
 */
#define QUICK_MAXLENGTH 1

/**
* @brief Stratégie commune de toutes les IA dans les jeux rapides.
*/
#define QUICK_STRAT STRAT_SCORE

/**
 * @brief Vitesse de départ des serpents dans les jeux rapides.
 */
#define QUICK_SPEED SLOW

/**
 * @brief Générateur d'objets utilisé dans les jeux rapides.
 */
#define QUICK_OBJGEN OGEN_BASIC

/**
 * @mainpage Le projet snake game.
 *
 */

#endif // _PROJECT_PARAMETERS_H_
