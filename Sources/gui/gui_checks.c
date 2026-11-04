#include "gui_checks.h"


bool check_board(board* b) {
    if (!b) {
        fprintf(stderr, "Error: The board is NULL.\n");
        return false;
    }
    if (b->hsize <= 0) {
        fprintf(stderr, "Error: The horizontal size of the board is invalid.\n");
        return false;
    }
    if (b->vsize <= 0) {
        fprintf(stderr, "Error: The vertical size of the board is invalid.\n");
        return false;
    }
    if (b->size != b->hsize * b->vsize) {
        fprintf(stderr, "Error: The size of the board is invalid.\n");
        return false;
    }
    if (!b->objects) {
        fprintf(stderr, "Error: The objects table of the board is NULL.\n");
        return false;
    }
    if (!b->outdirs) {
        fprintf(stderr, "Error: The outdirs table of the board is NULL.\n");
        return false;
    }
    if (!b->indirs) {
        fprintf(stderr, "Error: The indirs table of the board is NULL.\n");
        return false;
    }
    if (!b->masked) {
        fprintf(stderr, "Error: The table of masked cells of the board is NULL.\n");
        return false;
    }
    if (b->empty_cells_count < 0 || b->empty_cells_count > b->size) {
        fprintf(stderr, "Error: The number of empty cells of the board is invalid.\n");
        return false;
    }
    if (!b->empty_cells_listing) {
        fprintf(stderr, "Error: The table of empty cells of the board is NULL.\n");
        return false;
    }
    if (!b->empty_cells_indices) {
        fprintf(stderr, "Error: The table of indices of empty cells of the board is NULL.\n");
        return false;
    }

    // Checking the empty cell listing
    for (int i = 0; i < b->empty_cells_count; i++) {

        if (b->empty_cells_listing[i] < 0 || b->empty_cells_listing[i] >= b->size) {
            fprintf(stderr, "Error: The empty cell listing is invalid.\n");
            return false;
        }
    }
    for (int i = 0; i < b->size; i++) {
        if (b->masked[i]) {
            continue;
        }

        if ((b->objects[i] == EMPTY && b->empty_cells_indices[i] == -1) || (b->objects[i] != EMPTY && b->empty_cells_indices[i] != -1)) {
            fprintf(stderr, "Error: The empty cell listing is invalid.\n");
            return false;
        }
    }
    for (int i = 0; i < b->size; i++) {
        if (b->masked[i]) {
            continue;
        }
        if (b->empty_cells_indices[i] != -1 && b->empty_cells_listing[b->empty_cells_indices[i]] != i) {
            fprintf(stderr, "Error: The empty cell listing is invalid.\n");
            return false;
        }
    }


    return true;
}

bool check_snake(snake* s, int size) {
    if (!s) {
        fprintf(stderr, "Error: The snake is NULL.\n");
        return false;
    }
    if (s->full_length <= 0) {
        fprintf(stderr, "Error: The full length of the snake is invalid.\n");
        return false;
    }
    if (s->length <= 0 || s->length > s->full_length) {
        fprintf(stderr, "Error: The length of the snake is invalid.\n");
        return false;
    }
    if (s->score < 0) {
        fprintf(stderr, "Error: The score of the snake is invalid.\n");
        return false;
    }
    if (s->distance < 0) {
        fprintf(stderr, "Error: The distance of the snake is invalid.\n");
        return false;
    }
    if (s->progress < 0) {
        fprintf(stderr, "Error: The progress of the snake is invalid.\n");
        return false;
    }
    if (s->head < 0 || s->head >= size) {
        fprintf(stderr, "Error: The head of the snake is invalid.\n");
        return false;
    }
    if (s->tail < 0 || s->tail >= size) {
        fprintf(stderr, "Error: The tail of the snake is invalid.\n");
        return false;
    }
    if (s->head == s->tail) {
        fprintf(stderr, "Error: The head and tail of the snake are the same.\n");
        return false;
    }
    if (s->speed < 0 || s->speed >= SPEED_SIZE) {
        fprintf(stderr, "Error: The speed of the snake is invalid.\n");
        return false;
    }
    if (s->move < 0 || s->move >= DIRECTION_SIZE) {
        fprintf(stderr, "Error: The direction of the snake is invalid.\n");
        return false;
    }
    return true;
}




bool check_game(game* g) {

    if (!g) {
        fprintf(stderr, "The game is NULL.\n");
        return false;
    }
    if (g->nb_players < 0 || g->nb_players > 2) {
        fprintf(stderr, "The number of players is invalid.\n");
        return false;
    }
    if (g->nb_ais < 0) {
        fprintf(stderr, "The number of computer controlled snakes is invalid.\n");
        return false;
    }
    if (g->nb_alive < 0) {
        fprintf(stderr, "The number of alive snakes is invalid.\n");
        return false;
    }
    if (!check_board(g->b)) {
        return false;
    }



    for (int i = 0; i < g->nb_ais + g->nb_players; i++) {
        if (!check_snake(g->snakes_array[i], g->b->size)) {
            return false;
        }
    }


    return true;
}

bool check_score(score_table* st) {
    if (!st) {
        fprintf(stderr, "Error: The score table is NULL.\n");
        return false;
    }

    if (!st->game_to_score) {
        fprintf(stderr, "Error: The game_to_score table is NULL.\n");
        return false;
    }
    if (!st->score_to_game) {
        fprintf(stderr, "Error: The score_to_game table is NULL.\n");
        return false;
    }
    if (st->nb_games < 0) {
        fprintf(stderr, "Error: The number of games is invalid.\n");
        return false;
    }
    if (st->cu_game < 0 || st->cu_game > st->nb_games) {
        fprintf(stderr, "Error: The number of the current game is invalid.\n");
        return false;
    }

    if (!st->scores) {
        fprintf(stderr, "Error: The whole scores array is NULL.\n");
        return false;
    }

    for (int i = 0; i < st->nb_snakes; i++) {
        if (!st->scores[i]) {
            fprintf(stderr, "Error: The scores array of snake %d is NULL.\n", i);
            return false;
        }
        for (int j = 0; j < st->nb_games + 1; j++) {
            if (!st->scores[i][j]) {
                fprintf(stderr, "Error: The score object of snake %d in game %d is NULL.\n", i, j);
                return false;
            }
        }
    }
    return true;
}
