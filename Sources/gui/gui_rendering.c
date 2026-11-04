#include "gui_rendering.h"

SDL_Texture* txt_anims;





/*****************************/
/*+ Fonctions préliminaires **/
/*****************************/

void render_get_cellpos(int i, int j, int p, SDL_Rect* pos) {
  pos->x = (i - var_startx[p]) * 2 * var_tile_size[p] + var_topleftx[p] + var_tile_size[p] / 2;
  pos->y = (j - var_starty[p]) * 2 * var_tile_size[p] + var_toplefty[p] + var_tile_size[p] / 2;
}

void render_get_cellpos_tile(int i, int j, int p, SDL_Rect* pos) {
  pos->x = (i - var_startx[p]) * 2 * var_tile_size[p] + var_topleftx[p] + var_tile_size[p];
  pos->y = (j - var_starty[p]) * 2 * var_tile_size[p] + var_toplefty[p] + var_tile_size[p];
}



bool render_outofview(int i, int j, int p) {
  if (i + 1 < var_startx[p] || j + 1 < var_starty[p] || i - 1 > var_endx[p] || j - 1 > var_endy[p]) {
    return true;
  }
  return false;
}


/************************/
/*+ Displaying objects **/
/************************/

void render_objects(board* b, int p) {

  SDL_Rect pos;
  pos.h = var_tile_size[p];
  pos.w = var_tile_size[p];

  SDL_Rect toon;
  toon.h = 2 * var_tile_size[p];
  toon.w = 2 * var_tile_size[p];

  pos.x = var_topleftx[p] + var_tile_size[p] + var_tile_size[p] / 2;
  pos.y = var_toplefty[p] + var_tile_size[p] + var_tile_size[p] / 2;




  for (int i = var_startx[p]; i < var_endx[p] && i < b->hsize; i++) {
    pos.y = var_toplefty[p] + var_tile_size[p] + var_tile_size[p] / 2;
    for (int j = var_starty[p]; j < var_endy[p] && j < b->vsize;j++) {

      switch (b->objects[i + j * b->hsize])
      {
      case APPLE:
        SDL_RenderCopy(renderer, txt_food, &clp_textures[CLP_APPLE], &pos);
        break;
      case CHERRY:
        SDL_RenderCopy(renderer, txt_food, &clp_textures[CLP_CHERRY], &pos);
        break;
      case BANANA:
        SDL_RenderCopy(renderer, txt_food, &clp_textures[CLP_BANANA], &pos);
        break;
      case GRAPES:
        SDL_RenderCopy(renderer, txt_food, &clp_textures[CLP_GRAPES], &pos);
        break;
      case PINEAPPLE:
        SDL_RenderCopy(renderer, txt_food, &clp_textures[CLP_PINEAPPLE], &pos);
        break;
      case STUDENT:
        toon.x = pos.x - var_tile_size[p] / 2;
        toon.y = pos.y - var_tile_size[p] + var_tile_size[p] / 4;
        SDL_RenderCopy(renderer, txt_student, &clp_textures[CLP_STUDENT], &toon);
        break;
      case CHILI:
        SDL_RenderCopy(renderer, txt_food, &clp_textures[CLP_CHILI], &pos);
        break;
      case MUSHROOM:
        SDL_RenderCopy(renderer, txt_food, &clp_textures[CLP_MUSHROOM], &pos);
        break;
      default:
        break;
      }



      pos.y += 2 * var_tile_size[p];
    }
    pos.x += 2 * var_tile_size[p];
  }
}




void render_empty_cells(board* b, int p) {

  SDL_Rect pos;
  pos.h = 2 * var_tile_size[p];
  pos.w = 2 * var_tile_size[p];

  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(ORANGE));

  for (int i = 0; i < b->empty_cells_count;i++) {

    int x = b->empty_cells_listing[i] % b->hsize;
    int y = b->empty_cells_listing[i] / b->hsize;
    if (render_outofview(x, y, p)) {
      continue;
    }
    render_get_cellpos_tile(x, y, p, &pos);

    SDL_RenderFillRect(renderer, &pos);


  }
  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));


}



void render_empty_cells_indices(board* b, int p) {

  SDL_Rect pos;
  pos.h = 2 * var_tile_size[p];
  pos.w = 2 * var_tile_size[p];

  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(BLUET));

  for (int i = 0; i < b->size;i++) {

    if (b->empty_cells_indices[i] == -1) {
      continue;
    }


    int x = i % b->hsize;
    int y = i / b->hsize;
    if (render_outofview(x, y, p)) {
      continue;
    }
    render_get_cellpos_tile(x, y, p, &pos);

    SDL_RenderFillRect(renderer, &pos);

  }


  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));


}


void render_snake_cells(board* b, int p) {

  SDL_Rect pos;
  pos.h = 2 * var_tile_size[p];
  pos.w = 2 * var_tile_size[p];

  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(PALE));

  for (int i = 0; i < b->size;i++) {

    if (b->objects[i] != SNAKE) {
      continue;
    }


    int x = i % b->hsize;
    int y = i / b->hsize;
    if (render_outofview(x, y, p)) {
      continue;
    }
    render_get_cellpos_tile(x, y, p, &pos);

    SDL_RenderFillRect(renderer, &pos);

  }


  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));


}



/*****************/
/* Display snake */
/*****************/







void render_snake_head(direction indir, direction outdir, bool large, int frame, int p, SDL_Rect* pos) {

  pos->h = 3 * var_tile_size[p];
  pos->w = 3 * var_tile_size[p];
  int st_index;
  int tu_index;
  if (large) {
    st_index = CLP_SHAL0;
    tu_index = CLP_SHATL0;
  }
  else {
    st_index = CLP_SHAS0;
    tu_index = CLP_SHATS0;
  }

  if (indir == LEFT) {
    switch (outdir)
    {
    case RIGHT:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[st_index + frame], pos);
      break;
    case UP:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[tu_index + frame], pos);
      break;
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 0, NULL, SDL_FLIP_VERTICAL);
      break;
    default:
      fprintf(stderr, "Error in snake directions left.\n");
      break;
    }
  }
  else if (indir == RIGHT) {
    switch (outdir)
    {
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, 0, NULL, SDL_FLIP_HORIZONTAL);
      break;
    case UP:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 0, NULL, SDL_FLIP_HORIZONTAL);
      break;
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 180, NULL, SDL_FLIP_NONE);
      break;
    default:
      fprintf(stderr, "Error in snake directions right.\n");
      break;
    }
  }
  else if (indir == UP) {
    switch (outdir)
    {
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, -90, NULL, SDL_FLIP_HORIZONTAL);
      break;
    default:
      fprintf(stderr, "Error in snake directions up.\n");
      break;
    }
  }
  else if (indir == DOWN) {
    switch (outdir)
    {
    case UP:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, -90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, -90, NULL, SDL_FLIP_VERTICAL);
      break;
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, -90, NULL, SDL_FLIP_VERTICAL);
      break;
    default:
      fprintf(stderr, "Error in snake directions down.\n");
      break;
    }
  }

}

void render_snake_tail(direction indir, direction outdir, bool large, int frame, int p, SDL_Rect* pos) {

  pos->h = 3 * var_tile_size[p];
  pos->w = 3 * var_tile_size[p];
  int st_index;
  int tu_index;
  if (large) {
    st_index = CLP_STAL0;
    tu_index = CLP_STATL0;
  }
  else {
    st_index = CLP_STAS0;
    tu_index = CLP_STATS0;
  }

  if (indir == LEFT) {
    switch (outdir)
    {
    case RIGHT:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[st_index + frame], pos);
      break;
    case UP:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, -90, NULL, SDL_FLIP_NONE);
      break;
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 90, NULL, SDL_FLIP_VERTICAL);
      break;
    default:
      fprintf(stderr, "Error in snake directions left.\n");
      break;
    }
  }
  else if (indir == RIGHT) {
    switch (outdir)
    {
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, 0, NULL, SDL_FLIP_HORIZONTAL);
      break;
    case UP:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, -90, NULL, SDL_FLIP_VERTICAL);
      break;
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    default:
      fprintf(stderr, "Error in snake directions right.\n");
      break;
    }
  }
  else if (indir == UP) {
    switch (outdir)
    {
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[tu_index + frame], pos);
      break;
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 0, NULL, SDL_FLIP_HORIZONTAL);
      break;
    default:
      fprintf(stderr, "Error in snake directions up.\n");
      break;
    }
  }
  else if (indir == DOWN) {
    switch (outdir)
    {
    case UP:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, -90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[tu_index + frame], pos, 0, NULL, SDL_FLIP_VERTICAL);
      break;
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[st_index + frame], pos, 180, NULL, SDL_FLIP_NONE);
      break;
    default:
      fprintf(stderr, "Error in snake directions down.\n");
      break;
    }
  }


}

void render_static_part(direction indir, direction outdir, bool tail, bool full, int p, SDL_Rect* pos) {
  pos->h = var_tile_size[p];
  pos->w = var_tile_size[p];
  int end;
  if (tail) {
    end = CLP_STAIL;
  }
  else {
    end = CLP_STUBE;
  }

  pos->y += var_tile_size[p];
  pos->x += var_tile_size[p];
  render_tile_snake(indir, outdir, p, pos);


  switch (indir)
  {
  case UP:
    pos->y -= var_tile_size[p];
    SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[end], pos, 90, NULL, SDL_FLIP_NONE);
    pos->y += var_tile_size[p];
    break;
  case RIGHT:
    pos->x += var_tile_size[p];
    SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[end], pos, 0, NULL, SDL_FLIP_HORIZONTAL);
    pos->x -= var_tile_size[p];
    break;
  case DOWN:
    pos->y += var_tile_size[p];
    SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[end], pos, -90, NULL, SDL_FLIP_NONE);
    pos->y -= var_tile_size[p];
    break;
  case LEFT:
    pos->x -= var_tile_size[p];
    SDL_RenderCopy(renderer, txt_anims, &clp_textures[end], pos);
    pos->x += var_tile_size[p];
    break;
  default:
    break;
  }
  if (full) {
    switch (outdir)
    {
    case UP:
      pos->y -= var_tile_size[p];
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STUBE], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      pos->x += var_tile_size[p];
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[CLP_STUBE], pos);
      break;
    case DOWN:
      pos->y += var_tile_size[p];
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STUBE], pos, -90, NULL, SDL_FLIP_NONE);
      break;
    case LEFT:
      pos->x -= var_tile_size[p];
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[CLP_STUBE], pos);
      break;
    default:
      break;
    }

  }

}



void render_tile_snake(direction indir, direction outdir, int p, SDL_Rect* pos) {
  pos->h = var_tile_size[p];
  pos->w = var_tile_size[p];
  if (indir == LEFT) {
    switch (outdir)
    {
    case RIGHT:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[CLP_STUBE], pos);
      break;
    case UP:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STURN], pos, -90, NULL, SDL_FLIP_NONE);
      break;
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STURN], pos, 180, NULL, SDL_FLIP_NONE);
    default:
      break;
    }
  }
  else if (indir == RIGHT) {
    switch (outdir)
    {
    case LEFT:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[CLP_STUBE], pos);
      break;
    case UP:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[CLP_STURN], pos);
      break;
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STURN], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    default:
      break;
    }
  }
  else if (indir == UP) {
    switch (outdir)
    {
    case DOWN:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STUBE], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[CLP_STURN], pos);
      break;
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STURN], pos, -90, NULL, SDL_FLIP_NONE);
      break;
    default:
      break;
    }
  }
  else if (indir == DOWN) {
    switch (outdir)
    {
    case UP:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STUBE], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STURN], pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case LEFT:
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_STURN], pos, 180, NULL, SDL_FLIP_NONE);
      break;
    default:
      break;
    }
  }

}



void render_snake(game* g, int k, int frame, int p) {
  if (k < 0 || k >= g->nb_ais + g->nb_players) {
    return;
  }
  snake* s = g->snakes_array[k];
  board* b = g->b;


  if (s->alive) {
    if (k == g->nb_ais) {
      txt_anims = txt_snakegreen;
    }
    else if (k == g->nb_ais + 1) {
      txt_anims = txt_snakeblue;
    }
    else {
      txt_anims = txt_snakered;
    }
  }
  else {
    txt_anims = txt_snakeblack;
    frame = 0;
  }


  //render_all_snake_tiles();
  // Rectangle for the drawing
  SDL_Rect pos;


  if (s->length < 1 || s->full_length < 1) {
    fprintf(stderr, "Error: snake length should be at least 1.\n");
    exit(EXIT_FAILURE);
  }

  // Special case for the snake of max length 1
  if (s->full_length == 1) {
    render_get_cellpos(s->tail % b->hsize, s->tail / b->hsize, p, &pos);
    if (!s->alive) {
      render_snake_tail(b->indirs[s->tail], b->outdirs[s->tail], false, 0, p, &pos);
      return;
    }
    render_snake_tail(b->indirs[s->tail], b->outdirs[s->tail], false, frame, p, &pos);
    render_get_cellpos(s->head % b->hsize, s->head / b->hsize, p, &pos);
    render_snake_head(b->indirs[s->head], s->move, false, frame, p, &pos);
    return;
  }


  // Case when the snake has max length at least 2



  // We start with the tail
  int seg = s->tail;
  render_get_cellpos(seg % b->hsize, seg / b->hsize, p, &pos);
  if (s->length < s->full_length) {
    render_static_part(b->indirs[seg], b->outdirs[seg], true, s->length >= 2, p, &pos);
  }
  else {
    render_snake_tail(b->indirs[s->tail], b->outdirs[s->tail], s->length >= 2, frame, p, &pos);
  }
  // We now draw the body

  if (s->length >= 2) {

    seg = get_adj_cell(b, seg, b->outdirs[seg]);
    render_get_cellpos(seg % b->hsize, seg / b->hsize, p, &pos);
    pos.x += var_tile_size[p];
    pos.y += var_tile_size[p];
    render_tile_snake(b->indirs[seg], b->outdirs[seg], p, &pos);
  }


  if (s->length >= 3) {
    for (int i = 0; i < s->length - 2; i++) {
      seg = get_adj_cell(b, seg, b->outdirs[seg]);
      render_get_cellpos(seg % b->hsize, seg / b->hsize, p, &pos);
      render_static_part(b->indirs[seg], b->outdirs[seg], false, false, p, &pos);
    }
  }


  // Drawing the head
  if (s->alive) {
    seg = s->head;
    render_get_cellpos(seg % b->hsize, seg / b->hsize, p, &pos);

    render_snake_head(b->indirs[seg], s->move, true, frame, p, &pos);

  }
  else {
    pos.h = var_tile_size[p];
    pos.w = var_tile_size[p];
    render_get_cellpos(seg % b->hsize, seg / b->hsize, p, &pos);
    switch (b->outdirs[seg])
    {
    case UP:
      pos.x += var_tile_size[p];
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_SHEAD], &pos, -90, NULL, SDL_FLIP_NONE);
      break;
    case RIGHT:
      pos.x += 2 * var_tile_size[p];
      pos.y += var_tile_size[p];
      SDL_RenderCopy(renderer, txt_anims, &clp_textures[CLP_SHEAD], &pos);
      break;
    case DOWN:
      pos.x += var_tile_size[p];
      pos.y += 2 * var_tile_size[p];
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_SHEAD], &pos, 90, NULL, SDL_FLIP_NONE);
      break;
    case LEFT:
      pos.y += var_tile_size[p];
      SDL_RenderCopyEx(renderer, txt_anims, &clp_textures[CLP_SHEAD], &pos, 180, NULL, SDL_FLIP_NONE);
      break;

    default:
      break;
    }



  }








}




char score_buffer[64];

#define SCORE_PAD 20

void render_ingame_score(game* g, int p) {
  if (!g) {
    fprintf(stderr, "Invalid game.\n");
    exit(EXIT_FAILURE);
  }
  if (p < 0 || p > 1) {
    fprintf(stderr, "Invalid player.\n");
    exit(EXIT_FAILURE);
  }

  int width = var_screen_width;
  if (var_dual_screen) {
    width /= 2;
  }

  int size = var_screen_width / 8;

  sprintf(score_buffer, "Player %d", p + 1);

  render_frame(width - 5, 5, size, 132, NULL, ANC_NE);
  render_text(width - 5 - (size / 2), SCORE_PAD, score_buffer, Jungle24, ANC_NC);

  sprintf(score_buffer, "%d", g->snakes_array[g->nb_ais + p]->score);
  render_text(width - 5 - size + SCORE_PAD, SCORE_PAD + 30, "Score:", Jungle20, ANC_NW);
  render_text(width - 5 - SCORE_PAD, SCORE_PAD + 30, score_buffer, Jungle20, ANC_NE);

  sprintf(score_buffer, "%d", g->snakes_array[g->nb_ais + p]->length);
  render_text(width - 5 - size + SCORE_PAD, SCORE_PAD + 55, "Length:", Jungle20, ANC_NW);
  render_text(width - 5 - SCORE_PAD, SCORE_PAD + 55, score_buffer, Jungle20, ANC_NE);

  render_text(width - 5 - size + SCORE_PAD, SCORE_PAD + 80, "Speed:", Jungle20, ANC_NW);
  render_text(width - 5 - SCORE_PAD, SCORE_PAD + 80, speed_names[g->snakes_array[g->nb_ais + p]->speed], Jungle20, ANC_NE);





  //render






}







/********************************/
/*+ Affichage d'un poly d'algo **/
/********************************/



/*
void render_holy_poly(game* thegame, int frame, int speed) {
  CHECK_NULL(1, thegame, "The game");


  SDL_Rect pos;
  //pos.w = 100 * var_render_zoom;
  //pos.h = 175 * var_render_zoom;
  SDL_Rect impactpos;
  //impactpos.w = 192 * var_render_zoom;
  //impactpos.h = 192 * var_render_zoom;



  // Affichage de la scene
  render_scene_unkill(thegame, true, an_minotaurs_alive);

  if (frame / speed < 6) {
    render_toon_idle(PLAYER, thegame->player_alive, thegame->player_dir, thegame->m->player % thegame->m->hsize, thegame->m->player / thegame->m->hsize);
    for (int i = 0; i < thegame->m->nb_minotaurs;i++) {
      render_toon_idle(MINOTAUR, an_minotaurs_alive[i], thegame->minotaurs_dirs[i], thegame->m->minotaurs[i] % thegame->m->hsize, thegame->m->minotaurs[i] / thegame->m->hsize);
    }
    // Affichage des éclairs
    for (int i = 0; i < thegame->m->nb_minotaurs;i++) {
      if (an_minotaurs_alive[i] != thegame->minotaurs_alive[i]) {
        render_get_cellpos(thegame->m->minotaurs[i] % thegame->m->hsize, thegame->m->minotaurs[i] / thegame->m->hsize, &pos);
        //pos.x -= 14 * var_render_zoom;
        //pos.y -= 130 * var_render_zoom;
        SDL_RenderCopy(renderer, txt_lightning, &clp_textures[CLP_LIGHT1 + frame / speed], &pos);
      }
    }
  }
  else {

    render_all_toons_idle(thegame);
    for (int i = 0; i < thegame->m->nb_minotaurs;i++) {
      if (an_minotaurs_alive[i] != thegame->minotaurs_alive[i]) {
        if (frame / speed < 9) {
          render_get_cellpos(thegame->m->minotaurs[i] % thegame->m->hsize, thegame->m->minotaurs[i] / thegame->m->hsize, &pos);
          //pos.x -= 14 * var_render_zoom;
          //pos.y -= 130 * var_render_zoom;
          SDL_RenderCopy(renderer, txt_lightning, &clp_textures[CLP_LIGHT1 + 5], &pos);
        }
        render_get_cellpos(thegame->m->minotaurs[i] % thegame->m->hsize, thegame->m->minotaurs[i] / thegame->m->hsize, &impactpos);
        //impactpos.x -= 58 * var_render_zoom;
        //impactpos.y -= 54 * var_render_zoom;
        SDL_RenderCopy(renderer, txt_impact, &clp_textures[CLP_IMPACT1 + frame / speed - 6], &impactpos);
      }

    }

  }
  if (var_adv_path) {
    render_print_complex_path(thegame, var_adv_path);
  }
  //render_all_informations(thegame);
}

*/




/***************************/
/*+ Affichage d'une bombe **/
/***************************/



// Bombs

void render_snake_explosion(int i, int f, int p) {




  SDL_Rect pos;
  render_get_cellpos(var_game->snakes_array[i]->head % var_game->b->hsize, var_game->snakes_array[i]->head / var_game->b->hsize, p, &pos);
  pos.w = var_tile_size[p] * 3;
  pos.h = var_tile_size[p] * 3;

  pos.x -= var_tile_size[p] / 2;
  pos.y -= var_tile_size[p] / 2;

  switch (var_game->snakes_array[i]->move)
  {
  case UP:
    pos.x += var_tile_size[p] / 2;
    pos.y -= var_tile_size[p];
    break;

  case LEFT:
    pos.x -= var_tile_size[p];
    pos.y += var_tile_size[p] / 2;
    break;

  case RIGHT:
    pos.x += 2 * var_tile_size[p];
    pos.y += var_tile_size[p] / 2;
    break;

  case DOWN:
    pos.x += var_tile_size[p] / 2;
    pos.y += 2 * var_tile_size[p];
    break;

  default:
    break;
  }



  SDL_RenderCopy(renderer, txt_explosion, &clp_textures[CLP_EXPLO1 + f / 12], &pos);
}


