/**
 * @file gui_grid.h
 * @brief
 * Pre-computation of the displayed grid. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

#ifndef _GUI_GRID_H_
#define _GUI_GRID_H_

 /*   ____      _     _      */
 /*  / ___|_ __(_) __| |___  */
 /* | |  _| '__| |/ _` / __| */
 /* | |_| | |  | | (_| \__ \ */
 /*  \____|_|  |_|\__,_|___/ */

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../project_tools.h"
#include "../project_board.h"
#include "gui_init_graphic.h"

 /**
  * @brief
  * Structure used to represent a single grid cell on the screen. It contains the clips to use to render the cell.
  *
  * @remark
  * A cell of the board corresponds to FOUR grid cells.
  */
typedef struct {
    textureclips clip[4]; //!< The clips.
    unsigned char nbclips; //!< The number of clips to use (1, 2, 3 or 4).
    bool topdots; //!< Whether the cell has dots on the top.
    bool leftdots; //!< Whether the cell has dots on the left.
} gridcell;


/**
 * @brief
 * Structure used to represent the grid dislpayed on the screen.
 *
 * @remark
 * The grid is built from the board. If the board has size (hsize, vsize), the grid has
 * size (2 * hsize + 2, 2 * vsize + 2): 4 grid cells for each cell of the board, plus the
 * border.
 */
typedef struct
{
    gridcell** cells; // Two-dimensional array of grid cells.
    int width; // Width of the grid.
    int height; // Height of the grid.
} grid;

extern grid* var_grid_display; //!< The grid displayed on the screen.

/************/
/* Creation */
/************/

/**
 * @brief
 * Returns a random grass tile.
 */
textureclips random_rock_tile(void);

/**
 * @brief
 * Makes a single grid cell a grass tile (the specific grass
 * tile is chosen randomly).
 *
 * @remark
 * Does not set the dots.
 */
void make_grass_tile(gridcell* //!< The grid cell to set as a grass tile.
);

/**
 * @brief
 * Makes a single grid cell a rock tile (the specific rock
 * tile is chosen randomly).
 *
 * @remark
 * Does not set the dots.
 */
void make_rock_tile(gridcell* //!< The grid cell to set as a rock tile.
);

void make_fence_tile(gridcell* cell, direction dirh, direction dirv);

/**
 * @brief
 * Fully builds the four grid cells corresponding to a playable cell
 * of the board.
 *
 * @remark
 * The cell is assumed to be playable.
 */
void playable_to_gridcell(int, //!< The horizontal coordinate of the board cell.
    int, //!< The vertical coordinate of the board cell.
    grid* //!< The grid to build.
);

/**
 * @brief
 * Fully builds the four grid cells corresponding to a masked cell
 * of the board.
 *
 * @remark
 * The cell is assumed to be masked.
 */
void masked_to_gridcell(board*, //!< The board.
    int, //!< The horizontal coordinate of the board cell.
    int, //!< The vertical coordinate of the board cell.
    grid* //!< The grid to build.
);


/**
 * @brief
 * Checks whether a cell of the board is playable (inside the board
 * and not masked).
 *
 * @return
 * True if the cell is playable, false otherwise.
 */
bool playable_cell(board*, //!< The board.
    int, //!< The horizontal coordinate of the cell.
    int  //!< The vertical coordinate of the cell.
);

/**
 * @brief
 * Creation of the grid displayed on the screen from a board.
 *
 * @return
 * The grid displayed on the screen.
 */
grid* create_grid(board* //!< The board to display.
);

/**
 * @brief
 * Free the memory allocated for a grid.
 */
void delete_grid(grid* //!< The grid.
);




/**
 * @brief
 * Displays the grid on the screen.
 */
void display_grid(grid*, //!< The grid to display.
    int i //!< The screen on which the grid must be displayed.
);


#endif // _GUI_GRID_H_
