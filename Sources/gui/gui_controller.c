#include "gui_controller.h"







/**************************************/
/*+ Intialisation/Suppression du jeu **/
/**************************************/

void ctl_init_demo(void) {
  // Kills an eventual previous game.
  ctl_kill_game();

  // Initialization of the zoom level for the demo.
  init_zoom_demo();

  // The demo game is played on a single screen
  init_single_screen();

  // No mask is used for the demo.
  mask* themask = NULL;

  // Creation of the demo game.
  int h = (var_screen_height / (2 * var_tile_size[0])) - 2;
  int w = (var_screen_width / (2 * var_tile_size[0])) - 4;
  var_game = new_game(w, h, themask, 0, 1, SLOW, 1);

  // Checking the validity of the created game.
  if (!check_game(var_game)) {
    fprintf(stderr, "Error in the creation of the demo game.\n");
    delete_game(var_game);
    var_game = NULL;
    return;
  }

  // Creation of the displayed grid.
  var_grid_display = create_grid(var_game->b);

  // Centering the grid on the screen.
  scroll_to_center(var_game->b, 0);

  // Setup of the explosions array.
  init_explosions_state(3);
}

void ctl_init_game(void) {

  // Killing all eventual previous games.
  ctl_kill_game();

  // Initialization of the zoom level for the game.
  init_zoom_game();

  // Changing the mode to game.
  var_mode = MODE_GAME;

  // Loading the mask.
  mask* themask = NULL;
  if (gen_use_mask) {
    char thepath[10 + strlen(gen_maskname)];
    sprintf(thepath, "../Masques/%s", gen_maskname);
    themask = read_mask(thepath);

#ifdef DEBUGMASK
    print_mask(themask);
#endif
  }

  // Defaulting the strategies of the computer controlled snakes if no strategies are loaded.
  if (!var_strats) {
    MALLOC(var_strats, gen_iasnakes);
    for (int i = 0; i < gen_iasnakes; i++) {
      var_strats[i] = gen_strat;
    }
  }


  // Creation of the game.
  var_game = new_game(gen_hsize, gen_vsize, themask, gen_players, gen_iasnakes, gen_speed, gen_maxlength);
  if (!check_game(var_game)) {
    fprintf(stderr, "Error in the creation of the game.\n");
    exit(EXIT_FAILURE);
  }


  // Initialization of the displayed grid.
  var_grid_display = create_grid(var_game->b);

  // Initialization of the screen mode.
  if (gen_players == 2) {
    init_dual_screen();
  }
  else {
    init_single_screen();
  }

  if (gen_players == 0) {
    scroll_to_center(var_game->b, 0);
  }


  // Initialization of the player tracking.
  if (gen_players >= 1) {
    init_player_tracking(var_game->snakes_array[var_game->nb_ais]->head % var_game->b->hsize, var_game->snakes_array[var_game->nb_ais]->head / var_game->b->hsize, 0);
  }
  else {
    disable_player_tracking(0);
  }


  if (gen_players == 2) {
    init_player_tracking(var_game->snakes_array[var_game->nb_ais + 1]->head % var_game->b->hsize, var_game->snakes_array[var_game->nb_ais + 1]->head / var_game->b->hsize, 1);
  }
  else {
    disable_player_tracking(1);
  }


  // Initialization of the explosions array.
  init_explosions_state(gen_players + gen_iasnakes);

  // Initialization of the time counter.
  init_time_counter();
}


void ctl_kill_game(void) {
  if (var_game) {
    delete_game(var_game);
    var_game = NULL;
  }
  if (var_grid_display) {
    delete_grid(var_grid_display);
    var_grid_display = NULL;
  }
  if (var_explosions_state)
  {
    free(var_explosions_state);
    var_explosions_state = NULL;
  }
}

void ctl_init_scores(void) {
  // Killing an eventual previous score table.
  ctl_kill_scores();

  // Creation of the score table.
  var_scores = new_score_table(gen_nbgames, gen_iasnakes + gen_players);

  if (!check_score(var_scores)) {
    fprintf(stderr, "Error in the creation of the score table.\n");
  }
}

void ctl_kill_scores(void) {
  if (var_scores) {
    delete_score_table(var_scores);
    var_scores = NULL;
  }
}


/*******************/
/*+ Menus control +*/
/*******************/

void ctl_enter_menu(void) {
  if (var_mode == MODE_MENU) {
    return;
  }

  var_mode = MODE_MENU;
  var_menu = MENU_MAIN;
  var_selected_button = BT_QGAME;
  var_reset_buttons();
  // Kills an eventual previous game.
  ctl_kill_game();
  // Kills an eventual previous score table.
  ctl_kill_scores();
  ctl_init_demo();
}


void ctl_enter_scores(void) {
  var_mode = MODE_SCORES;

  if (var_scores) {
    var_score_page = 0;
    var_scores_per_page = (var_screen_height - SCORE_BOT_SPACE - SCORE_NB_TOP - 80) / SCORE_NB_STEP;
    var_score_max_page = (var_scores->nb_snakes / var_scores_per_page) - 1;
    if (var_scores->nb_snakes % var_scores_per_page) {
      var_score_max_page++;
    }
    sort_scores(var_scores, var_scores->cu_game, SC_MAIN);
    var_selected_button = BT_SCORE;
  }
  else {
    var_selected_button = BT_QUITSCORENULL;
  }
  var_reset_buttons();
}

void ctl_exit_scores(void) {
  var_nb_game++;
  if (var_nb_game < gen_nbgames) {
    var_reset_buttons();
    ctl_init_game();
    if (var_scores) {
      move_to_next_game(var_scores);
    }
  }
  else {
    var_mode = MODE_FINAL;

    if (var_scores) {
      compute_final_scores(var_scores);
      sort_scores(var_scores, var_scores->nb_games, SC_MAIN);
      var_selected_button = BT_SCORE;
    }
    else {
      var_selected_button = BT_QUITSCORENULL;
    }
    var_reset_buttons();

  }
}


void ctl_update_game(void) {
  if (!var_game) {
    return;
  }

  // Object generation.
  if (var_mode == MODE_MENU) {
    generator_funs[OGEN_SAPPLE](var_game);
  }
  else {
    generator_funs[var_objgen](var_game);
  }




  // Choosing the strategies to apply (depends on whether this is the demo or a real game)
  strat* strat_array;
  if (var_mode == MODE_MENU) {
    strat_array = var_demo_strats;
  }
  else {
    strat_array = var_strats;
  }



  // Applying strategies to the AIs
  for (int i = 0; i < var_game->nb_ais; i++) {
    if (var_game->snakes_array[i]->progress + speed_to_value(var_game->snakes_array[i]->speed) == LENGTH_CELL) {
      strat_funs[strat_array[i]](var_game, i);
    }
  }

  int p1pr = 0;
  int p2pr = 0;
  if (var_game->nb_players > 0) {
    p1pr = var_game->snakes_array[var_game->nb_ais]->progress;
  }
  if (var_game->nb_players > 1) {
    p2pr = var_game->snakes_array[var_game->nb_ais + 1]->progress;
  }


  // Implementing the turn for all snakes
  implement_turn_all_snakes(var_game, var_scores);


  // Updating the player tracking for the scrolling
  update_player_tracking(var_game, 0, p1pr);
  update_player_tracking(var_game, 1, p2pr);


  // Setting up the explosions for the dead players.
  for (int i = 0; i < var_game->nb_ais + var_game->nb_players; i++) {
    if (var_explosions_state[i] == -1 && !var_game->snakes_array[i]->alive) {
      var_explosions_state[i] = 0;
    }
  }
}

/***********************/
/*+ Display functions +*/
/***********************/



void ctl_display_screen(unsigned char i) {

  // If there is no game or no grid display, we do nothing.
  if (!var_game || !var_grid_display) {
    return;
  }

  // We check the validity of the screen number (the program exits if the screen number is invalid).
  check_valid_screen(i);

  // We set the viewport to the screen.
  SDL_RenderSetViewport(renderer, &var_screen[i]);

  // We display the board.
  display_grid(var_grid_display, i);

  // We display the objects.
  render_objects(var_game->b, i);

  // We display the snakes.
  for (int k = 0; k < var_game->nb_ais + var_game->nb_players; k++) {
    render_snake(var_game, k, (var_game->snakes_array[k]->progress * 16) / LENGTH_CELL, i);
  }

  // We display the explosions.
  display_explosions(i);

#ifdef DEBUGEMPTYLIST
  // We display the empty cells (for debugging only)
  render_empty_cells(var_game->b, i);
#endif

#ifdef DEBUGEMPTYINDICES
  // We display the empty cells (for debugging only)
  render_empty_cells_indices(var_game->b, i);
#endif

#ifdef DEBUGSNAKES
  // We display the snake cells (for debugging only)
  render_snake_cells(var_game->b, i);
#endif

  // We restore the viewport to the full screen.
  SDL_RenderSetViewport(renderer, NULL);
}


void ctl_display_menu(void) {

  // Dislpays the background demo game.
  ctl_display_screen(0);

  // Displays a gray layer over the demo game.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
  SDL_RenderFillRect(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));

  // Displays the menu.
  render_menu();

}

void ctl_display_game(void) {

  // Displaying the screen(s)

  // Left screen (or full screen if there is no dual screen)
  ctl_display_screen(0);

  // Right screen (if required)
  if (var_dual_screen) {
    ctl_display_screen(1);
    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(BLACK));
    SDL_RenderDrawLine(renderer, var_screen_width / 2, 0, var_screen_width / 2, var_screen_height);
    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));
  }

  // Player 1 score
  if (var_game && var_game->nb_players > 0) {
    SDL_RenderSetViewport(renderer, &var_screen[var_player_screen[0]]);
    render_ingame_score(var_game, 0);
  }

  //Player 2 score
  if (var_game && var_game->nb_players > 1) {
    SDL_RenderSetViewport(renderer, &var_screen[var_player_screen[1]]);
    render_ingame_score(var_game, 1);
  }
  SDL_RenderSetViewport(renderer, NULL);
}

void ctl_display_pause(void) {
  // Displays a gray layer over the game.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
  SDL_RenderFillRect(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));

  render_frame(var_screen_width / 2, var_screen_height / 2, 400, 100, NULL, ANC_CC);
  render_text(var_screen_width / 2, var_screen_height / 2, "Pause (press p to continue)", Jungle24, ANC_CC);
}


void display_explosions(int p) {
  for (int i = 0; i < var_game->nb_ais + var_game->nb_players; i++) {
    if (var_explosions_state[i] <= -1 || var_explosions_state[i] >= 84) {
      continue;
    }
    render_snake_explosion(i, var_explosions_state[i], p);
  }
}

/*******************/
/*+ Button pushes +*/
/*******************/


void ctl_button_push(void) {
  switch (var_mode)
  {
  case MODE_MENU:
    ctl_button_push_menu();
    break;
  case MODE_SCORES:
    pushbutton_scores();
    break;
  case MODE_FINAL:
    pushbutton_final();
    break;
  default:
    break;
  }
  var_pushed_button = BT_NONE;
}


void ctl_button_push_menu(void) {
  switch (var_menu)
  {
  case MENU_MAIN:
    ctl_button_push_mainmenu();
    break;
  case MENU_SETUP:
    ctl_button_push_setupmenu();
    break;
  case MENU_HELP:
    if (var_pushed_button == BT_HELPBACK) {
      change_menu(MENU_MAIN);
    }
    break;
  default:
    break;
  }
}

void ctl_button_push_mainmenu(void) {
  switch (var_pushed_button)
  {
  case BT_SETUP:
    change_menu(MENU_SETUP);
    break;
  case BT_HELP:
    change_menu(MENU_HELP);
    break;
  case BT_QGAME:
    ctl_init_scores();
    var_nb_game = 0;
    ctl_init_game();
    break;
  case BT_QUIT:
    set_flag(QUIT);
    break;
  default:
    break;
  }
}


static void update_mask_from_file(void) {

  if (var_maskindex == -1) {
    gen_use_mask = false;
    sprintf(gen_maskname, "Pas de masque");
  }
  else {
    gen_use_mask = true;
    sprintf(gen_maskname, "%s", var_maskstab[var_maskindex]->d_name);
  }
}

void ctl_button_push_setupmenu(void) {
  switch (var_pushed_button)
  {
  case BT_LAUNCH:
    ctl_init_scores();
    var_nb_game = 0;
    ctl_init_game();
    break;
  case BT_PBACK:
    change_menu(MENU_MAIN);
    break;
  case BT_NBPLAYERSL:
    gen_players = (gen_players + 2) % 3;
    break;
  case BT_NBPLAYERSR:
    gen_players = (gen_players + 1) % 3;
    break;
  case BT_INISPEEDL:
    gen_speed = (gen_speed + SPEED_SIZE - 1) % SPEED_SIZE;
    break;
  case BT_INISPEEDR:
    gen_speed = (gen_speed + 1) % SPEED_SIZE;
    break;
  case BT_GENEL:
    var_objgen = (var_objgen + OGEN_SIZE - 1) % OGEN_SIZE;
    break;
  case BT_GENER:
    var_objgen = (var_objgen + 1) % OGEN_SIZE;
    break;
  case BT_NBIAS:
    init_text_buffer(ED_IAS);
    break;
  case BT_NBGAMES:
    init_text_buffer(ED_GAMES);
    break;
  case BT_INILENGTH:
    init_text_buffer(ED_LENGTH);
    break;
  case BT_HSIZE:
    init_text_buffer(ED_X);
    break;
  case BT_VSIZE:
    init_text_buffer(ED_Y);
  case BT_IASTRATL:
    var_strat_assign = (var_strat_assign + STRAT_SIZE - 1) % STRAT_SIZE;
    break;
  case BT_IASTRATR:
    var_strat_assign = (var_strat_assign + 1) % STRAT_SIZE;
    break;
  case BT_IAGLOBAL:
    for (int i = 0; i < gen_iasnakes; i++) {
      var_strats[i] = var_strat_assign;
    }
    break;
  case BT_IASINGLE:
    var_strats[var_ia_select] = var_strat_assign;
    break;
  case BT_IASELEC:
    init_text_buffer(ED_SINGLEIA);
    break;
  case BT_MASKL:
    if (var_maskindex >= 0) {
      var_maskindex--;
    }
    else {
      var_maskindex = var_masktabsize - 1;
    }
    update_mask_from_file();
    break;
  case BT_MASKR:
    if (var_maskindex < var_masktabsize - 1) {
      var_maskindex++;
    }
    else {
      var_maskindex = -1;
    }
    update_mask_from_file();
    break;
  default:
    break;
  }
}


void pushbutton_scores(void) {
  if (!var_scores) {
    if (var_pushed_button == BT_QUITSCORENULL) {
      set_flag(NEXTGAME);
    }
    return;
  }



  switch (var_pushed_button)
  {
  case BT_SCORE:
    sort_scores(var_scores, var_scores->cu_game, SC_MAIN);
    break;
  case BT_STUDENTS:
    sort_scores(var_scores, var_scores->cu_game, SC_STUDENTS);
    break;
  case BT_LENGTH:
    sort_scores(var_scores, var_scores->cu_game, SC_LENGTH);
    break;
  case BT_DISTANCE:
    sort_scores(var_scores, var_scores->cu_game, SC_VISITED);
    break;
  case BT_TIME:
    sort_scores(var_scores, var_scores->cu_game, SC_TIME);
    break;
  case BT_NEXTSCORE:
    if (var_score_page < var_score_max_page) {
      var_score_page++;
    }
    break;
  case BT_PREVSCORE:
    if (var_score_page > 0) {
      var_score_page--;
    }
    break;
  case BT_QUITSCORE:
    set_flag(NEXTGAME);
    break;
  default:
    break;
  }

}


void pushbutton_final(void) {
  if (!var_scores) {
    if (var_pushed_button == BT_QUITSCORENULL) {
      set_flag(GOMENU);
    }
    return;
  }



  switch (var_pushed_button)
  {
  case BT_SCORE:
    sort_scores(var_scores, var_scores->nb_games, SC_MAIN);
    break;
  case BT_STUDENTS:
    sort_scores(var_scores, var_scores->cu_game, SC_STUDENTS);
    break;
  case BT_LENGTH:
    sort_scores(var_scores, var_scores->nb_games, SC_LENGTH);
    break;
  case BT_DISTANCE:
    sort_scores(var_scores, var_scores->nb_games, SC_VISITED);
    break;
  case BT_TIME:
    sort_scores(var_scores, var_scores->nb_games, SC_TIME);
    break;
  case BT_NEXTSCORE:
    if (var_score_page < var_score_max_page) {
      var_score_page++;
    }
    break;
  case BT_PREVSCORE:
    if (var_score_page > 0) {
      var_score_page--;
    }
    break;
  case BT_QUITSCORE:
    set_flag(GOMENU);
    break;
  default:
    break;
  }

}





/*********************************/
/*+ Prise en compte des actions **/
/*********************************/








void ctl_mouse_motion(SDL_Event* theevent) {
  if (flags[MOUSEDOWN] && var_mode == MODE_GAME) {
    scroll_with_mouse(theevent->motion.x, theevent->motion.y);
  }
  var_mousePosx = theevent->motion.x;
  var_mousePosy = theevent->motion.y;
}

void ctl_mouse_click(SDL_Event* theevent) {
  if (!flags[MOUSEDOWN] && theevent->button.button == SDL_BUTTON_LEFT)
  {
    set_flag(MOUSEDOWN);
  }
  switch (var_mode) {
  case MODE_MENU:
    mouse_menu(theevent->button.x, theevent->button.y);
    break;
  case MODE_SCORES:
  case MODE_FINAL:
    mouse_scores(theevent->button.x, theevent->button.y);
    break;
  default:
    break;
  }
}



void ctl_mouse_unclick(SDL_Event* theevent) {
  if (flags[MOUSEDOWN] && theevent->button.button == SDL_BUTTON_LEFT)
  {
    remove_flag(MOUSEDOWN);
  }
}

static void keyboard_game(SDL_KeyCode thecode) {

  void (*d1) (game*, direction);
  void (*d2) (game*, direction);

  if (gen_players > 1) {
    d1 = set_direction_player1;
    d2 = set_direction_player2;
  }
  else {
    d1 = set_direction_player1;
    d2 = set_direction_player1;
  }

  switch (thecode)
  {
  case SDLK_KP_PLUS:
  case SDLK_EQUALS:
  case SDLK_PLUS:
  case SDLK_2:
    increase_zoom(0);
    break;
  case SDLK_9:
    increase_zoom(1);
    break;
  case SDLK_KP_MINUS:
  case SDLK_6:
  case SDLK_MINUS:
  case SDLK_1:
    decrease_zoom(0);
    break;
  case SDLK_8:
    decrease_zoom(1);
    break;
  case SDLK_d:
    d1(var_game, RIGHT);
    break;
  case SDLK_q:
  case SDLK_a:
    d1(var_game, LEFT);
    break;
  case SDLK_s:
    d1(var_game, DOWN);
    break;
  case SDLK_z:
  case SDLK_w:
    d1(var_game, UP);
    break;
  case SDLK_RIGHT:
    d2(var_game, RIGHT);
    break;
  case SDLK_LEFT:
    d2(var_game, LEFT);
    break;
  case SDLK_DOWN:
    d2(var_game, DOWN);
    break;
  case SDLK_UP:
    d2(var_game, UP);
    break;
  case SDLK_p:
    if (flags[PAUSE]) {
      resume_time_counter();
    }
    else {
      pause_time_counter();

    }
    flip_flag(PAUSE);
    break;
  default:
    break;
  }
}

void ctl_input(SDL_Event* theevent) {

  switch (theevent->key.keysym.sym)
  {
  case SDLK_F1:
    set_flag(GOMENU);
    break;
  case SDLK_F4:
    set_flag(QUIT);
    break;
  default:
    break;
  }

  switch (var_mode) {
  case MODE_MENU:
  case MODE_SCORES:
  case MODE_FINAL:
    keyboard_menu(theevent->key.keysym.sym);
    break;
  case MODE_GAME:
    keyboard_game(theevent->key.keysym.sym);
    break;
  default:
    break;
  }
}




/*******************/
/*+ Boucle de jeu **/
/*******************/

void event_loop(void) {


  // The loop always starts in menu mode.
  ctl_enter_menu();

  // We reset all buttons and flags.
  var_reset_buttons();
  reset_flags();

  // Déclaration de l'événement
  SDL_Event event;

  // Main game loop
  while (!flags[QUIT]) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        set_flag(QUIT);
        break;
      }

      // Locks the keyboard until a key is released.
      if ((flags[KEYDOWN] && event.type != SDL_KEYUP)) {
        continue;
      }
      if (flags[KEYDOWN] && event.type == SDL_KEYUP) {
        flags[KEYDOWN] = false;
      }

      // Text input mode
      if (var_mode == MODE_MENU && var_menu == MENU_SETUP && var_edit_mode != ED_NONE) {
        switch (event.type) {
        case SDL_TEXTINPUT:
          append_to_text_buffer(var_editbuffer, event.text.text);
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
          case SDLK_BACKSPACE:
            if (var_editbuffer->length > 0)
              remove_char(var_editbuffer);
            break;
          case SDLK_RETURN:
          case SDLK_KP_ENTER:
            update_from_text_buffer();
            free_text_buffer(var_editbuffer);
            var_editbuffer = NULL;
            var_edit_mode = ED_NONE;
            break;
          default:
            break;
          }
        default:
          break;
        }
        continue;
      }

      // Mouse handling
      switch (event.type)
      {
      case SDL_MOUSEMOTION:
        ctl_mouse_motion(&event);
        break;
      case SDL_MOUSEBUTTONDOWN:
        ctl_mouse_click(&event);
        break;
      case SDL_MOUSEBUTTONUP:
        ctl_mouse_unclick(&event);
        break;

      default:
        break;
      }

      // Keyboard handling
      if (event.type == SDL_KEYDOWN) {
        set_flag(KEYDOWN);
        ctl_input(&event);
      }

    }

    // Reset of the buttons and handling of pushes (if necessary)
    if (flags[PUSHED] && SDL_GetTicks() - var_button_countdown >= 100) {
      var_reset_buttons();
      remove_flag(PUSHED);
      ctl_button_push();
    }

    // Handling flags
    if (flags[GOMENU]) {
      ctl_enter_menu();
      remove_flag(GOMENU);
    }

    if (flags[NEXTGAME]) {
      ctl_exit_scores();
      remove_flag(NEXTGAME);
    }


    // Handling the case when the game is over.
    if (var_game && var_game->nb_alive == 0 && explosions_over()) {
      switch (var_mode)
      {
      case MODE_MENU:
        ctl_init_demo();
        break;
      case MODE_GAME:
        check_game(var_game);
        ctl_enter_scores();
        break;

      default:
        break;
      }


    }



    // Update of the game.
    if (var_game && (var_mode == MODE_GAME || var_mode == MODE_MENU) && !flags[PAUSE]) {
      ctl_update_game();
      for (int i = 0; i < var_game->nb_ais + var_game->nb_players; i++) {
        if (var_explosions_state[i] >= 0) {
          var_explosions_state[i]++;
        }
      }
    }


    // Displaying the game
    SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));
    SDL_RenderClear(renderer);




    switch (var_mode)
    {
    case MODE_MENU:
      ctl_display_menu();
      break;
    case MODE_GAME:
      ctl_display_game();
#ifndef HIDEPAUSE
      if (flags[PAUSE]) {
        ctl_display_pause();
      }
#endif
      break;
    case MODE_SCORES:
      ctl_display_game();
      render_scores(false);
      break;
    case MODE_FINAL:
      ctl_display_game();
      render_scores(true);
      break;
    default:
      break;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(5); //5
  }
}





