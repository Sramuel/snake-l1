/**
 * @file gui_controller.h
 * @brief
 * Game loop. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <time.h>
#include "gui_rendering.h"
#include "gui_menus.h"
#include "gui_grid.h"
#include "gui_checks.h"
#include "../project_parameters.h"
#include "../project_tools.h"
#include "../project_game.h"  
#include "../project_strats.h"
#include "../project_objgen.h"

 /*   ____                        _                    */
 /*  / ___| __ _ _ __ ___   ___  | | ___   ___  _ __   */
 /* | |  _ / _` | '_ ` _ \ / _ \ | |/ _ \ / _ \| '_ \  */
 /* | |_| | (_| | | | | | |  __/ | | (_) | (_) | |_) | */
 /*  \____|\__,_|_| |_| |_|\___| |_|\___/ \___/| .__/  */
 /*                                            |_|     */

/*****************************/
/*+ Intialization and reset +*/
/*****************************/

/**
 * @brief Initializes a new demo game for the menu background.
 */
void ctl_init_demo(void);

/**
 * @brief Initializes a game.
 */
void ctl_init_game(void);

/**
 * @brief Releases the game.
 */
void ctl_kill_game(void);

/**
 * @brief Initializes the score table.
 */
void ctl_init_scores(void);

/**
 * @brief Releases the score table.
 */
void ctl_kill_scores(void);

/*******************/
/*+ Menus control +*/
/*******************/

/**
 * @brief Enters the menu mode.
 */
void ctl_enter_menu(void);

/**
 * @brief Enters the score screen.
 */
void ctl_enter_scores(void);

/**
 * @brief Exits score menu.
 */
void ctl_exit_scores(void);

/******************/
/*+ Game update  +*/
/******************/

/**
 * @brief Updates the game. Called before each turn.
 */
void ctl_update_game(void);


/***********************/
/*+ Display functions +*/
/***********************/

/**
 * @brief Displays the current game on one of the two screens (0 or 1).
 *
 * @remark
 * For screen 1, this fails if there is no dual screen.
 */
void ctl_display_screen(unsigned char //!< The screen number.
);

/**
 * @brief Displays the menu.
 */
void ctl_display_menu(void);

/**
 * @brief Displays a classical game.
 */
void ctl_display_game(void);


/**
 * @brief Displays a pause screen over the game.
 */
void ctl_display_pause(void);


/**
 * @brief Displays the explosions (if any).
 */
void display_explosions(int //!< The screen number;
);

/*******************/
/*+ Button pushes +*/
/*******************/


/**
 * @brief Handles a button push in any context.
 *
 * @details
 * Calls the appropriate function depending on the current mode.
 */
void ctl_button_push(void);


/**
 * @brief Handles a button push in the menu.
 *
 * @details
 * Calls the appropriate function depending on the current menu.
 */
void ctl_button_push_menu(void);

/**
 * @brief Handles a button push in the main menu.
 */
void ctl_button_push_mainmenu(void);

/**
 * @brief Handles a button push in the setup menu.
 */
void ctl_button_push_setupmenu(void);

/**
 * @brief Handles a button push on the scores.
 */
void pushbutton_scores(void);

/**
 * @brief Handles a button push on the final scores.
 */
void pushbutton_final(void);


/***************************/
/*+ Enacting user actions +*/
/***************************/

/**
 * @brief Handles the mouse motion.
 */
void ctl_mouse_motion(SDL_Event* //!< The Event to get the mouse position.
);

/**
 * @brief Handles a mouse click.
 */
void ctl_mouse_click(SDL_Event* //!< The Event to get the mouse position.
);

/**
 * @brief Handles a mouse unclick.
 */
void ctl_mouse_unclick(SDL_Event* //!< The Event to get the mouse position.
);

/**
 * @brief Handles the keyboard input.
 */
void ctl_input(SDL_Event* //!< The Event to get the key used.
);

/***************/
/*+ Game loop +*/
/***************/

/**
 * @brief The game loop.
 */
void event_loop(void);






#endif // CONTROLLER_H_
