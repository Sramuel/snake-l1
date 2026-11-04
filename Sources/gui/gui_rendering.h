/**
 * @file gui_rendering.h
 * @brief
 * Rendering. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

#ifndef _GUI_RENDERING_H_
#define _GUI_RENDERING_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_timer.h>
#include <dirent.h>

#include "../project_snake.h"
#include "gui_init_graphic.h"
#include "gui_gamevars.h"
#include "gui_menus.h"

 /*  ____                _           _              */
 /* |  _ \ ___ _ __   __| | ___ _ __(_)_ __   __ _  */
 /* | |_) / _ \ '_ \ / _` |/ _ \ '__| | '_ \ / _` | */
 /* |  _ <  __/ | | | (_| |  __/ |  | | | | | (_| | */
 /* |_| \_\___|_| |_|\__,_|\___|_|  |_|_| |_|\__, | */
 /*                                          |___/  */


/*****************************/
/*+ Preliminary functions   **/
/*****************************/

/**
 * @brief Gets the position of a cell on the screen (used for snakes)
 */
void render_get_cellpos(int, //!< Horizontal coordinate of the cell in the board.
    int, //!< Vertical coordinate of the cell in the board.
    int, //!< Screen used
    SDL_Rect* //!< Postion is returned by pointer.
);

/**
 * @brief Gets the position of a cell on the screen (used for tiles)
 */
void render_get_cellpos_tile(int, //!< Horizontal coordinate of the cell in the board.
    int, //!< Vertical coordinate of the cell in the board.
    int, //!< Screen used
    SDL_Rect* //!< Postion is returned by pointer.
);

/**
 * @brief Returns a Boolean indicating whether the a cell is outside the screen.
 */
bool render_outofview(int //!< Horizontal coordinate of the cell in the board.
    , int //!< Vertical coordinate of the cell in the board.
    , int //!< Screen used.
);



/************************/
/*+ Displaying objects **/
/************************/

/**
 * @brief Displays all the objects.
 */
void render_objects(board* //!< The board.
    , int // The screen used.
);


/**
 * @brief Displays the empty cells as given by the array empty_cells_listing.
 */
void render_empty_cells(board* //!< The board.
    , int // The screen used.
);

/**
 * @brief Displays the empty cells as marked in the array empty_cells_indices.
 */
void render_empty_cells_indices(board* //!< The board.
    , int // The screen used.
);


/**
 * @brief Displays the snake filled cells.
 */
void render_snake_cells(board* //!< The board.
    , int // The screen used.
);


/*****************/
/*+ Display snakes */
/*****************/


/**
 * @brief Displays the snake's head.
 */
void render_snake_head(direction, //!< The direction from which the head entered the cell.
    direction, //!< The direction toward which the head is moving.
    bool, //!< Is the snake large? (2 cells long at least)
    int, //!< Animation frame to display (0 to 15).
    int, //!< Screen used.
    SDL_Rect* //!< Position of the cell on the screen.
);


/**
 * @brief Displays the snake's tail.
 */
void render_snake_tail(direction, //!< The direction from which the tail entered the cell.
    direction, //!< The direction towards which the snake exited the cell.
    bool, //!< Is the snake large? (2 cells long at least)
    int, //!< Animation frame to display (0 to 15).
    int, //!< Screen used.
    SDL_Rect* //!< Position of the cell on the screen.
);

/**
 * @brief Displays a segment of the snake's body.
 */

void render_static_part(direction, //!< The direction from which the segment entered the cell.
    direction, //!< The direction towards which the snake exited the cell.
    bool, //!< Is the segment a tail?
    bool, //!< Is the segment a full segment?
    int, //!< Screen used.
    SDL_Rect* //!< Position of the cell on the screen.
);


/**
 * @brief Displays a single tile of the snake.
 */
void render_tile_snake(direction, //!< The direction from which the segment entered the cell.
    direction, //!< The direction towards which the snake exited the cell.
    int, //!< Screen used.
    SDL_Rect* //!< Position of the cell on the screen.
);

/**
 * @brief Displays a snake.
 */
void render_snake(game*, //!< The game.
    int, //!< The snake index in the game.
    int, //!< The frame of the animation (0 to 15).
    int //!< The screen used.
);


/**********************/
/*+ Displaying ingame score **/
/*******************/


/**
 * @brief Displays the score of a player in the game.
 */
void render_ingame_score(game*, //!< The game to display.
    int //!< The player to display.
);


/**********************/
/*+ Displaying explosion **/
/*******************/

/**
 * @brief Displays the explosion of a snake.
 */
void render_snake_explosion(int, //!< Index of the snake in the game.
    int, //!< Explosion state (0 to 83).
    int //!< Screen used.
);

#endif // _GUI_RENDERING_H_
