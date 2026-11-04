#include "gui_grid.h"



grid* var_grid_display = NULL;

void make_grass_tile(gridcell* cell) {
    switch (rand() % 16)
    {
    case 2:
        cell->clip[0] = CLP_GRASST1;
        cell->nbclips = 1;
        break;
    case 4:
        cell->clip[0] = CLP_GRASST2;
        cell->nbclips = 1;
        break;
    case 8:
        cell->clip[0] = CLP_GRASST3;
        cell->nbclips = 1;
        break;
    case 14:
        cell->clip[0] = CLP_GRASSC;
        cell->clip[1] = CLP_GRASSP2;
        cell->nbclips = 2;
        break;
    default:
        cell->clip[0] = CLP_GRASSC;
        cell->nbclips = 1;
        break;
    }
    cell->topdots = false;
    cell->leftdots = false;
}


void make_rock_tile(gridcell* cell) {
    switch (rand() % 30)
    {
    case 2:
        cell->clip[0] = CLP_ROCKT1;
        cell->nbclips = 1;
        break;
    case 7:
        cell->clip[0] = CLP_ROCKT2;
        cell->nbclips = 1;
        break;
    case 11:
        cell->clip[0] = CLP_ROCKT3;
        cell->nbclips = 1;
        break;
    case 14:
        cell->clip[0] = CLP_ROCKC;
        cell->clip[1] = CLP_CACTUS4;
        cell->nbclips = 2;
        break;
    case 17:
        cell->clip[0] = CLP_ROCKC;
        cell->clip[1] = CLP_CACTUS5;
        cell->nbclips = 2;
        break;
    default:
        cell->clip[0] = CLP_ROCKC;
        cell->nbclips = 1;
        break;
    }
    cell->topdots = false;
    cell->leftdots = false;
}

void make_fence_tile(gridcell* cell, direction dirh, direction dirv) {
    make_rock_tile(cell);
    if (dirh == LEFT && dirv == LEFT) {
        cell->clip[1] = CLP_GRASSR;
        cell->clip[2] = CLP_FENCEW;
        cell->nbclips = 3;
    }
    else if (dirh == LEFT && dirv == UP) {
        cell->clip[1] = CLP_GRASSDR;
        cell->clip[2] = CLP_FENCER;
        cell->clip[3] = CLP_FENCED;
        cell->nbclips = 4;
    }
    else if (dirh == LEFT && dirv == DOWN) {
        cell->clip[1] = CLP_GRASSUR;
        cell->clip[2] = CLP_FENCER;
        cell->clip[3] = CLP_FENCEU;
        cell->nbclips = 4;
    }
    else if (dirh == RIGHT && dirv == RIGHT) {
        cell->clip[1] = CLP_GRASSL;
        cell->clip[2] = CLP_FENCEW;
        cell->nbclips = 3;
    }
    else if (dirh == RIGHT && dirv == UP) {
        cell->clip[1] = CLP_GRASSDL;
        cell->clip[2] = CLP_FENCEL;
        cell->clip[3] = CLP_FENCED;
        cell->nbclips = 4;
    }
    else if (dirh == RIGHT && dirv == DOWN) {
        cell->clip[1] = CLP_GRASSUL;
        cell->clip[2] = CLP_FENCEL;
        cell->clip[3] = CLP_FENCEU;
        cell->nbclips = 4;
    }
    else if (dirh == UP && dirv == UP) {
        cell->clip[1] = CLP_GRASSD;
        cell->clip[2] = CLP_FENCEC;
        cell->nbclips = 3;
    }
    else if (dirh == DOWN && dirv == DOWN) {
        cell->clip[1] = CLP_GRASSU;
        cell->clip[2] = CLP_FENCEC;
        cell->nbclips = 3;
    }


}


void playable_to_gridcell(int i, int j, grid* gr) {
    make_grass_tile(&gr->cells[2 * i + 1][2 * j + 1]);
    make_grass_tile(&gr->cells[2 * i + 2][2 * j + 1]);
    make_grass_tile(&gr->cells[2 * i + 1][2 * j + 2]);
    make_grass_tile(&gr->cells[2 * i + 2][2 * j + 2]);
    gr->cells[2 * i + 1][2 * j + 1].topdots = true;
    gr->cells[2 * i + 1][2 * j + 1].leftdots = true;
    gr->cells[2 * i + 2][2 * j + 1].topdots = true;
    gr->cells[2 * i + 2][2 * j + 1].leftdots = false;
    gr->cells[2 * i + 1][2 * j + 2].topdots = false;
    gr->cells[2 * i + 1][2 * j + 2].leftdots = true;
    gr->cells[2 * i + 2][2 * j + 2].topdots = false;
    gr->cells[2 * i + 2][2 * j + 2].leftdots = false;
}

void masked_to_gridcell(board* b, int i, int j, grid* gr) {
    make_rock_tile(&gr->cells[2 * i + 1][2 * j + 1]);
    make_rock_tile(&gr->cells[2 * i + 2][2 * j + 1]);
    make_rock_tile(&gr->cells[2 * i + 1][2 * j + 2]);
    make_rock_tile(&gr->cells[2 * i + 2][2 * j + 2]);
    gr->cells[2 * i + 1][2 * j + 1].topdots = false;
    gr->cells[2 * i + 1][2 * j + 1].leftdots = false;
    gr->cells[2 * i + 2][2 * j + 1].topdots = false;
    gr->cells[2 * i + 2][2 * j + 1].leftdots = false;
    gr->cells[2 * i + 1][2 * j + 2].topdots = false;
    gr->cells[2 * i + 1][2 * j + 2].leftdots = false;
    gr->cells[2 * i + 2][2 * j + 2].topdots = false;
    gr->cells[2 * i + 2][2 * j + 2].leftdots = false;

    bool up = playable_cell(b, i, j - 1);
    bool down = playable_cell(b, i, j + 1);
    bool left = playable_cell(b, i - 1, j);
    bool right = playable_cell(b, i + 1, j);

    bool upleft = playable_cell(b, i - 1, j - 1);
    bool upright = playable_cell(b, i + 1, j - 1);
    bool downleft = playable_cell(b, i - 1, j + 1);
    bool downright = playable_cell(b, i + 1, j + 1);



    if (!up && !down && !left && !right && !upleft && !upright && !downleft && !downright) {
        if (!(rand() % 20)) {
            gr->cells[1 + 2 * i][1 + 2 * j].clip[0] = CLP_WATERC;
            gr->cells[2 + 2 * i][1 + 2 * j].clip[0] = CLP_WATERC;
            gr->cells[1 + 2 * i][2 + 2 * j].clip[0] = CLP_WATERC;
            gr->cells[2 + 2 * i][2 + 2 * j].clip[0] = CLP_WATERC;

            gr->cells[1 + 2 * i][1 + 2 * j].clip[1] = CLP_ROCKFLU;
            gr->cells[2 + 2 * i][1 + 2 * j].clip[1] = CLP_ROCKFRU;
            gr->cells[1 + 2 * i][2 + 2 * j].clip[1] = CLP_ROCKFLD;
            gr->cells[2 + 2 * i][2 + 2 * j].clip[1] = CLP_ROCKFRD;
            gr->cells[1 + 2 * i][1 + 2 * j].nbclips = 2;
            gr->cells[2 + 2 * i][1 + 2 * j].nbclips = 2;
            gr->cells[1 + 2 * i][2 + 2 * j].nbclips = 2;
            gr->cells[2 + 2 * i][2 + 2 * j].nbclips = 2;
        }
        return;
    }

    if (up) {
        gr->cells[2 * i + 1][2 * j + 1].topdots = true;
        gr->cells[2 * i + 2][2 * j + 1].topdots = true;
    }

    if (left) {
        gr->cells[2 * i + 1][2 * j + 1].leftdots = true;
        gr->cells[2 * i + 1][2 * j + 2].leftdots = true;
    }

    // Left-up corner 
    if (left && up) {
        gr->cells[1 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSFLU;
        gr->cells[1 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCEL;
        gr->cells[1 + 2 * i][1 + 2 * j].clip[3] = CLP_FENCEU;
        gr->cells[1 + 2 * i][1 + 2 * j].nbclips = 4;
    }
    else if (left) {
        gr->cells[1 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSR;
        gr->cells[1 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCEW;
        gr->cells[1 + 2 * i][1 + 2 * j].nbclips = 3;
    }
    else if (up) {
        gr->cells[1 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSD;
        gr->cells[1 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCEC;
        gr->cells[1 + 2 * i][1 + 2 * j].nbclips = 3;
    }
    else if (upleft) {
        gr->cells[1 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSDR;
        gr->cells[1 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCER;
        gr->cells[1 + 2 * i][1 + 2 * j].clip[3] = CLP_FENCED;
        gr->cells[1 + 2 * i][1 + 2 * j].nbclips = 4;
    }

    // Right-up corner
    if (right && up) {
        gr->cells[2 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSFRU;
        gr->cells[2 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCER;
        gr->cells[2 + 2 * i][1 + 2 * j].clip[3] = CLP_FENCEU;
        gr->cells[2 + 2 * i][1 + 2 * j].nbclips = 4;
    }
    else if (right) {
        gr->cells[2 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSL;
        gr->cells[2 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCEW;
        gr->cells[2 + 2 * i][1 + 2 * j].nbclips = 3;
    }
    else if (up) {
        gr->cells[2 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSD;
        gr->cells[2 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCEC;
        gr->cells[2 + 2 * i][1 + 2 * j].nbclips = 3;
    }
    else if (upright) {
        gr->cells[2 + 2 * i][1 + 2 * j].clip[1] = CLP_GRASSDL;
        gr->cells[2 + 2 * i][1 + 2 * j].clip[2] = CLP_FENCEL;
        gr->cells[2 + 2 * i][1 + 2 * j].clip[3] = CLP_FENCED;
        gr->cells[2 + 2 * i][1 + 2 * j].nbclips = 4;
    }

    // Left-down corner
    if (left && down) {
        gr->cells[1 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSFLD;
        gr->cells[1 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCEL;
        gr->cells[1 + 2 * i][2 + 2 * j].clip[3] = CLP_FENCED;
        gr->cells[1 + 2 * i][2 + 2 * j].nbclips = 4;
    }
    else if (left) {
        gr->cells[1 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSR;
        gr->cells[1 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCEW;
        gr->cells[1 + 2 * i][2 + 2 * j].nbclips = 3;
    }
    else if (down) {
        gr->cells[1 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSU;
        gr->cells[1 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCEC;
        gr->cells[1 + 2 * i][2 + 2 * j].nbclips = 3;
    }
    else if (downleft) {
        gr->cells[1 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSUR;
        gr->cells[1 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCER;
        gr->cells[1 + 2 * i][2 + 2 * j].clip[3] = CLP_FENCEU;
        gr->cells[1 + 2 * i][2 + 2 * j].nbclips = 4;
    }

    // Right-down corner
    if (right && down) {
        gr->cells[2 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSFRD;
        gr->cells[2 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCER;
        gr->cells[2 + 2 * i][2 + 2 * j].clip[3] = CLP_FENCED;
        gr->cells[2 + 2 * i][2 + 2 * j].nbclips = 4;
    }
    else if (right) {
        gr->cells[2 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSL;
        gr->cells[2 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCEW;
        gr->cells[2 + 2 * i][2 + 2 * j].nbclips = 3;
    }
    else if (down) {
        gr->cells[2 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSU;
        gr->cells[2 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCEC;
        gr->cells[2 + 2 * i][2 + 2 * j].nbclips = 3;
    }
    else if (downright) {
        gr->cells[2 + 2 * i][2 + 2 * j].clip[1] = CLP_GRASSUL;
        gr->cells[2 + 2 * i][2 + 2 * j].clip[2] = CLP_FENCEL;
        gr->cells[2 + 2 * i][2 + 2 * j].clip[3] = CLP_FENCEU;
        gr->cells[2 + 2 * i][2 + 2 * j].nbclips = 4;
    }
}







bool playable_cell(board* b, int i, int j) {
    if (i < 0 || j < 0 || i >= b->hsize || j >= b->vsize) {
        return false;
    }
    if (b->masked[j * b->hsize + i]) {
        return false;
    }
    return true;
}


grid* create_grid(board* b) {
    grid* gr;
    MALLOC(gr, 1);
    gr->width = b->hsize * 2 + 2;
    gr->height = b->vsize * 2 + 2;
    MALLOC(gr->cells, gr->width);
    for (int i = 0; i < gr->width; i++) {
        MALLOC(gr->cells[i], gr->height);
    }

    // Left-Up corner
    make_rock_tile(&gr->cells[0][0]);
    if (playable_cell(b, 0, 0)) {
        make_fence_tile(&gr->cells[0][0], RIGHT, DOWN);
    }
    gr->cells[0][0].topdots = false;
    gr->cells[0][0].leftdots = false;

    // Right-Up corner
    make_rock_tile(&gr->cells[gr->width - 1][0]);
    if (playable_cell(b, b->hsize - 1, 0)) {
        gr->cells[gr->width - 1][0].clip[1] = CLP_GRASSUR;
        gr->cells[gr->width - 1][0].clip[2] = CLP_FENCER;
        gr->cells[gr->width - 1][0].clip[3] = CLP_FENCEU;
        gr->cells[gr->width - 1][0].nbclips = 4;
    }
    gr->cells[gr->width - 1][0].topdots = false;
    gr->cells[gr->width - 1][0].leftdots = false;

    // Left-Down corner
    make_rock_tile(&gr->cells[0][gr->height - 1]);
    if (playable_cell(b, 0, b->vsize - 1)) {
        gr->cells[0][gr->height - 1].clip[1] = CLP_GRASSDL;
        gr->cells[0][gr->height - 1].clip[2] = CLP_FENCEL;
        gr->cells[0][gr->height - 1].clip[3] = CLP_FENCED;
        gr->cells[0][gr->height - 1].nbclips = 4;
    }
    gr->cells[0][gr->height - 1].topdots = false;
    gr->cells[0][gr->height - 1].leftdots = false;

    // Right-Down corner
    make_rock_tile(&gr->cells[gr->width - 1][gr->height - 1]);
    if (playable_cell(b, b->hsize - 1, b->vsize - 1)) {
        gr->cells[gr->width - 1][gr->height - 1].clip[1] = CLP_GRASSDR;
        gr->cells[gr->width - 1][gr->height - 1].clip[2] = CLP_FENCER;
        gr->cells[gr->width - 1][gr->height - 1].clip[3] = CLP_FENCED;
        gr->cells[gr->width - 1][gr->height - 1].nbclips = 4;
    }
    gr->cells[gr->width - 1][gr->height - 1].topdots = false;
    gr->cells[gr->width - 1][gr->height - 1].leftdots = false;

    // Top border
    for (int i = 0; i < b->hsize;i++) {
        make_rock_tile(&gr->cells[1 + 2 * i][0]);
        make_rock_tile(&gr->cells[2 + 2 * i][0]);
        if (playable_cell(b, i, 0)) {
            make_fence_tile(&gr->cells[1 + 2 * i][0], DOWN, DOWN);
            make_fence_tile(&gr->cells[2 + 2 * i][0], DOWN, DOWN);
        }
        else {
            if (i > 0 && playable_cell(b, i - 1, 0)) {
                make_fence_tile(&gr->cells[1 + 2 * i][0], LEFT, DOWN);
            }
            if (i < b->hsize - 1 && playable_cell(b, i + 1, 0)) {
                make_fence_tile(&gr->cells[2 + 2 * i][0], RIGHT, DOWN);
            }

        }
        gr->cells[1 + 2 * i][0].topdots = false;
        gr->cells[2 + 2 * i][0].topdots = false;
        gr->cells[1 + 2 * i][0].leftdots = false;
        gr->cells[2 + 2 * i][0].leftdots = false;
    }


    // Bottom border
    for (int i = 0; i < b->hsize;i++) {
        make_rock_tile(&gr->cells[1 + 2 * i][gr->height - 1]);
        make_rock_tile(&gr->cells[2 + 2 * i][gr->height - 1]);
        gr->cells[1 + 2 * i][gr->height - 1].leftdots = false;
        gr->cells[2 + 2 * i][gr->height - 1].leftdots = false;
        gr->cells[1 + 2 * i][gr->height - 1].topdots = false;
        gr->cells[2 + 2 * i][gr->height - 1].topdots = false;
        if (playable_cell(b, i, b->vsize - 1)) {
            make_fence_tile(&gr->cells[1 + 2 * i][gr->height - 1], UP, UP);
            make_fence_tile(&gr->cells[2 + 2 * i][gr->height - 1], UP, UP);
            gr->cells[1 + 2 * i][gr->height - 1].topdots = true;
            gr->cells[2 + 2 * i][gr->height - 1].topdots = true;
        }
        else {
            if (i > 0 && playable_cell(b, i - 1, b->vsize - 1)) {
                make_fence_tile(&gr->cells[1 + 2 * i][0], LEFT, UP);
            }
            if (i < b->hsize - 1 && playable_cell(b, i + 1, b->vsize - 1)) {
                make_fence_tile(&gr->cells[2 + 2 * i][0], RIGHT, UP);
            }

        }

    }

    // Left border
    for (int i = 0; i < b->vsize;i++) {
        make_rock_tile(&gr->cells[0][1 + 2 * i]);
        make_rock_tile(&gr->cells[0][2 + 2 * i]);
        if (playable_cell(b, 0, i)) {
            make_fence_tile(&gr->cells[0][1 + 2 * i], RIGHT, RIGHT);
            make_fence_tile(&gr->cells[0][2 + 2 * i], RIGHT, RIGHT);
        }
        else {
            if (i > 0 && playable_cell(b, 0, i - 1)) {
                make_fence_tile(&gr->cells[0][1 + 2 * i], RIGHT, UP);
            }
            if (i < b->vsize - 1 && playable_cell(b, 0, i + 1)) {
                make_fence_tile(&gr->cells[0][2 + 2 * i], RIGHT, DOWN);
            }
        }

        gr->cells[0][1 + 2 * i].topdots = false;
        gr->cells[0][2 + 2 * i].topdots = false;
        gr->cells[0][1 + 2 * i].leftdots = false;
        gr->cells[0][2 + 2 * i].leftdots = false;
    }

    // Right border
    for (int i = 0; i < b->vsize;i++) {
        make_rock_tile(&gr->cells[gr->width - 1][1 + 2 * i]);
        make_rock_tile(&gr->cells[gr->width - 1][2 + 2 * i]);
        gr->cells[gr->width - 1][1 + 2 * i].leftdots = false;
        gr->cells[gr->width - 1][2 + 2 * i].leftdots = false;
        gr->cells[gr->width - 1][1 + 2 * i].topdots = false;
        gr->cells[gr->width - 1][2 + 2 * i].topdots = false;
        if (playable_cell(b, b->hsize - 1, i)) {
            make_fence_tile(&gr->cells[gr->width - 1][1 + 2 * i], LEFT, LEFT);
            make_fence_tile(&gr->cells[gr->width - 1][2 + 2 * i], LEFT, LEFT);
            gr->cells[gr->width - 1][1 + 2 * i].leftdots = true;
            gr->cells[gr->width - 1][2 + 2 * i].leftdots = true;
        }
        else {
            if (i > 0 && playable_cell(b, b->hsize - 1, i - 1)) {
                make_fence_tile(&gr->cells[gr->width - 1][1 + 2 * i], LEFT, UP);
            }
            if (i < b->vsize - 1 && playable_cell(b, b->hsize - 1, i + 1)) {
                make_fence_tile(&gr->cells[gr->width - 1][2 + 2 * i], LEFT, DOWN);
            }
        }
    }

    // Inner cells
    for (int i = 0; i < b->hsize;i++) {
        for (int j = 0; j < b->vsize;j++) {

            if (playable_cell(b, i, j)) {
                playable_to_gridcell(i, j, gr);
            }
            else {
                masked_to_gridcell(b, i, j, gr);
            }
        }
    }
    return gr;
}




void delete_grid(grid* gr) {
    if (!gr) {
        return;
    }
    for (int i = 0; i < gr->width; i++) {
        free(gr->cells[i]);
    }
    free(gr->cells);
    free(gr);
}




void display_grid(grid* gr, int p) {

    SDL_Rect postop;
    SDL_Rect pos;
    postop.h = var_tile_size[p];
    postop.w = var_tile_size[p];
    pos.h = var_tile_size[p];
    pos.w = var_tile_size[p];
    SDL_Rect hline;
    hline.h = 1;
    hline.w = var_tile_size[p] / 4;
    SDL_Rect vline;
    vline.h = var_tile_size[p] / 4;
    vline.w = 1;

    int endx = MIN(var_endx[p], (gr->width - 2) / 2);
    int endy = MIN(var_endy[p], (gr->height - 2) / 2);

    postop.x = var_topleftx[p];
    postop.y = var_toplefty[p];


    int x = var_startx[p] * 2;
    int y = var_starty[p] * 2;

    int xmax = endx * 2 + 2;
    int ymax = endy * 2 + 2;


    for (int i = x; i < xmax; i++) {
        pos.x = postop.x;
        pos.y = postop.y;
        for (int j = y; j < ymax;j++) {
            for (int k = 0; k < gr->cells[i][j].nbclips; k++) {
                SDL_RenderCopy(renderer, txt_terrain, &clp_textures[gr->cells[i][j].clip[k]], &pos);
            }
            if (gr->cells[i][j].topdots) {
                hline.x = pos.x;
                hline.y = pos.y;
                SDL_RenderFillRect(renderer, &hline);
                hline.x += var_tile_size[p] / 2;
                SDL_RenderFillRect(renderer, &hline);


            }

            if (gr->cells[i][j].leftdots) {
                vline.x = pos.x;
                vline.y = pos.y;
                SDL_RenderFillRect(renderer, &vline);
                vline.y += var_tile_size[p] / 2;
                SDL_RenderFillRect(renderer, &vline);
            }

            pos.y += var_tile_size[p];
        }
        postop.x += var_tile_size[p];
    }


}
