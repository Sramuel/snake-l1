#include "gui_menus.h"

char menus_buffer[128];

/**
 * @brief Data for the all buttons.
 */
button_data var_buttons[BT_SIZE];

/*************/
/*+ Anchors +*/
/*************/


void shift_to_anchor(int* x, int* y, int w, int h, anchor anc) {
    switch (anc)
    {
    case ANC_NW:
        break;
    case ANC_NC:
        *x -= w / 2;
        break;
    case ANC_NE:
        *x -= w;
        break;
    case ANC_CW:
        *y -= h / 2;
        break;
    case ANC_CC:
        *x -= w / 2;
        *y -= h / 2;
        break;
    case ANC_CE:
        *x -= w;
        *y -= h / 2;
        break;
    case ANC_SW:
        *y -= h;
        break;
    case ANC_SC:
        *x -= w / 2;
        *y -= h;
        break;
    case ANC_SE:
        *x -= w;
        *y -= h;
        break;
    default:
        break;
    }
}

/*************/
/*+ button+*/
/*************/


int var_button_countdown = 0;
button var_selected_button = BT_NONE;
bool var_buttons_flags[BT_SIZE];

button var_pushed_button = BT_NONE;


void var_reset_buttons(void) {
    for (int i = 0; i < BT_SIZE;i++) {
        var_buttons_flags[i] = false;
    }
}

void var_push_button(button bt) {
    var_pushed_button = bt;
    var_buttons_flags[bt] = true;
    var_button_countdown = SDL_GetTicks();
}

void var_release_button(button bt) {
    var_buttons_flags[bt] = false;
}

#define SBUTTON_BWIDTH 60
#define SBUTTON_HEIGHT 32
#define LBUTTON_BWIDTH 80
#define LBUTTON_HEIGHT 48

void init_button(button bt, const char* label, bool big, int x, int y, int w, TTF_Font* thefont, button up, button right, button down, button left, anchor a) {
    strcpy(var_buttons[bt].label, label);
    var_buttons[bt].big = big;

    var_buttons[bt].x = x;
    var_buttons[bt].y = y;
    var_buttons[bt].font = thefont;

    var_buttons[bt].up = up;
    var_buttons[bt].left = left;
    var_buttons[bt].down = down;
    var_buttons[bt].right = right;

    if (big) {
        if (w < 2 * LBUTTON_BWIDTH) {
            w = 2 * LBUTTON_BWIDTH;
        }
        var_buttons[bt].w = w;
        var_buttons[bt].h = LBUTTON_HEIGHT;

        shift_to_anchor(&var_buttons[bt].x, &var_buttons[bt].y, var_buttons[bt].w, LBUTTON_HEIGHT, a);
    }
    else {
        if (w < 2 * SBUTTON_BWIDTH) {
            w = 2 * SBUTTON_BWIDTH;
        }
        var_buttons[bt].w = w;
        var_buttons[bt].h = SBUTTON_HEIGHT;

        shift_to_anchor(&var_buttons[bt].x, &var_buttons[bt].y, var_buttons[bt].w, SBUTTON_HEIGHT, a);
    }
}

void init_selec_buttons(button lb, button rb, int x, int y, int width, TTF_Font* thefont, anchor a) {
    if (width < 4 * 46) {
        width = 4 * 46;
    }
    var_buttons[lb].x = x;
    var_buttons[lb].y = y;
    shift_to_anchor(&var_buttons[lb].x, &var_buttons[lb].y, width, 48, a);
    var_buttons[lb].w = 46;
    var_buttons[lb].h = 48;
    var_buttons[lb].font = thefont;
    var_buttons[lb].up = BT_NONE;
    var_buttons[lb].right = BT_NONE;
    var_buttons[lb].down = BT_NONE;
    var_buttons[lb].left = BT_NONE;

    var_buttons[rb].x = var_buttons[lb].x + width - 46;
    var_buttons[rb].y = var_buttons[lb].y;
    var_buttons[rb].w = 46;
    var_buttons[rb].h = 48;
    var_buttons[rb].font = thefont;
    var_buttons[rb].up = BT_NONE;
    var_buttons[rb].right = BT_NONE;
    var_buttons[rb].down = BT_NONE;
    var_buttons[rb].left = BT_NONE;
}

void init_text_button(button bt, int x, int y, int width, TTF_Font* thefont, anchor a) {
    if (width < 4 * 46) {
        width = 4 * 46;
    }
    var_buttons[bt].t_x = x;
    var_buttons[bt].t_y = y;
    shift_to_anchor(&var_buttons[bt].t_x, &var_buttons[bt].t_y, width, 48, a);
    var_buttons[bt].x = var_buttons[bt].t_x + width - 46;
    var_buttons[bt].y = var_buttons[bt].t_y;
    var_buttons[bt].w = 46;
    var_buttons[bt].h = 48;
    var_buttons[bt].font = thefont;
    var_buttons[bt].up = BT_NONE;
    var_buttons[bt].right = BT_NONE;
    var_buttons[bt].down = BT_NONE;
    var_buttons[bt].left = BT_NONE;
}









void init_all_buttons(void) {
    int middle = var_screen_width / 2;

    // Main menu
    int y = 310;
    init_button(BT_QGAME, "Quick game", true, middle, y, MAIN_BWIDTH, Jungle36, BT_QUIT, BT_QGAME, BT_SETUP, BT_QGAME, ANC_CC);
    y += MAIN_STEP;
    init_button(BT_SETUP, "Setup game", true, middle, y, MAIN_BWIDTH, Jungle36, BT_QGAME, BT_SETUP, BT_HELP, BT_SETUP, ANC_CC);
    y += MAIN_STEP;
    init_button(BT_HELP, "Help", true, middle, y, MAIN_BWIDTH, Jungle36, BT_SETUP, BT_HELP, BT_QUIT, BT_HELP, ANC_CC);
    y += MAIN_STEP;
    init_button(BT_QUIT, "Quit", true, middle, y, MAIN_BWIDTH, Jungle36, BT_HELP, BT_QUIT, BT_QGAME, BT_QUIT, ANC_CC);


    // Score menu
    init_button(BT_SCORE, "Score", false, middle - SCORE_BT_SEP / 2 - SCORE_BT_SEP, SCORE_BT_TOP, SCORE_BT_WIDTH, Jungle20, BT_QUITSCORE, BT_STUDENTS, BT_PREVSCORE, BT_TIME, ANC_CC);
    init_button(BT_STUDENTS, "Students eaten", false, middle - SCORE_BT_SEP / 2, SCORE_BT_TOP, SCORE_BT_WIDTH, Jungle20, BT_QUITSCORE, BT_LENGTH, BT_PREVSCORE, BT_SCORE, ANC_CC);
    init_button(BT_LENGTH, "Final length", false, middle + SCORE_BT_SEP / 2, SCORE_BT_TOP, SCORE_BT_WIDTH, Jungle20, BT_QUITSCORE, BT_DISTANCE, BT_PREVSCORE, BT_STUDENTS, ANC_CC);
    init_button(BT_DISTANCE, "Visited cells", false, middle + SCORE_BT_SEP / 2 + SCORE_BT_SEP, SCORE_BT_TOP, SCORE_BT_WIDTH, Jungle20, BT_QUITSCORE, BT_TIME, BT_PREVSCORE, BT_LENGTH, ANC_CC);
    init_button(BT_TIME, "Time alive", false, middle + SCORE_BT_SEP / 2 + 2 * SCORE_BT_SEP, SCORE_BT_TOP, SCORE_BT_WIDTH, Jungle20, BT_QUITSCORE, BT_SCORE, BT_PREVSCORE, BT_DISTANCE, ANC_CC);

    init_button(BT_PREVSCORE, "Previous", false, middle - (SCORE_BT_SEP / 2), var_screen_height - SCORE_BOT_SPACE - 50, SCORE_BT_WIDTH, Jungle20, BT_SCORE, BT_NEXTSCORE, BT_QUITSCORE, BT_NEXTSCORE, ANC_SC);
    init_button(BT_NEXTSCORE, "Next", false, middle + (SCORE_BT_SEP / 2), var_screen_height - SCORE_BOT_SPACE - 50, SCORE_BT_WIDTH, Jungle20, BT_SCORE, BT_PREVSCORE, BT_QUITSCORE, BT_PREVSCORE, ANC_SC);
    init_button(BT_QUITSCORE, "Continue", true, middle, var_screen_height - SCORE_BOT_SPACE / 2, 240, Jungle28, BT_NEXTSCORE, BT_QUITSCORE, BT_SCORE, BT_QUITSCORE, ANC_CC);
    init_button(BT_QUITSCORENULL, "Continue", true, middle, var_screen_height - SCORE_BOT_SPACE / 2, 240, Jungle28, BT_QUITSCORENULL, BT_QUITSCORENULL, BT_QUITSCORENULL, BT_QUITSCORENULL, ANC_CC);

    // Play menu


    init_button(BT_LAUNCH, "Launch game", true, middle + PLAY_BOTSEP, PLAY_BOTB, 280, Jungle28, BT_LAUNCH, BT_LAUNCH, BT_LAUNCH, BT_PBACK, ANC_NC);
    init_button(BT_PBACK, "Go to main menu", true, middle - PLAY_BOTSEP, PLAY_BOTB, 280, Jungle28, BT_LAUNCH, BT_LAUNCH, BT_LAUNCH, BT_PBACK, ANC_NC);

    init_selec_buttons(BT_NBPLAYERSL, BT_NBPLAYERSR, middle - PLAY_SIDEDIST, PLAY_PLAYERTOP, 500, Jungle24, ANC_CC);
    init_selec_buttons(BT_MASKL, BT_MASKR, middle + PLAY_SIDEDIST, PLAY_MASKTOP, 500, Jungle24, ANC_CC);



    init_text_button(BT_NBIAS, middle - PLAY_SIDEDIST, PLAY_NBIASTOP, 500, Jungle24, ANC_CC);

    init_selec_buttons(BT_IASTRATL, BT_IASTRATR, middle - PLAY_SIDEDIST, PLAY_IASTRATEGYTOP, 500, Jungle24, ANC_CC);

    init_text_button(BT_IASELEC, (middle - PLAY_SIDEDIST) - 250, PLAY_IASINGLETOP, 250, Jungle24, ANC_CW);

    init_button(BT_IASINGLE, "Assign to this IA", false, (middle - PLAY_SIDEDIST) + 250, PLAY_IASINGLETOP, 230, Jungle24, BT_IASINGLE, BT_IASINGLE, BT_IASINGLE, BT_IASINGLE, ANC_CE);


    init_button(BT_IAGLOBAL, "Assign as a common strategy to all IAs", false, middle - PLAY_SIDEDIST, PLAY_IAGLOBALTOP, 500, Jungle24, BT_IAGLOBAL, BT_IAGLOBAL, BT_IAGLOBAL, BT_IAGLOBAL, ANC_CC);




    init_text_button(BT_HSIZE, (middle + PLAY_SIDEDIST) - 250, PLAY_SIZETOP, 250, Jungle24, ANC_CW);
    init_text_button(BT_VSIZE, (middle + PLAY_SIDEDIST) + 250, PLAY_SIZETOP, 250, Jungle24, ANC_CE);

    init_selec_buttons(BT_GENEL, BT_GENER, middle + PLAY_SIDEDIST, PLAY_OBJTOP, 500, Jungle24, ANC_CC);

    init_selec_buttons(BT_INISPEEDL, BT_INISPEEDR, (middle + PLAY_SIDEDIST) - 250, PLAY_SLTOP, 250, Jungle24, ANC_CW);
    init_text_button(BT_INILENGTH, (middle + PLAY_SIDEDIST) + 250, PLAY_SLTOP, 250, Jungle24, ANC_CE);

    init_text_button(BT_NBGAMES, middle + PLAY_SIDEDIST, PLAY_ROUNDTOP, 500, Jungle24, ANC_CC);


    // Help menu


    init_button(BT_HELPBACK, "Go to main menu", true, middle, PLAY_BOTB, 280, Jungle28, BT_HELPBACK, BT_HELPBACK, BT_HELPBACK, BT_HELPBACK, ANC_NC);
    return;
}


bool mouse_capture_button(int x, int y, button b) {
    if (x < var_buttons[b].x || x > var_buttons[b].x + var_buttons[b].w) {
        return false;
    }
    if (y < var_buttons[b].y || y > var_buttons[b].y + var_buttons[b].h) {
        return false;
    }
    var_push_button(b);
    set_flag(PUSHED);
    return true;


}


void render_button(button b) {
    int height;
    int bwidth;


    if (var_buttons[b].big) {
        height = LBUTTON_HEIGHT;
        bwidth = LBUTTON_BWIDTH;
    }
    else {
        height = SBUTTON_HEIGHT;
        bwidth = SBUTTON_BWIDTH;
    }
    int twidth = var_buttons[b].w - 2 * bwidth;
    SDL_Rect pos;
    pos.x = var_buttons[b].x;
    pos.y = var_buttons[b].y;
    pos.h = height;
    pos.w = bwidth;

    // The button itself

    if (var_buttons_flags[b]) {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_BIGBLON], &pos);
        pos.x += bwidth;
        if (twidth > 0) {
            pos.w = twidth;
            SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_BIGBCON], &pos);
            pos.w = bwidth;
            pos.x += twidth;
        }
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_BIGBRON], &pos);
    }
    else {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_BIGBLOFF], &pos);
        pos.x += bwidth;
        if (twidth > 0) {
            pos.w = twidth;
            SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_BIGBCOFF], &pos);
            pos.w = bwidth;
            pos.x += twidth;
        }
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_BIGBROFF], &pos);
    }

    int x = var_buttons[b].x + var_buttons[b].w / 2;
    int y = var_buttons[b].y + height / 2;

    if (var_buttons[b].font == Paci20) {

        render_text(x, y + 2, var_buttons[b].label, var_buttons[b].font, ANC_CC);
    }
    else {
        render_text(x, y, var_buttons[b].label, var_buttons[b].font, ANC_CC);
    }


    if (var_selected_button == b) {
        if (var_buttons[b].big) {
            pos.h = 50;
            pos.w = 50;
            pos.x = var_buttons[b].x - 50;
            pos.y -= 2;
            SDL_RenderCopy(renderer, txt_icons, &clp_textures[CLP_ARRE], &pos);
            pos.x = var_buttons[b].x + var_buttons[b].w;
            SDL_RenderCopy(renderer, txt_icons, &clp_textures[CLP_ARRW], &pos);
        }
        else {
            pos.h = 30;
            pos.w = 30;
            pos.x = var_buttons[b].x - 30;
            pos.y -= 0;
            SDL_RenderCopy(renderer, txt_icons, &clp_textures[CLP_ARRE], &pos);

        }



    }


}


/***********************/
/*+ General functions +*/
/***********************/


void render_menu(void) {
    switch (var_menu)
    {
    case MENU_MAIN:
        render_mainmenu();
        break;
    case MENU_SETUP:
        render_playmenu();
        break;
    case MENU_HELP:
        render_helpmenu();
        break;
    default:
        break;
    }
}


void change_menu(menu_type new_menu) {
    switch (new_menu)
    {
    case MENU_MAIN:
        var_menu = MENU_MAIN;
        new_menu = MENU_SIZE;
        var_selected_button = BT_QGAME;
        break;
    case MENU_SETUP:
        var_menu = MENU_SETUP;
        new_menu = MENU_SIZE;
        var_selected_button = BT_LAUNCH;
        break;
    case MENU_HELP:
        var_menu = MENU_HELP;
        new_menu = MENU_SIZE;
        var_selected_button = BT_HELPBACK;
        break;
    default:
        break;
    }
}



void keyboard_menu(SDL_KeyCode key) {
    switch (key)
    {
    case SDLK_UP:
        var_selected_button = var_buttons[var_selected_button].up;
        return;
        break;
    case SDLK_DOWN:
        var_selected_button = var_buttons[var_selected_button].down;
        return;
        break;
    case SDLK_LEFT:
        var_selected_button = var_buttons[var_selected_button].left;
        return;
        break;
    case SDLK_RIGHT:
        var_selected_button = var_buttons[var_selected_button].right;
        return;
        break;
    case SDLK_RETURN:
        var_push_button(var_selected_button);
        set_flag(PUSHED);
        return;
        break;

    default:
        break;
    }

    switch (var_menu)
    {
    case MENU_MAIN:
        keyboard_mainmenu(key);
        break;
    case MENU_SETUP:
        keyboard_playmenu(key);
        break;
    case MENU_HELP:
        keyboard_helpmenu(key);
        break;
    default:
        break;
    }

}

void mouse_menu(int x, int y) {
    switch (var_menu)
    {
    case MENU_MAIN:
        mouse_mainmenu(x, y);
        break;
    case MENU_SETUP:
        mouse_playmenu(x, y);
        break;
    case MENU_HELP:
        mouse_helpmenu(x, y);
        break;
    default:
        break;
    }
}



/***************/
/*+ Main menu **/
/***************/

void render_mainmenu(void) {
    int y = 110;
    render_frame(var_screen_width / 2, y, 800, 100, NULL, ANC_CC);
    render_text(var_screen_width / 2, y, "The InitC Snake Game", SnakeFont, ANC_CC);

    render_button(BT_QGAME);
    render_button(BT_SETUP);
    render_button(BT_HELP);
    render_button(BT_QUIT);

}


void keyboard_mainmenu(SDL_KeyCode key) {
    return;
}

void mouse_mainmenu(int x, int y) {
    for (int i = BT_QGAME; i <= BT_QUIT; i++) {
        mouse_capture_button(x, y, i);
    }
}





/***************/
/*+ Play menu **/
/***************/


void render_playmenu(void) {
    int middle = var_screen_width / 2;

    render_frame(middle, PLAY_TITLETOP, 400, 100, NULL, ANC_CC);
    render_text(middle, PLAY_TITLETOP, "Game parameters", Jungle36, ANC_CC);




    int xleft = middle - PLAY_SIDEDIST;
    int mwidth = 560;

    render_frame(xleft, PLAY_TOPWINDOW, mwidth, 120, NULL, ANC_NC);

    render_text(xleft, PLAY_PLAYERTOP - 40, "Number of players", Jungle24, ANC_CC);
    switch (gen_players)
    {
    case 0:
        render_selector(BT_NBPLAYERSL, BT_NBPLAYERSR, "No player");
        break;
    case 1:
        render_selector(BT_NBPLAYERSL, BT_NBPLAYERSR, "One player");
        break;
    case 2:
        render_selector(BT_NBPLAYERSL, BT_NBPLAYERSR, "Two players");
        break;
    default:
        break;
    }

    render_frame(xleft, PLAY_TOPWINDOW2, mwidth, 400, NULL, ANC_NC);

    render_text(middle - PLAY_SIDEDIST, PLAY_NBIASTOP - 40, "Number of IAs", Jungle24, ANC_CC);
    if (var_edit_mode == ED_IAS) {
        print_text_buffer_center();
        render_selector_edit(BT_NBIAS, menus_buffer);
    }
    else {
        sprintf(menus_buffer, "%d", gen_iasnakes);
        render_selector_edit(BT_NBIAS, menus_buffer);
    }

    if (gen_iasnakes > 0) {


        render_text(middle - PLAY_SIDEDIST, PLAY_IASTRATEGYTOP - 40, "Choose a strategy to assign", Jungle24, ANC_CC);
        render_selector(BT_IASTRATL, BT_IASTRATR, strat_names[var_strat_assign]);

        sprintf(menus_buffer, "Assign to IA %d. Current: %s", var_ia_select + 1, strat_names[var_strats[var_ia_select]]);
        render_text(middle - PLAY_SIDEDIST, PLAY_IASINGLETOP - 40, menus_buffer, Jungle24, ANC_CC);

        if (var_edit_mode == ED_SINGLEIA) {
            print_text_buffer_center();
            render_selector_edit(BT_IASELEC, menus_buffer);
        }
        else {
            sprintf(menus_buffer, "%d", var_ia_select + 1);
            render_selector_edit(BT_IASELEC, menus_buffer);
        }

        render_button(BT_IASINGLE);


        render_button(BT_IAGLOBAL);
    }




    render_frame(middle + PLAY_SIDEDIST, PLAY_TOPWINDOW, mwidth, PLAY_TOPWINDOW2 + 400 - PLAY_TOPWINDOW, NULL, ANC_NC);

    render_text(middle + PLAY_SIDEDIST, PLAY_MASKTOP - 40, "Mask used for the board", Jungle24, ANC_CC);
    if (gen_use_mask) {
        render_selector(BT_MASKL, BT_MASKR, gen_maskname);
    }
    else {
        render_selector(BT_MASKL, BT_MASKR, "No mask");
    }

    render_text(middle + PLAY_SIDEDIST - 125, PLAY_SIZETOP - 40, "Horizontal size", Jungle24, ANC_CC);
    if (var_edit_mode == ED_X) {
        print_text_buffer_center();
        render_selector_edit(BT_HSIZE, menus_buffer);
    }
    else {
        sprintf(menus_buffer, "%d", gen_hsize);
        render_selector_edit(BT_HSIZE, menus_buffer);
    }

    render_text(middle + PLAY_SIDEDIST + 125, PLAY_SIZETOP - 40, "Vertical size", Jungle24, ANC_CC);
    if (var_edit_mode == ED_Y) {
        print_text_buffer_center();
        render_selector_edit(BT_VSIZE, menus_buffer);
    }
    else {
        sprintf(menus_buffer, "%d", gen_vsize);
        render_selector_edit(BT_VSIZE, menus_buffer);
    }

    render_text(middle + PLAY_SIDEDIST, PLAY_OBJTOP - 40, "Object generator", Jungle24, ANC_CC);
    render_selector(BT_GENEL, BT_GENER, generator_names[var_objgen]);

    render_text(middle + PLAY_SIDEDIST - 125, PLAY_SLTOP - 40, "Initial speed", Jungle24, ANC_CC);
    render_selector(BT_INISPEEDL, BT_INISPEEDR, speed_names[gen_speed]);



    render_text(middle + PLAY_SIDEDIST + 125, PLAY_SLTOP - 40, "Initial full length", Jungle24, ANC_CC);
    if (var_edit_mode == ED_LENGTH) {
        print_text_buffer_center();
        render_selector_edit(BT_INILENGTH, menus_buffer);
    }
    else {
        sprintf(menus_buffer, "%d", gen_maxlength);
        render_selector_edit(BT_INILENGTH, menus_buffer);
    }

    render_text(middle + PLAY_SIDEDIST, PLAY_ROUNDTOP - 40, "Number of rounds", Jungle24, ANC_CC);
    if (var_edit_mode == ED_GAMES) {
        print_text_buffer_center();
        render_selector_edit(BT_NBGAMES, menus_buffer);
    }
    else {
        sprintf(menus_buffer, "%d", gen_nbgames);
        render_selector_edit(BT_NBGAMES, menus_buffer);
    }



    render_button(BT_LAUNCH);
    render_button(BT_PBACK);

    return;

}


void mouse_playmenu(int x, int y) {
    for (int i = BT_LAUNCH; i <= BT_NBIAS; i++) {
        mouse_capture_button(x, y, i);
    }

    if (gen_iasnakes > 0) {
        for (int i = BT_IASELEC; i <= BT_IASINGLE; i++) {
            mouse_capture_button(x, y, i);
        }
    }

}


void keyboard_playmenu(SDL_KeyCode key) {
    switch (key)
    {
    case SDLK_ESCAPE:
        var_push_button(BT_PBACK);
        set_flag(PUSHED);
        break;
    case SDLK_l:
        var_push_button(BT_LAUNCH);
        set_flag(PUSHED);
        break;
    default:
        break;
    }

}


/****************/
/*+ Help menu +**/
/****************/


#define HELP_PADTOP 200
#define HELP_PADSTEP 60

void render_helpmenu(void) {
    int middle = var_screen_width / 2;
    int xleft = middle - PLAY_SIDEDIST;
    int xright = middle + PLAY_SIDEDIST;
    int mwidth = 500;


    // Left side

    render_frame(xleft, PLAY_TOPWINDOW - 80 - 50, mwidth, 420, NULL, ANC_NC);
    render_text(xleft, PLAY_PLAYERTOP - 40 - 80 - 50, "Player 1 Controls", Jungle24, ANC_CC);

    SDL_Rect pos;
    pos.x = xleft - 25;
    pos.y = HELP_PADTOP;
    pos.h = 50;
    pos.w = 50;

    SDL_Rect posr;
    posr.h = 2;
    posr.w = 75;


    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(xleft, HELP_PADTOP + 25, "z", Jungle28, ANC_CC);

    posr.x = xleft - 110;
    posr.y = HELP_PADTOP + 24;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xleft - 118, HELP_PADTOP + 25, "Go Up", Jungle24, ANC_CE);



    pos.y += HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(xleft, HELP_PADTOP + 25 + HELP_PADSTEP, "s", Jungle28, ANC_CC);

    posr.x = xleft;
    posr.y = HELP_PADTOP + 25 + 2 * HELP_PADSTEP;
    posr.w = 104;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xleft + 113, HELP_PADTOP + 2 * HELP_PADSTEP + 25, "Go Down", Jungle24, ANC_CW);

    posr.h = 31;
    posr.w = 2;
    posr.y -= 31;
    SDL_RenderFillRect(renderer, &posr);


    posr.h = 2;
    posr.w = 75;

    pos.x -= HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(xleft - HELP_PADSTEP, HELP_PADTOP + 25 + HELP_PADSTEP, "q", Jungle28, ANC_CC);

    posr.x = xleft - 105;
    posr.y = HELP_PADTOP + 25 + HELP_PADSTEP;
    posr.w -= HELP_PADSTEP;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xleft - 113, HELP_PADTOP + 25 + HELP_PADSTEP, "Go Left", Jungle24, ANC_CE);

    pos.x += 2 * HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(xleft + HELP_PADSTEP, HELP_PADTOP + 25 + HELP_PADSTEP, "d", Jungle28, ANC_CC);

    posr.x = xleft + HELP_PADSTEP + 25 + 6;
    posr.y = HELP_PADTOP + 25 + HELP_PADSTEP;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xleft + 113, HELP_PADTOP + 25 + HELP_PADSTEP, "Go Right", Jungle24, ANC_CW);

    pos.x -= (HELP_PADSTEP + 30);

    pos.y += 2 * HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(pos.x + 25, pos.y + 25, "1", Jungle28, ANC_CC);


    posr.x = pos.x - 60 + 25;
    posr.y = 25 + pos.y + HELP_PADSTEP;
    posr.w = 62;
    SDL_RenderFillRect(renderer, &posr);
    render_text(posr.x - 4, posr.y, "Zoom Out", Jungle24, ANC_CE);

    posr.x = pos.x + 25;
    posr.h = 31;
    posr.w = 2;
    posr.y -= 31;
    SDL_RenderFillRect(renderer, &posr);


    pos.x += HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(pos.x + 25, pos.y + 25, "2", Jungle28, ANC_CC);


    posr.x = pos.x + 25;
    posr.y = 25 + pos.y + HELP_PADSTEP;
    posr.h = 2;
    posr.w = 62;
    SDL_RenderFillRect(renderer, &posr);
    render_text(posr.x + 66, posr.y, "Zoom In", Jungle24, ANC_CW);

    posr.x = pos.x + 25;
    posr.h = 31;
    posr.w = 2;
    posr.y -= 31;
    SDL_RenderFillRect(renderer, &posr);






    // Right side

    render_frame(xright, PLAY_TOPWINDOW - 80 - 50, mwidth, 420, NULL, ANC_NC);
    render_text(xright, PLAY_PLAYERTOP - 40 - 80 - 50, "Player 2 Controls", Jungle24, ANC_CC);
    render_text(xright, PLAY_PLAYERTOP - 40 - 100, "(controls Player 1 if no Player 2)", Jungle24, ANC_CC);


    pos.x = xright - 25;
    pos.y = HELP_PADTOP;
    pos.h = 50;
    pos.w = 50;


    posr.h = 2;
    posr.w = 75;


    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    SDL_RenderCopy(renderer, txt_icons, &clp_textures[CLP_ARRN], &pos);
    // render_text(xright, HELP_PADTOP + 25, "z", Jungle28, ANC_CC);

    posr.x = xright - 110;
    posr.y = HELP_PADTOP + 24;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xright - 118, HELP_PADTOP + 25, "Go Up", Jungle24, ANC_CE);



    pos.y += HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    SDL_RenderCopy(renderer, txt_icons, &clp_textures[CLP_ARRS], &pos);
    //    render_text(xright, HELP_PADTOP + 25 + HELP_PADSTEP, "s", Jungle28, ANC_CC);

    posr.x = xright;
    posr.y = HELP_PADTOP + 25 + 2 * HELP_PADSTEP;
    posr.w = 104;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xright + 113, HELP_PADTOP + 2 * HELP_PADSTEP + 25, "Go Down", Jungle24, ANC_CW);

    posr.h = 31;
    posr.w = 2;
    posr.y -= 31;
    SDL_RenderFillRect(renderer, &posr);


    posr.h = 2;
    posr.w = 75;

    pos.x -= HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    SDL_RenderCopy(renderer, txt_icons, &clp_textures[CLP_ARRW], &pos);
    //render_text(xright - HELP_PADSTEP, HELP_PADTOP + 25 + HELP_PADSTEP, "q", Jungle28, ANC_CC);

    posr.x = xright - 105;
    posr.y = HELP_PADTOP + 25 + HELP_PADSTEP;
    posr.w -= HELP_PADSTEP;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xright - 113, HELP_PADTOP + 25 + HELP_PADSTEP, "Go Left", Jungle24, ANC_CE);

    pos.x += 2 * HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    SDL_RenderCopy(renderer, txt_icons, &clp_textures[CLP_ARRE], &pos);
    //render_text(xright + HELP_PADSTEP, HELP_PADTOP + 25 + HELP_PADSTEP, "d", Jungle28, ANC_CC);

    posr.x = xright + HELP_PADSTEP + 25 + 6;
    posr.y = HELP_PADTOP + 25 + HELP_PADSTEP;
    SDL_RenderFillRect(renderer, &posr);
    render_text(xright + 113, HELP_PADTOP + 25 + HELP_PADSTEP, "Go Right", Jungle24, ANC_CW);

    pos.x -= (HELP_PADSTEP + 30);

    pos.y += 2 * HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(pos.x + 25, pos.y + 25, "8", Jungle28, ANC_CC);


    posr.x = pos.x - 60 + 25;
    posr.y = 25 + pos.y + HELP_PADSTEP;
    posr.w = 62;
    SDL_RenderFillRect(renderer, &posr);
    render_text(posr.x - 4, posr.y, "Zoom Out", Jungle24, ANC_CE);

    posr.x = pos.x + 25;
    posr.h = 31;
    posr.w = 2;
    posr.y -= 31;
    SDL_RenderFillRect(renderer, &posr);


    pos.x += HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(pos.x + 25, pos.y + 25, "9", Jungle28, ANC_CC);


    posr.x = pos.x + 25;
    posr.y = 25 + pos.y + HELP_PADSTEP;
    posr.h = 2;
    posr.w = 62;
    SDL_RenderFillRect(renderer, &posr);
    render_text(posr.x + 66, posr.y, "Zoom In", Jungle24, ANC_CW);

    posr.x = pos.x + 25;
    posr.h = 31;
    posr.w = 2;
    posr.y -= 31;
    SDL_RenderFillRect(renderer, &posr);

    // Bottom

    render_frame(middle, 520, 360, 240, NULL, ANC_NC);

    pos.x = middle - 140;
    pos.y = 520 + 120 - 25;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(pos.x + 25, pos.y + 25, "F1", Jungle28, ANC_CC);

    posr.x = middle - 140 + 54;
    posr.y = 520 + 120 - 1;
    posr.h = 2;
    posr.w = 75;
    SDL_RenderFillRect(renderer, &posr);
    render_text(posr.x + 79, posr.y, "Quit to Menu", Jungle24, ANC_CW);

    pos.y += HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(pos.x + 25, pos.y + 25, "F4", Jungle28, ANC_CC);

    posr.y += HELP_PADSTEP;
    SDL_RenderFillRect(renderer, &posr);
    render_text(posr.x + 79, posr.y, "Quit application", Jungle24, ANC_CW);

    pos.y -= 2 * HELP_PADSTEP;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_MOVEOFF], &pos);
    render_text(pos.x + 25, pos.y + 25, "p", Jungle28, ANC_CC);

    posr.y -= 2 * HELP_PADSTEP;
    SDL_RenderFillRect(renderer, &posr);
    render_text(posr.x + 79, posr.y, "Pause game", Jungle24, ANC_CW);

    render_button(BT_HELPBACK);
}




void mouse_helpmenu(int x, int y) {
    mouse_capture_button(x, y, BT_HELPBACK);
}


void keyboard_helpmenu(SDL_KeyCode key) {
    switch (key)
    {
    case SDLK_ESCAPE:
        var_push_button(BT_HELPBACK);
        set_flag(PUSHED);
        break;
    default:
        break;
    }

}


/*******************/
/*+ Render scores +*/
/*******************/








void render_scores(bool final) {
    // Displays a gray layer over the game.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
    SDL_RenderFillRect(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));

    int middle = var_screen_width / 2;

    if (final) {
        render_frame(middle, SCORE_TI_TOP, 540, 80, NULL, ANC_CC);
        sprintf(menus_buffer, "Final scores for the %d rounds", gen_nbgames);
        render_text(middle, SCORE_TI_TOP, menus_buffer, Jungle36, ANC_CC);
        strcpy(var_buttons[BT_QUITSCORE].label, "Quit to menu");
        strcpy(var_buttons[BT_LENGTH].label, "Total length");



    }
    else {
        render_frame(middle, SCORE_TI_TOP, 440, 80, NULL, ANC_CC);
        sprintf(menus_buffer, "Round %d/%d: summary", var_nb_game + 1, gen_nbgames);
        render_text(middle, SCORE_TI_TOP, menus_buffer, Jungle36, ANC_CC);
        strcpy(var_buttons[BT_QUITSCORE].label, "Continue");
        strcpy(var_buttons[BT_LENGTH].label, "Length");
    }



    if (!var_scores) {
        render_frame(middle, SCORE_WI_TOP, 800, 80, NULL, ANC_NC);
        render_text(middle, SCORE_WI_TOP + 50, "Scores are not implemented", Jungle28, ANC_NC);
        render_button(BT_QUITSCORENULL);
        return;
    }
    else {
        render_button(BT_QUITSCORE);
    }










    int r;
    if (final) {
        r = var_scores->nb_games;
    }
    else {
        r = var_scores->cu_game;
    }

    int w_height = var_screen_height - SCORE_WI_TOP - SCORE_BOT_SPACE;
    render_frame(middle, SCORE_WI_TOP, 1260, w_height, NULL, ANC_NC);

    render_button(BT_SCORE);
    render_button(BT_STUDENTS);
    render_button(BT_LENGTH);
    render_button(BT_DISTANCE);
    render_button(BT_TIME);
    render_button(BT_PREVSCORE);
    render_button(BT_NEXTSCORE);


    int top = SCORE_NB_TOP;



    for (int i = var_score_page * var_scores_per_page; i < MIN(var_scores->nb_snakes, (var_score_page + 1) * var_scores_per_page); i++) {

        sprintf(menus_buffer, "*%d*", i + 1);
        render_text(middle - 2 * SCORE_BT_SEP - 3 * (SCORE_BT_SEP / 4) - 20, top, menus_buffer, Jungle20, ANC_CW);

        if (var_scores->score_to_game[i] == gen_iasnakes) {
            render_text(middle - 2 * SCORE_BT_SEP - (SCORE_BT_SEP / 2), top, "Player 1", Jungle20, ANC_CC);
        }
        else if (var_scores->score_to_game[i] == gen_iasnakes + 1) {
            render_text(middle - 2 * SCORE_BT_SEP - (SCORE_BT_SEP / 2), top, "Player 2", Jungle20, ANC_CC);
        }
        else {
            sprintf(menus_buffer, "IA %d", var_scores->score_to_game[i] + 1);
            render_text(middle - 2 * SCORE_BT_SEP - (SCORE_BT_SEP / 2), top, menus_buffer, Jungle20, ANC_CC);
        }


        for (int j = 0; j < SC_SIZE - 1; j++) {
            sprintf(menus_buffer, "%d", var_scores->scores[i][r]->vals[j]);
            render_text(middle - (1 - j) * SCORE_BT_SEP - SCORE_BT_SEP / 2, top, menus_buffer, Jungle20, ANC_CC);
        }
        sprintf(menus_buffer, "%ds", var_scores->scores[i][r]->vals[SC_SIZE - 1]);
        render_text(middle - (2 - SC_SIZE) * SCORE_BT_SEP - SCORE_BT_SEP / 2, top, menus_buffer, Jungle20, ANC_CC);
        top += SCORE_NB_STEP;

    }
}

void mouse_scores(int x, int y) {

    if (!var_scores) {
        mouse_capture_button(x, y, BT_QUITSCORENULL);
        return;
    }
    for (int i = BT_SCORE; i <= BT_QUITSCORE; i++) {
        mouse_capture_button(x, y, i);
    }
}

void keyboard_scores(SDL_KeyCode key) {
    switch (key)
    {
    case SDLK_UP:
        var_selected_button = var_buttons[var_selected_button].up;
        break;
    case SDLK_DOWN:
        var_selected_button = var_buttons[var_selected_button].down;
        break;
    case SDLK_LEFT:
        var_selected_button = var_buttons[var_selected_button].left;
        break;
    case SDLK_RIGHT:
        var_selected_button = var_buttons[var_selected_button].right;
        break;
    case SDLK_RETURN:
        var_push_button(var_selected_button);
        set_flag(PUSHED);
    default:
        break;
    }
}




/************************/
/*+ Affichage de texte **/
/************************/



// Affichage de texte
int render_text(int x, int y, const char* text, TTF_Font* font, anchor anc) {
    SDL_Surface* surf_text = TTF_RenderUTF8_Blended(font, text, WHITE);
    SDL_Texture* text_text = SDL_CreateTextureFromSurface(renderer, surf_text);
    SDL_Rect pos;
    shift_to_anchor(&x, &y, surf_text->w, surf_text->h, anc);
    pos.x = x;
    pos.y = y;
    pos.h = surf_text->h;
    pos.w = surf_text->w;
    SDL_RenderCopy(renderer, text_text, NULL, &pos);
    SDL_FreeSurface(surf_text);
    SDL_DestroyTexture(text_text);
    return pos.w;
}


void print_text_buffer_center(void) {
    if (SDL_GetTicks() % 800 <= 400) {
        sprintf(menus_buffer, "%s_", var_editbuffer->content);
    }
    else {
        sprintf(menus_buffer, "%s  ", var_editbuffer->content);
    }
}



/***************************/
/*+ Affichages des cadres **/
/***************************/





void render_selector(button lb, button rb, const char* string) {


    SDL_Rect pos;
    pos.h = 48;
    pos.w = 48;
    pos.x = var_buttons[lb].x;
    pos.y = var_buttons[lb].y;


    int width = var_buttons[rb].x + 46 - var_buttons[lb].x;
    int iwidth = width - 4 * 46;

    pos.w = 2 * 46;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITWB], &pos);
    pos.x += 2 * 46;

    if (iwidth > 0) {
        pos.w = iwidth;
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITC], &pos);
        pos.x += iwidth;
        pos.w = 2 * 46;
    }
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITEB], &pos);


    pos.h = 28;
    pos.w = 28;
    pos.x = var_buttons[lb].x;

    pos.x += 10;
    pos.y += 10;

    if (var_buttons_flags[lb]) {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_PUSHON], &pos);
    }
    else {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_PUSHOFF], &pos);
    }
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_LEFTD], &pos);

    pos.x = var_buttons[rb].x + 46 - 38;
    if (var_buttons_flags[rb]) {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_PUSHON], &pos);
    }
    else {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_PUSHOFF], &pos);
    }
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_RIGHTD], &pos);

    render_text(var_buttons[lb].x + width / 2, var_buttons[lb].y + 24, string, var_buttons[lb].font, ANC_CC);

}

void render_selector_edit(button bt, const char* string) {

    SDL_Rect pos;
    pos.h = 48;
    pos.w = 48;
    pos.x = var_buttons[bt].t_x;
    pos.y = var_buttons[bt].t_y;

    int width = var_buttons[bt].x + 46 - var_buttons[bt].t_x;
    int iwidth = width - 4 * 46;

    pos.x += 44;



    pos.w = 48;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITW], &pos);
    pos.x += 48;
    pos.w = iwidth;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITC], &pos);
    pos.x += pos.w;
    pos.w = 2 * 46;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITEB], &pos);


    pos.h = 28;
    pos.w = 28;

    pos.y += 10;

    pos.x = var_buttons[bt].x + 46 - 38;
    if (var_buttons_flags[bt]) {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_PUSHON], &pos);
    }
    else {
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_PUSHOFF], &pos);
    }
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_EDIT], &pos);



    render_text(var_buttons[bt].t_x + width / 2, var_buttons[bt].y + 24, string, var_buttons[bt].font, ANC_CC);
}







static void render_boxed_title(int x, int y, const char* title) {
    SDL_Surface* surf_text = TTF_RenderUTF8_Blended(Paci20, title, WHITE);
    SDL_Texture* text_text = SDL_CreateTextureFromSurface(renderer, surf_text);
    SDL_Rect pos;


    int tw = surf_text->w + 2 * 24;
    pos.x = x + 24;
    pos.y = y - 2;
    pos.h = surf_text->h;
    pos.w = surf_text->w;
    SDL_RenderCopy(renderer, text_text, NULL, &pos);
    SDL_FreeSurface(surf_text);
    SDL_DestroyTexture(text_text);


    pos.h = 48;
    pos.w = 48;
    pos.x = x;
    pos.y = y;

    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITW], &pos);
    pos.x += 48;

    if (tw > 2 * 48) {
        pos.w = tw - 2 * 48;
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITC], &pos);
        pos.x += pos.w;
    }
    pos.w = 48;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TTITE], &pos);

    render_text(x + 24, y + 2, title, Paci20, ANC_NW);
}

void render_frame(int x, int y, int w, int h, const char* title, anchor anc) {
    h = MAX(h, 128);
    w = MAX(w, 128);

    shift_to_anchor(&x, &y, w, h, anc);

    SDL_Rect pos;
    pos.h = 64;
    pos.w = 64;
    pos.x = x;
    pos.y = y;
    // Le cadre principal
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXNW], &pos);
    pos.x += pos.w;

    if (w > 128) {
        pos.w = w - 128;
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXN], &pos);
        pos.x += pos.w;
    }
    pos.w = 64;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXNE], &pos);

    pos.x = x;
    pos.y += pos.h;
    if (h > 128) {
        pos.h = h - 128;
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXW], &pos);
        pos.x += pos.w;
        if (w > 128) {
            pos.w = w - 128;
            SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXC], &pos);
            pos.x += pos.w;
        }
        pos.w = 64;
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXE], &pos);
        pos.y += pos.h;
    }

    pos.x = x;
    pos.h = 64;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXSW], &pos);
    pos.x += pos.w;

    if (w > 128) {
        pos.w = w - 128;
        SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXS], &pos);
        pos.x += pos.w;
    }
    pos.w = 64;
    SDL_RenderCopy(renderer, txt_frames, &clp_textures[CLP_TBOXSE], &pos);


    // Le titre

    y -= 20;
    x += 20;

    if (title) {

        render_boxed_title(x, y, title);
    }

}




