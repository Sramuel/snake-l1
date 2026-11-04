/**
 * @file gui_checks.h
 * @brief
 * Error checks. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

#ifndef _GUI_CHECKS_H_
#define _GUI_CHECKS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../project_board.h"
#include "../project_snake.h"
#include "../project_game.h"
#include "../project_score.h"

 /*  _____                            _               _    _              */
 /* | ____|_ __ _ __ ___  _ __    ___| |__   ___  ___| | _(_)_ __   __ _  */
 /* |  _| | '__| '__/ _ \| '__|  / __| '_ \ / _ \/ __| |/ / | '_ \ / _` | */
 /* | |___| |  | | | (_) | |    | (__| | | |  __/ (__|   <| | | | | (_| | */
 /* |_____|_|  |_|  \___/|_|     \___|_| |_|\___|\___|_|\_\_|_| |_|\__, | */
 /*                                                                |___/  */

 /**
  * @brief Checks whether a board is well initialized.
  *
  * @return True if the board is well initialized.
  */
bool check_board(board* //!< The board.
);

/**
 * @brief Checks whether a snake is well initialized.
 *
 * @return True if the snake is well initialized.
 */
bool check_snake(snake*, //!< The snake.
    int //!< The size of the board.
);

/**
 * @brief Checks whether a game is well initialized.
 *
 * @return True if the game is well initialized.
 */
bool check_game(game* //!< The game.
);

/**
 * @brief Checks whether a score table is well initialized.
 *
 * @return True if the score table is well initialized.
 */
bool check_score(score_table* //!< The score table.
);



#endif // _GUI_CHECKS_H_
