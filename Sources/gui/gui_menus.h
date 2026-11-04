/**
 * @file gui_menus.h
 * @brief
 * Menus. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

#ifndef _GUI_MENUS_H_
#define _GUI_MENUS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_timer.h>
#include <dirent.h>

#include "gui_init_graphic.h"
#include "gui_gamevars.h"
#include "../project_tools.h"

 /*  __  __                       */
 /* |  \/  | ___ _ __  _   _ ___  */
 /* | |\/| |/ _ \ '_ \| | | / __| */
 /* | |  | |  __/ | | | |_| \__ \ */
 /* |_|  |_|\___|_| |_|\__,_|___/ */


/*********************/
/*+ Menu parameters +*/
/*********************/

// Main menu
#define MAIN_STEP 75 // Separation between buttons
#define MAIN_BWIDTH 240 // Button width

// Score menu
#define SCORE_BT_WIDTH 180 // Button width
#define SCORE_BT_SEP 210 // Separation between buttons
#define SCORE_BT_TOP 200 // Top of the buttons
#define SCORE_TI_TOP 80 // Top of the title
#define SCORE_WI_TOP 160 // Top of the window
#define SCORE_NB_TOP 240 // Top of the scores
#define SCORE_NB_STEP 30 // Step between scores
#define SCORE_BOT_SPACE 200 // Space at the bottom


// Play menu
#define PLAY_TITLETOP 110 // Top of the title
#define PLAY_SIDEDIST 330 // Distance between the sides and the center
#define PLAY_TOPWINDOW 210 // Distance between the title and the top of the sides
#define PLAY_TOPWINDOW2 360 // Distance between the title and the top of the sides
#define PLAY_PLAYERTOP 290 // Top of the player selector
#define PLAY_BOTB 800 // Bottom buttons top
#define PLAY_BOTSEP 200 // Separation between bottom buttons and the center

#define PLAY_NBIASTOP 440 // Top of the IAs selector
#define PLAY_IASTRATEGYTOP 540 // Top of the strategy selector
#define PLAY_IASINGLETOP 640 // Top of the single IAs strategy selector
#define PLAY_IAGLOBALTOP 700 // Top of the global IAs set button



#define PLAY_MASKTOP 290 // Top of the mask selector
#define PLAY_SIZETOP 390 // Top of the sizes selector
#define PLAY_OBJTOP 490 // Top of the object generator selector
#define PLAY_SLTOP 590 // Top of the speed/length selector
#define PLAY_ROUNDTOP 690 // Top of the games number selector

// Help Menu

/*************/
/*+ Anchors +*/
/*************/

typedef enum {
    ANC_NW, //!< North-West.
    ANC_NC, //!< North-Centre.
    ANC_NE, //!< North-East.
    ANC_CW, //!< Centre-West.
    ANC_CC, //!< Centre-Centre.
    ANC_CE, //!< Centre-East.
    ANC_SW, //!< South-West.
    ANC_SC, //!< South-Centre.
    ANC_SE //!< South-East.
} anchor;

/**
 * @brief Shifts the coordinates from the anchor to top left.
 */
void shift_to_anchor(int*, //!< Horizontal coordinate.
    int*, //!< Vertical coordinate.
    int, //!< Width.
    int, //!< Height.
    anchor //!< Anchor.
);


/*************/
/*+ buttons +*/
/*************/


/**
 * @brief Internal names of all buttons.
 */
typedef enum {

    // Main Menu
    BT_QGAME, //!< Launch quick game.
    BT_SETUP, //!< Game setup.
    BT_HELP, //!< Help.
    BT_QUIT, //!< Quit.

    // Play Menu

    BT_LAUNCH, //!< Launch the game.
    BT_PBACK, //!< Back to the main menu.

    BT_NBGAMES, //!< Number of games.
    BT_INISPEEDL, //!< Speed.
    BT_INISPEEDR, //!< Speed.
    BT_INILENGTH, //!< Size.
    BT_HSIZE, //!< Horizontal size.
    BT_VSIZE, //!< Vertical size.
    BT_GENEL, //!< Generator
    BT_GENER, //!< Generator
    BT_MASKL, //!< Mask
    BT_MASKR, //!< Mask


    BT_NBPLAYERSL, //!< Number of players.
    BT_NBPLAYERSR, //!< Number of players.
    BT_NBIAS, //!< Number of IAs.


    BT_IASELEC, // IAs selector
    BT_IASTRATL, // Global IAs left
    BT_IASTRATR, // Global IAs right
    BT_IAGLOBAL, // Global IAs set
    BT_IASINGLE, // Single IA set

    // Help Menu
    BT_HELPBACK, //!< Back to the main menu.


    // Score display
    BT_SCORE,
    BT_STUDENTS,
    BT_LENGTH,
    BT_DISTANCE,
    BT_TIME,
    BT_NEXTSCORE,
    BT_PREVSCORE,
    BT_QUITSCORE,
    BT_QUITSCORENULL,

    BT_SIZE,
    BT_NONE,
} button;

/**
 * @brief Counter for the button animation.
 */
extern int var_button_countdown;

/**
 * @brief Currently selected button.
 */
extern button var_selected_button;

/**
 * @brief The last pushed button.
 */
extern button var_pushed_button;

/**
 * @brief Array indicating which buttons are currently being pushed (for animations).
 */
extern bool var_buttons_flags[BT_SIZE];

/**
 * @brief Réinitialistion des boutons.
 */
void var_reset_buttons(void);

/**
 * @brief Pushed a button.
 */
void var_push_button(button);

/**
 * @brief Releases a button.
 */
void var_release_button(button);

/**
 * @brief Data for the buttons.
 */
typedef struct {
    char label[128];
    bool big;
    int x;
    int y;
    int t_x;
    int t_y;
    int w;
    int h;
    TTF_Font* font;
    button up;
    button left;
    button down;
    button right;
} button_data;


/**
 * @brief Initialization of a single button
 */
void init_button(button, //!< The button.
    const char*, //!< The label.
    bool, //!< Big button?
    int, //!< Horizontal coordinate.
    int, //!< Vertical coordinate.
    int, //!< Width.
    TTF_Font*, //!< Font to use.
    button, //!< Up button.
    button, //!< Right button.
    button, //!< Down button.
    button, //!< Left button.
    anchor //!< Anchor.
);



/**
 * @brief Initialization of two selector buttons.
 */
void init_selec_buttons(button, //!< The left button.
    button, //!< The right button.
    int, //!< Horizontal coordinate.
    int, //!< Vertical coordinate.
    int, //!< Width of the selector.
    TTF_Font*, //!< Font to use.
    anchor //!< Anchor.
);


/**
 * @brief Initialization of two selector buttons.
 */
void init_text_button(button, //!< The button.
    int, //!< Horizontal coordinate.
    int, //!< Vertical coordinate.
    int, //!< Width of the editor.
    TTF_Font*, //!< Font to use.
    anchor //!< Anchor.
);


/**
 * @brief Initialization of all buttons.
 */
void init_all_buttons(void);


/**
 * @brief Capture the mouse on a button.
 */
bool mouse_capture_button(int, //!< Horizontal coordinate of the mouse.
    int, //!< Vertical coordinate of the mouse.
    button //!< The button.
);


/**
 * @brief Render a button.
 */
void render_button(button //!< The button.
);



/***********************/
/*+ General functions +*/
/***********************/


/**
 * @brief Displays the menu.
 *
 * @details
 * Calls the appropriate rendering function according to the current menu.
 */
void render_menu(void);


/**
 * @brief Changes the menu.
 */
void change_menu(menu_type //!< The new menu.
);

/**
 * @brief Handles the keyboard on the menu.
 *
 * @details
 * Calls the appropriate function according to the current menu.
 */
void keyboard_menu(SDL_KeyCode //!< The key.
);


/**
 * @brief Handles the mouse on the menu.
 *
 * @details
 * Calls the appropriate function according to the current menu.
 */
void mouse_menu(int, //!< Horizontal coordinate of the mouse.
    int //!< Vertical coordinate of the mouse.
);




/***************/
/*+ Main menu **/
/***************/


/**
 * @brief Displays the main menu.
 */
void render_mainmenu(void);


/**
 * @brief Handles the keyboard on the main menu.
 */
void keyboard_mainmenu(SDL_KeyCode //!< The key.
);


/**
 * @brief Handles the mouse on the main menu.
 */
void mouse_mainmenu(int, //!< Horizontal coordinate of the mouse.
    int //!< Vertical coordinate of the mouse.
);




/***************/
/*+ Play menu **/
/***************/

/**
 * @brief Displays the play menu.
 */
void render_playmenu(void);

/**
 * @brief Handles the keyboard on the play menu.
 */
void keyboard_playmenu(SDL_KeyCode //!< The key.
);

/**
 * @brief Handles the mouse on the play menu.
 */
void mouse_playmenu(int, //!< Horizontal coordinate of the mouse.
    int //!< Vertical coordinate of the mouse.
);

/****************/
/*+ Help menu +**/
/****************/

/**
 * @brief Displays the help menu.
 */
void render_helpmenu(void);

/**
 * @brief Handles the keyboard on the help menu.
 */
void keyboard_helpmenu(SDL_KeyCode //!< The key.
);

/**
 * @brief Handles the mouse on the help menu.
 */
void mouse_helpmenu(int, //!< Horizontal coordinate of the mouse.
    int //!< Vertical coordinate of the mouse.
);



/*******************/
/*+ Render scores +*/
/*******************/


/**
 * @brief Displays the scores.
 */
void render_scores(bool //!< Final scores?
);

/**
 * @brief Handles the mouse on the scores.
 */
void mouse_scores(int, //!< Horizontal coordinate of the mouse.
    int //!< Vertical coordinate of the mouse.
);

/**
 * @brief Handles the keyboard on the scores.
 */
void keyboard_scores(SDL_KeyCode //!< The key.
);

/*********************/
/*+ Displaying text **/
/*********************/

/**
 * @brief Displays text.
 */
int render_text(int //!< Horizontal coordinate.
    , int //!< Vertical coordinate.
    , const char* //!< Text to display.
    , TTF_Font* //!< Font to use.
    , anchor //!< Anchor.
);

/**
 * @brief Displays text in an edition buffer.
 */
void print_text_buffer_center(void);

/***************************/
/*+ Displaying frames **/
/***************************/


/**
 * @brief Dislays a selector.
 */
void render_selector(button, //!< The left button.
    button, //!< The right button.
    const char* //!< The string to display.
);


/**
 * @brief Displays an editable selector.
 */
void render_selector_edit(button, //!< The button.
    const char* //!< The text to display.
);

/**
 * @brief Displays a frame.
 */
void render_frame(int x //!< Horizontal coordinate.
    , int //!< Vertical coordinate.
    , int //!< Width.
    , int //!< Height.
    , const char* //!< Title.
    , anchor //!< Anchor.
);






#endif // _GUI_MENUS_H_
