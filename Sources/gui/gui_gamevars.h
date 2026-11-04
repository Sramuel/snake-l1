/**
 * @file gui_gamevars.h
 * @brief
 * Global variables used by the interface. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

#ifndef GAMEVARS_H_
#define GAMEVARS_H_

 /*   ____ _       _           _                   _       _     _            */
 /*  / ___| | ___ | |__   __ _| | __   ____ _ _ __(_) __ _| |__ | | ___  ___  */
 /* | |  _| |/ _ \| '_ \ / _` | | \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __| */
 /* | |_| | | (_) | |_) | (_| | |  \ V / (_| | |  | | (_| | |_) | |  __/\__ \ */
 /*  \____|_|\___/|_.__/ \__,_|_|   \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/ */


#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "../project_game.h"
#include "../project_strats.h"
#include "../project_objgen.h"
#include "gui_textbuf.h"


/***********/
/*+ Flags +*/
/***********/


/**
 * @brief Flags.
 */
typedef enum {
    QUIT,
    HELP,
    PAUSE,
    PUSHED,
    MOUSEDOWN,
    KEYDOWN,
    NEXTGAME,
    GOMENU,
    NB_FLAGS
} ctl_flags;

/**
 * @brief Array of flags.
 */
extern bool flags[NB_FLAGS];

/**
 * @brief Activation of a flag.
 */
void set_flag(ctl_flags //!< The flag.
);

/**
 * @brief Deactivation of a flag.
 */
void remove_flag(ctl_flags //!< The flag
);

/*
 * @brief Inversion of a flag.
 */
void flip_flag(ctl_flags //!< The flag
);

/**
 * @brief Reset of all flags.
 */
void reset_flags(void);

/******************************/
/*+ Dimensions of the window +*/
/******************************/

/**
 * @brief Horizontal size of the window.
 */
extern int var_screen_width;

/**
 * @brief Vertical size of the window.
 */
extern int var_screen_height;


/*******************/
/*+ Mouse control +*/
/*******************/

/**
 * @brief Saves the horizontal coordinate of the mouse.
 */
extern int var_mousePosx;

/**
 * @brief Saves the vertical coordinate of the mouse.
 */
extern int var_mousePosy;

/**
 * @brief Records if the left mouse button is pushed (true) or not (false).
 */
extern bool var_leftMouseButtonDown;


/************************/
/*+ Zoom and Scrolling +*/
/************************/

/**
 * @brief Is the dual screen mode activated?
 */
extern bool var_dual_screen;


/**
 * @brief Dimensions of the two screens.
 *
 * @remark
 * If dual screen mode is off, the screen is stored in var_screen[0]. If dual
 * screen mode is on, the left screen is stored in var_screen[0] and the right
 * screen is stored in var_screen[1].
 */
extern SDL_Rect var_screen[2];


/**
 * @brief Associates to each player the screen on which it is displayed.
 */
extern unsigned char var_player_screen[2];


/**
 * @brief Initializes the dual screen mode.
 */
void init_dual_screen(void);

/**
 * @brief Initializes the single screen mode.
 */
void init_single_screen(void);


/**
 * @brief Checks if a screen index is currently valid.
 *
 * @details
 * The valid screens indices are 0 and 1. Moreover, 1 is only valid when dual
 * screen mode is activated.
 */
bool check_valid_screen(unsigned char //!< The screen index to check.
);


/**
 * @brief Current zoom level.
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the zoom level is stored
 * in var_render_zoom_level[0]. If dual screen is on (var_dual_screen = true),
 * the zoom level is stored in var_render_zoom_level[0] for the first screen
 * and var_render_zoom_level[1] for the second screen.
 */
extern int var_render_zoom_level[2];

/**
 * @brief The size of a tile at the current zoom level (a cell of the board is
 * a four tiles square).
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the tile size is stored
 * in var_tile_size[0]. If dual screen is on (var_dual_screen = true), the tile
 * size is stored in var_tile_size[0] for the first screen and var_tile_size[1]
 * for the second screen.
 */
extern int var_tile_size[2];

/**
 * @brief Initialization of the zoom level for the menu demo.
 */
void init_zoom_demo(void);


/**
 * @brief Initialization of the zoom level for a normal game.
 */
void init_zoom_game(void);

/**
 * @brief Horizontal scrolling offset.
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the offset is stored in
 * var_scrollOffsetx[0]. If dual screen is on (var_dual_screen = true), the
 * offset is stored in var_scrollOffsetx[0] for the first screen and
 * var_scrollOffsetx[1] for the second screen.
 */
extern int var_scrollOffsetx[2];

/**
 * @brief Vertical scrolling offset.
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the offset is stored in
 * var_scrollOffsety[0]. If dual screen is on (var_dual_screen = true), the
 * offset is stored in var_scrollOffsety[0] for the first screen and
 * var_scrollOffsety[1] for the second screen.
 */
extern int var_scrollOffsety[2];

/**
 * @brief Horizontal coordinate of the first cell in the display area (in the board).
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the coordinate is stored in
 * var_startx[0]. If dual screen is on (var_dual_screen = true), the coordinate
 * is stored in var_startx[0] for the first screen and var_startx[1] for the
 * second screen.
 */
extern int var_startx[2];

/**
 * @brief Vertical coordinate of the first cell in the display area (in the board).
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the coordinate is stored in
 * var_starty[0]. If dual screen is on (var_dual_screen = true), the coordinate
 * is stored in var_starty[0] for the first screen and var_starty[1] for the
 * second screen.
 */
extern int var_starty[2];

/**
 * @brief Horizontal coordinate of the last cell in the display area (in the board).
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the coordinate is stored in
 * var_endx[0]. If dual screen is on (var_dual_screen = true), the coordinate
 * is stored in var_endx[0] for the first screen and var_endx[1] for the
 * second screen.
 */
extern int var_endx[2];

/**
 * @brief Vertical coordinate of the last cell in the display area (in the board).
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the coordinate is stored in
 * var_endy[0]. If dual screen is on (var_dual_screen = true), the coordinate
 * is stored in var_endy[0] for the first screen and var_endy[1] for the
 * second screen.
 */
extern int var_endy[2];

/**
 * @brief Horizontal coordinate of the first cell in the display area (on the screen).
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the coordinate is stored in
 * var_topleftx[0]. If dual screen is on (var_dual_screen = true), the coordinate
 * is stored in var_topleftx[0] for the first screen and var_topleftx[1] for the
 * second screen.
 */
extern int var_topleftx[2];

/**
 * @brief Vertical coordinate of the first cell in the display area (on the screen).
 *
 * @remark
 * If dual screen is off (var_dual_screen = false), the coordinate is stored in
 * var_toplefty[0]. If dual screen is on (var_dual_screen = true), the coordinate
 * is stored in var_toplefty[0] for the first screen and var_toplefty[1] for the
 * second screen.
 */
extern int var_toplefty[2];

/**
 * @brief Updates the variables that define the borders of the display area according
 * to the scrolling offsets.
 *
 * @details
 * The function updates the following variables according to the scrolling offsets:
 * var_startx, var_starty, var_endx, var_endy, var_topleftx and var_toplefty.
 *
 * @remark
 * The parameter indicates which screen has to be updated (0 for the first screen, 1 for the second screen).
 *
 */
void scroll_update_borders(unsigned char //!< The screen to update.
);

/**
 * @brief Decrease the zoom level by one.
 *
 * @remark
 * The parameter indicates which screen has to be updated (0 for the first screen, 1 for the second screen).
 *
 */
void decrease_zoom(unsigned char //!< The screen to update.
);

/**
 * @brief Increase the zoom level by one.
 *
 * @remark
 * The parameter indicates which screen has to be updated (0 for the first screen, 1 for the second screen).
 */
void increase_zoom(unsigned char //!< The screen to update.
);

/**
 * @brief Manual scrolling.
 *
 * @remark
 * The third parameter indicates which screen has to be updated (0 for the first screen, 1 for the second screen).
 */
void scroll_manual(int, //!< Horizontal scrolling.
    int, //!< Vertical scrolling.
    unsigned char //!< The screen to update.
);

/**
 * @brief Mouse scrolling.
 *
 * @remark
 * The screen to scroll is the one where the mouse is.
 */
void scroll_with_mouse(int, //!< Horizontal scrolling.
    int //!< Vertical scrolling.
);

/**
 * @brief Centers the screen on a given board cell.
 *
 * @remark
 * The third parameter indicates which screen has to be updated (0 for the first screen, 1 for the second screen).
 */
void scroll_to_cell(board*, //!< The board.
    int, //!< The cell to center on (number in the board).
    unsigned char //!< The screen to update.
);


/**
 * @brief Centers the screen on a given board coordinate.
 *
 * @remark
 * The third parameter indicates which screen has to be updated (0 for the first screen, 1 for the second screen).
 */
void scroll_to_coords(int, //!< Horizontal coordinate.
    int, //!< Vertical coordinate.
    unsigned char //!< The screen to update.
);


/**
 * @brief Scrolls the screen so that the board is centered.
 *
 * @remark
 * The second parameter indicates which screen has to be updated (0 for the first screen, 1 for the second screen).
 */
void scroll_to_center(board* //!< The board.
    , unsigned char //!< The screen to update.
);



/**********************/
/*+ Player tracking  +*/
/**********************/



/**
 * @brief Is the player being tracked? (0: player 1, 1: player 2)
 */
extern bool player_track[2];

/**
 * @brief Horizontal starting coordinate of the player (0: player 1, 1: player 2).
 */
extern int player_xstart[2];

/**
 * @brief Vertical starting coordinate of the player (0: player 1, 1: player 2).
 */
extern int player_ystart[2];

/**
 * @brief Horizontal shift of the player (0: player 1, 1: player 2).
 */
extern int player_xshift[2];

/**
 * @brief Vertical shift of the player (0: player 1, 1: player 2).
 */
extern int player_yshift[2];

/**
 * @brief Horizontal backlog of the player (0: player 1, 1: player 2).
 */
extern int player_xbacklog[2];

/**
 * @brief Vertical backlog of the player (0: player 1, 1: player 2).
 */
extern int player_ybacklog[2];


/**
 * @brief Initialization of the player tracking.
 */
void init_player_tracking(int, // Starting horizontal coordinate of the player.
    int, // Starting vertical coordinate of the player.
    unsigned char // The player to track (0: player 1, 1: player 2).
);

/**
 * @brief Disables the tracking of the player.
 */
void disable_player_tracking(unsigned char // The player to track (0: player 1, 1: player 2).
);


/**
 * @brief Updates the tracking of the player.
 */
void update_player_tracking(game*, // The game.
    unsigned char, // The player to track (0: player 1, 1: player 2).
    int // The previous progress of the player.
);

/*******************/
/*+ Speed control +*/
/*******************/

/**
 * @brief Array of speed names.
 */
extern const char* speed_names[SPEED_SIZE];

/*******************/
/*+ Reading masks +*/
/*******************/

/**
 * @brief Tableau de la liste des fichiers de masques.
 */
extern struct dirent** var_maskstab;

/**
 * @brief Taille du tableau de la liste des fichiers de masques.
 */
extern int var_masktabsize;

/**
 * @brief Index du masque sélectionné dans le tableau de la liste des fichiers de masques. (-1 si aucun masque n'est utilisé)
 */
extern int var_maskindex;

/**
 * @brief Initialisation du tableau de la liste des fichiers de masques.
 */
void var_init_maskstab(void);

/**
 * @brief Libération du tableau de la liste des fichiers de masques.
 */
void var_free_maskstab(void);


/*******************/
/*+ Keyboard text +*/
/*******************/

/**
 * @brief Internal names of the various values that can be edited.
 */
typedef enum {
    ED_X, //!< Horizontal size.
    ED_Y, //!< Vertical size.
    ED_IAS, //!< Number of IAs.
    ED_SINGLEIA, //!< IA to edit.
    ED_LENGTH, //!< Initial length.
    ED_GAMES, //!< Number of games.
    ED_NONE, //!< Buffer is currently unused.
} edit_mode;

/**
 * @brief Global variable used to indicate the value which is currently being edited (ED_NONE if the buffer is unused).
 */
extern edit_mode var_edit_mode;

/**
 * @brief Global variable used for the buffer (NULL if the buffer is unused).
 */
extern text_buffer* var_editbuffer;


/**
 * @brief Initialization of the buffer
 */
void init_text_buffer(edit_mode //!< The value to edit.
);


/**
 * @brief Updates parameters from the buffer.
 */
void update_from_text_buffer(void);


/**********************************/
/*+ Variables pour la génération **/
/**********************************/

/**
 * @brief Number of games to play.
 */
extern int gen_nbgames;

/**
 * @brief How many players are there ?
 */
extern int gen_players;


/**
 * @brief How many IAs are there ?
 */
extern int gen_iasnakes;


/**
 * @brief Horizontal size.
 */
extern int gen_hsize;

/**
 * @brief Vertical size.
 */
extern int gen_vsize;


/**
 * @brief Do we have to use a mask ?
 */
extern bool gen_use_mask;

/**
 * @brief Name of the mask file to use.
 */
extern char gen_maskname[128];



/**
 * @brief Common starting speed of all snakes.
 */
extern speed gen_speed;

/**
 * @brief Maximum initial length of the snakes.
 */
extern int gen_maxlength;


/**
 * @brief Initial common strategy of all ias.
 */
extern strat gen_strat;




/**
 * @brief Strategy to assign in the interface
 */
extern strat var_strat_assign;

/**
 * @brief Currently selected IA in the interface.
 */
extern int var_ia_select;





/****************************/
/*+ Objects and strategies +*/
/****************************/

/**
 * @brief The object generator to use.
 */
extern generator var_objgen;

/**
 * @brief Strategies of the computer controlled snakes.
 */
extern strat* var_strats;

/**
 * @brief Size of the array of strategies.
 *
 * @remark
 * Must always be larger than the value of gen_iasnakes
 */
extern int var_strats_size;

/**
 * @brief Strategies of the computer controlled snakes in the menu demo.
 */
extern strat var_demo_strats[5];



/********************/
/*+    Games       +*/
/********************/

/**
 * @brief Global variable that stores a pointer to the game which is currently being played.
 *
 * @remark
 * In the menu, this is also where the pointer to the demo game is stored.
 */
extern game* var_game;

/**
 * @brief Global variable that stores a pointer to the scores of the current series of games.
 */
extern score_table* var_scores;


/**
 * @brief Global variable that stores the cocre page to be displayed (default: 0).
 */
extern int var_score_page;

/**
 * @brief Global variable that stores the last score page to be displayed.
 */
extern int var_score_max_page;

/**
 * @brief Global variable that stores the number of scores to display per page.
 */
extern int var_scores_per_page;

/**
 * @brief The four modes for the game loop.
 */
typedef enum {
    MODE_MENU, //!< Menu mode.
    MODE_GAME, //!< Game mode.
    MODE_SCORES, //!< Scores mode.
    MODE_FINAL, //!< Final scores mode.
    MODE_SIZE, //!< Number of modes.
} loop_modes;

/**
 * @brief Global variable that stores the current mode.
 */
extern loop_modes var_mode;


extern int var_nb_game;



/***************/
/*+ The menus +*/
/***************/

/**
 * @brief Internal names for the different menus.
 */
typedef enum {
    MENU_MAIN, //!< Main menu.
    MENU_SETUP, //!< Play menu.
    MENU_HELP, //!< Help menu.
    MENU_SIZE, //!< Number of menus.
} menu_type;

/**
 * @brief Global variable that stores the current menu.
 *
 * @remark
 * This variable is used to determine which menu to display when in
 * menu mode. When entering menu mode, it is set to MENU_MAIN.
 */
extern menu_type var_menu;



/*************************/
/*+ Handling explosions +*/
/*************************/



/**
 * @brief Number of explosions.
 *
 * @details
 * The number of explosions is the same as the number of snakes that are in
 * the game.
 */
extern int var_nb_explosions;


/**
 * @brief State of the explosions.
 *
 * @details
 * The state of the explosions is stored in an array of integers. Each element
 * of the array corresponds to a snake. The value of the element is the number
 * of frames since the explosion started. If the value is -1, the snake is not
 * exploding. If the value is greater than 83, the explosion is over.
 */
extern int* var_explosions_state;


/**
 * @brief Initializes the explosion state.
 */
void init_explosions_state(int //!< Number of snakes.
);


/**
 * @brief Checks whether all explosions are over.
 */
bool explosions_over(void);



#endif
