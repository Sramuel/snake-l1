#include "gui_gamevars.h"

/***********/
/*+ Flags +*/
/***********/

bool flags[NB_FLAGS];

void flip_flag(ctl_flags f) {
    flags[f] = !flags[f];
}

void set_flag(ctl_flags f) {
    flags[f] = true;
}

void remove_flag(ctl_flags f) {
    flags[f] = false;
}

void reset_flags(void) {
    for (int i = 0; i < NB_FLAGS; i++)
        flags[i] = false;
}

/******************************/
/*+ Dimensions of the window +*/
/******************************/

int var_screen_width, var_screen_height;

/*******************/
/*+ Mouse control +*/
/*******************/

int var_mousePosx;
int var_mousePosy;
bool var_leftMouseButtonDown;


/************************/
/*+ Zoom and Scrolling +*/
/************************/

bool var_dual_screen = false;

SDL_Rect var_screen[2];

unsigned char var_player_screen[2];

void init_dual_screen(void) {
    var_dual_screen = true;
    var_screen[0].x = 0;
    var_screen[0].y = 0;
    var_screen[0].w = var_screen_width / 2;
    var_screen[0].h = var_screen_height;
    var_screen[1].x = var_screen_width / 2;
    var_screen[1].y = 0;
    var_screen[1].w = var_screen_width / 2;
    var_screen[1].h = var_screen_height;
    var_player_screen[0] = 0;
    var_player_screen[1] = 1;
}

void init_single_screen(void) {
    var_dual_screen = false;
    var_screen[0].x = 0;
    var_screen[0].y = 0;
    var_screen[0].w = var_screen_width;
    var_screen[0].h = var_screen_height;
    var_player_screen[0] = 0;
    var_player_screen[1] = 0;
}

bool check_valid_screen(unsigned char i) {
    if (i != 0 && (i != 1 || !var_dual_screen)) {
        return false;
    }
    return true;
}

int var_render_zoom_level[2] = { 4, 4 };
int var_tile_size[2] = { 32,32 };

void init_zoom_demo(void) {
    var_render_zoom_level[0] = 4;
    var_tile_size[0] = 32;
}

void init_zoom_game(void) {
    var_render_zoom_level[0] = 3;
    var_tile_size[0] = 24;
    var_render_zoom_level[1] = 3;
    var_tile_size[1] = 24;
}



int var_scrollOffsetx[2];
int var_scrollOffsety[2];
int var_startx[2];
int var_starty[2];
int var_endx[2];
int var_endy[2];
int var_topleftx[2];
int var_toplefty[2];


void scroll_update_borders(unsigned char i) {

    // We check if the screen index is valid.
    if (!check_valid_screen(i)) {
        return;
    }

    int width;
    if (var_dual_screen) {
        width = var_screen_width / 2;
    }
    else {
        width = var_screen_width;
    }
    if (var_scrollOffsetx[i] >= 0) {
        var_startx[i] = 0;
        var_topleftx[i] = var_scrollOffsetx[i];
        var_endx[i] = var_startx[i] + (width - var_topleftx[i]) / (2 * var_tile_size[i]) + 2;
    }
    else {
        var_topleftx[i] = var_scrollOffsetx[i] % (2 * var_tile_size[i]);
        var_startx[i] = (var_topleftx[i] - var_scrollOffsetx[i]) / (2 * var_tile_size[i]);
        var_endx[i] = var_startx[i] + width / (2 * var_tile_size[i]) + 2;
    }

    if (var_scrollOffsety[i] >= 0) {
        var_starty[i] = 0;
        var_toplefty[i] = var_scrollOffsety[i];
        var_endy[i] = var_starty[i] + (var_screen_height - var_toplefty[i]) / (2 * var_tile_size[i]) + 2;
    }
    else {
        var_starty[i] = (-1 * var_scrollOffsety[i]) / (2 * var_tile_size[i]);
        var_toplefty[i] = var_scrollOffsety[i] % (2 * var_tile_size[i]);
        var_endy[i] = var_starty[i] + var_screen_height / (2 * var_tile_size[i]) + 2;
    }

}

void decrease_zoom(unsigned char i) {
    if (!check_valid_screen(i)) {
        return;
    }

    int d = 2;
    if (var_dual_screen) {
        d = 4;
    }

    if (var_render_zoom_level[i] <= 1) {
        return;
    }
    else {
        var_render_zoom_level[i]--;
        var_tile_size[i] = var_render_zoom_level[i] * 8;
        var_scrollOffsetx[i] = ((var_scrollOffsetx[i] - var_screen_width / d) / (var_render_zoom_level[i] + 1)) * var_render_zoom_level[i] + var_screen_width / d;
        var_scrollOffsety[i] = ((var_scrollOffsety[i] - var_screen_height / 2) / (var_render_zoom_level[i] + 1)) * var_render_zoom_level[i] + var_screen_height / 2;
        scroll_update_borders(i);
    }
}
void increase_zoom(unsigned char i) {
    if (!check_valid_screen(i)) {
        return;
    }

    int d = 2;
    if (var_dual_screen) {
        d = 4;
    }

    if (var_render_zoom_level[i] >= 6) {
        return;
    }
    else {
        var_render_zoom_level[i]++;
        var_tile_size[i] = var_render_zoom_level[i] * 8;
        var_scrollOffsetx[i] = ((var_scrollOffsetx[i] - var_screen_width / d) / (var_render_zoom_level[i] - 1)) * var_render_zoom_level[i] + var_screen_width / d;
        var_scrollOffsety[i] = ((var_scrollOffsety[i] - var_screen_height / 2) / (var_render_zoom_level[i] - 1)) * var_render_zoom_level[i] + var_screen_height / 2;
        scroll_update_borders(i);
    }
}


void scroll_manual(int x, int y, unsigned char i) {
    if (!check_valid_screen(i)) {
        return;
    }

    var_scrollOffsetx[i] += x;
    var_scrollOffsety[i] += y;
    scroll_update_borders(i);
}

void scroll_with_mouse(int x, int y) {
    if (var_dual_screen && var_mousePosx > var_screen_width / 2) {
        var_scrollOffsetx[1] += x - var_mousePosx;
        var_scrollOffsety[1] += y - var_mousePosy;
        scroll_update_borders(1);
    }
    else {
        var_scrollOffsetx[0] += x - var_mousePosx;
        var_scrollOffsety[0] += y - var_mousePosy;
        scroll_update_borders(0);

    }
}



void scroll_to_cell(board* b, int cell, unsigned char i) {
    if (!check_valid_screen(i)) {
        return;
    }


    if (b) {
        int step = var_tile_size[i] * 2;
        var_scrollOffsetx[i] = -1 * (cell % b->hsize) * step + var_screen_width / 2;
        var_scrollOffsety[i] = -1 * (cell / b->hsize) * step + var_screen_height / 2;
        scroll_update_borders(i);
    }
    else {
        fprintf(stderr, "Error: NULL board.\n");
        exit(EXIT_FAILURE);
    }
}


void scroll_to_coords(int x, int y, unsigned char i) {
    if (!check_valid_screen(i)) {
        return;
    }

    int step = var_tile_size[i] * 2;


    if (var_dual_screen) {
        var_scrollOffsetx[i] = -1 * x * step + var_screen_width / 4;
        var_scrollOffsety[i] = -1 * y * step + var_screen_height / 2;
    }
    else {
        var_scrollOffsetx[i] = -1 * x * step + var_screen_width / 2;
        var_scrollOffsety[i] = -1 * y * step + var_screen_height / 2;
    }

    scroll_update_borders(i);
}

void scroll_to_center(board* b, unsigned char i) {
    if (!check_valid_screen(i)) {
        return;
    }

    if (!b) {
        fprintf(stderr, "Error: NULL board.\n");
        exit(EXIT_FAILURE);
    }
    var_scrollOffsetx[i] = -(b->hsize + 1) * var_tile_size[i] + var_screen_width / 2;
    var_scrollOffsety[i] = -(b->vsize + 1) * var_tile_size[i] + var_screen_height / 2;
    scroll_update_borders(i);
}


/*********************/
/*+ Player tracking +*/
/*********************/

bool player_track[2] = { false, false };
int player_xstart[2];
int player_ystart[2];
int player_xshift[2];
int player_yshift[2];
int player_xbacklog[2];
int player_ybacklog[2];

void init_player_tracking(int x, int y, unsigned char i) {
    if (i != 0 && i != 1) {
        fprintf(stderr, "Invalid player.\n");
        exit(EXIT_FAILURE);
    }
    player_track[i] = true;
    player_xstart[i] = x;
    player_ystart[i] = y;
    player_xshift[i] = 0;
    player_yshift[i] = 0;
    player_xbacklog[i] = 0;
    player_ybacklog[i] = 0;
    scroll_to_coords(x, y, var_player_screen[i]);
}

void disable_player_tracking(unsigned char i) {
    if (i != 0 && i != 1) {
        fprintf(stderr, "Invalid player.\n");
        exit(EXIT_FAILURE);
    }
    player_track[i] = false;
}

void update_player_tracking(game* g, unsigned char i, int old) {

    if (g->nb_players > i && g->snakes_array[g->nb_ais + i]->alive && player_track[i]) {
        int thespeed = (g->snakes_array[g->nb_ais + i]->progress + LENGTH_CELL - old) % LENGTH_CELL;
        signed char xstep = 0, ystep = 0;
        switch (g->b->indirs[g->snakes_array[g->nb_ais + i]->head])
        {
        case UP:
            ystep += thespeed;
            break;
        case RIGHT:
            xstep -= thespeed;
            break;
        case DOWN:
            ystep -= thespeed;
            break;
        case LEFT:
            xstep += thespeed;
            break;
        default:
            break;
        }
        if (player_xbacklog[i] > 0 && xstep <= 0) {
            xstep += MIN(thespeed, player_xbacklog[i]);
            player_xbacklog[i] -= MIN(thespeed, player_xbacklog[i]);
        }
        else if (player_xbacklog[i] < 0 && xstep >= 0) {
            xstep += MAX(-thespeed, player_xbacklog[i]);
            player_xbacklog[i] -= MAX(-thespeed, player_xbacklog[i]);
        }

        if (player_ybacklog[i] > 0 && ystep <= 0) {
            ystep += MIN(thespeed, player_ybacklog[i]);
            player_ybacklog[i] -= MIN(thespeed, player_ybacklog[i]);
        }
        else if (player_ybacklog[i] < 0 && ystep >= 0) {
            ystep += MAX(-thespeed, player_ybacklog[i]);
            player_ybacklog[i] -= MAX(-thespeed, player_ybacklog[i]);
        }
        player_xshift[i] += xstep;
        player_yshift[i] += ystep;
        if ((g->snakes_array[g->nb_ais + i]->progress + speed_to_value(g->snakes_array[g->nb_ais + i]->speed)) == LENGTH_CELL) {
            switch (g->snakes_array[g->nb_ais + i]->move)
            {
            case UP:
                player_ybacklog[i] -= LENGTH_CELL;
                break;
            case RIGHT:
                player_xbacklog[i] += LENGTH_CELL;
                break;
            case DOWN:
                player_ybacklog[i] += LENGTH_CELL;
                break;
            case LEFT:
                player_xbacklog[i] -= LENGTH_CELL;
                break;
            default:
                break;
            }
            switch (g->b->indirs[g->snakes_array[g->nb_ais + i]->head])
            {
            case UP:
                player_ybacklog[i] -= LENGTH_CELL;
                break;
            case RIGHT:
                player_xbacklog[i] += LENGTH_CELL;
                break;
            case DOWN:
                player_ybacklog[i] += LENGTH_CELL;
                break;
            case LEFT:
                player_xbacklog[i] -= LENGTH_CELL;
                break;
            default:
                break;
            }
        }
        scroll_to_coords(player_xstart[i], player_ystart[i], var_player_screen[i]);
        scroll_manual(-player_xshift[i] * (2 * var_tile_size[i]) / LENGTH_CELL, -player_yshift[i] * (2 * var_tile_size[i]) / LENGTH_CELL, var_player_screen[i]);

    }

}

/*******************/
/*+ Speed control +*/
/*******************/

const char* speed_names[SPEED_SIZE] = { "Slower", "Slow", "Medium", "Fast", "Faster", "Ludicrous" };

/**************************/
/*+ Les différents menus **/
/**************************/

menu_type var_menu = MENU_MAIN;



game* menu_demo = NULL;


/*************************/
/*+ Lecture des masques **/
/*************************/

struct dirent** var_maskstab = NULL;
int var_maskindex = -1;
int var_masktabsize = 0;

static int is_mask_file(const struct dirent* dir) {
    char* ext = strstr(dir->d_name, ".msk");
    if (ext && ext[4] == '\0') {
        return true;
    }
    else {
        return false;
    }
}

void var_init_maskstab(void) {
    var_maskindex = -1;
    var_masktabsize = scandir("../Masques/", &var_maskstab, is_mask_file, alphasort);
}

void var_free_maskstab(void) {
    if (var_maskstab) {
        for (int i = 0; i < var_masktabsize;i++)
        {
            free(var_maskstab[i]);
        }
        free(var_maskstab);
    }
    var_maskstab = NULL;
    var_maskindex = -1;
    var_masktabsize = 0;
}

/********************************/
/*+ Entrée de texte au clavier **/
/********************************/

edit_mode var_edit_mode = ED_NONE;
text_buffer* var_editbuffer = NULL;


void init_text_buffer(edit_mode mode) {
    var_edit_mode = mode;
    var_editbuffer = create_text_buffer();
}




void update_from_text_buffer(void) {
    char* end_str;
    int num = strtol(var_editbuffer->content, &end_str, 10);
    if (*end_str != '\0') {
        fprintf(stderr, "Error: malformed string\n");
        return;
    }
    switch (var_edit_mode)
    {
    case ED_LENGTH:
        if (num >= 1) {
            gen_maxlength = num;
        }
        else {
            gen_maxlength = 1;
        }
        break;
    case ED_IAS:
        num = MIN(num, 10000);
        if (num > var_strats_size) {
            var_strats_size = num;
            REALLOC(var_strats, var_strats_size);
        }
        if (num > gen_iasnakes) {
            for (int i = gen_iasnakes; i < num; i++) {
                var_strats[i] = STRAT_EMPTY;
            }
            gen_iasnakes = num;
        }

        if (num <= 0) {
            gen_iasnakes = 0;
            var_ia_select = 0;
        }
        if (num > 0 && num < gen_iasnakes) {
            var_ia_select = MIN(num - 1, gen_iasnakes - 1);
            gen_iasnakes = num;
        }
        break;
    case ED_X:
        if (num > 10) {
            gen_hsize = num;
        }
        else {
            gen_hsize = 10;
        }
        break;
    case ED_Y:
        if (num > 10) {
            gen_vsize = num;
        }
        else {
            gen_vsize = 10;
        }
        break;
    case ED_SINGLEIA:
        if (num - 1 >= 0 && num - 1 < gen_iasnakes) {
            var_ia_select = num - 1;
        }
        else {
            var_ia_select = 0;
        }
        break;
    case ED_GAMES:
        if (num >= 1) {
            gen_nbgames = num;
        }
        else {
            gen_nbgames = 1;
        }
        break;
    default:
        break;
    }
}



/**********************************/
/*+ Variables pour la génération **/
/**********************************/

int gen_nbgames = 1;

int gen_players = 1;


int gen_iasnakes = 3;


int gen_hsize = 200;
int gen_vsize = 200;
int gen_nbminotaurs = 200;
int gen_braiding = 0;
bool gen_use_mask = false;
char gen_maskname[128] = "Pas de masque";

speed gen_speed = SLOW;

int gen_maxlength = 1;

strat gen_strat = STRAT_TIME;
strat var_strat_assign = STRAT_EMPTY;

int var_ia_select = 0;

/****************************/
/*+ Objects and strategies +*/
/****************************/


generator var_objgen = OGEN_BASIC;
strat* var_strats = NULL;
int var_strats_size = 0;
strat var_demo_strats[5] = { STRAT_CLOSESTFRUIT, STRAT_CLOSESTFRUIT, STRAT_CLOSESTFRUIT, STRAT_CLOSESTFRUIT, STRAT_CLOSESTFRUIT };





/*************/
/*+  Games  +*/
/*************/

game* var_game = NULL;



score_table* var_scores = NULL;

int var_score_page = 0;
int var_score_max_page = 0;
int var_scores_per_page = 0;


loop_modes var_mode = MODE_SIZE;

int var_nb_game = 0;


/*************************/
/*+ Handling explosions +*/
/*************************/

int var_nb_explosions = 0;

int* var_explosions_state = NULL;

void init_explosions_state(int n) {
    var_nb_explosions = n;
    MALLOC(var_explosions_state, n);
    for (int i = 0; i < n; i++) {
        var_explosions_state[i] = -1;
    }
}


bool explosions_over(void) {
    for (int i = 0; i < var_nb_explosions; i++) {
        if (var_explosions_state[i] >= 0 && var_explosions_state[i] < 84) {
            return false;
        }
    }
    return true;
}
