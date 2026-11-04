#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gui_init_graphic.h"


/***********/
/*+ Fonts +*/
/***********/

TTF_Font* Sans18, * Sans16, * Paci20, * SnakeFont, * Jungle18, * Jungle20, * Jungle24, * Jungle28, * Jungle36;
void init_fonts(void) {
  if (TTF_Init() < 0) {
    FATAL("TTF_Init: %s\n", TTF_GetError());
  }

  if (!(Paci20 = TTF_OpenFont("../Fonts/Pacifico.ttf", 20))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(Sans18 = TTF_OpenFont("../Fonts/Arial_Rounded_Bold.ttf", 18))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(Sans16 = TTF_OpenFont("../Fonts/DejaVuSans.ttf", 16))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(SnakeFont = TTF_OpenFont("../Fonts/snake.ttf", 72))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(Jungle18 = TTF_OpenFont("../Fonts/JungleRanger.ttf", 18))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(Jungle20 = TTF_OpenFont("../Fonts/JungleRanger.ttf", 20))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(Jungle24 = TTF_OpenFont("../Fonts/JungleRanger.ttf", 24))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(Jungle28 = TTF_OpenFont("../Fonts/JungleRanger.ttf", 28))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }

  if (!(Jungle36 = TTF_OpenFont("../Fonts/JungleRanger.ttf", 36))) {
    FATAL("TTF_OpenFont: %s\n", TTF_GetError());
  }
}

/*************/
/*+ Sprites +*/
/*************/

void init_image(void) {
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    FATAL("IMG_Init: %s\n", IMG_GetError());
  }
}


SDL_Texture* txt_icons;
SDL_Texture* txt_frames;
SDL_Texture* txt_student;

SDL_Texture* txt_explosion;
SDL_Texture* txt_terrain;

SDL_Texture* txt_snakegreen;
SDL_Texture* txt_snakeblue;
SDL_Texture* txt_snakered;
SDL_Texture* txt_snakeblack;

SDL_Texture* txt_food;


SDL_Rect clp_textures[CLP_SIZE];

void init_load_sprites(void) {

  SDL_Surface* image = NULL;

  image = IMG_Load("../Sprites/bluesnake.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_snakeblue = SDL_CreateTextureFromSurface(renderer, image);
  image = IMG_Load("../Sprites/greensnake.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_snakegreen = SDL_CreateTextureFromSurface(renderer, image);
  image = IMG_Load("../Sprites/redsnake.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_snakered = SDL_CreateTextureFromSurface(renderer, image);
  image = IMG_Load("../Sprites/blacksnake.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_snakeblack = SDL_CreateTextureFromSurface(renderer, image);


  SDL_FreeSurface(image);
  for (int i = CLP_STUBE; i <= CLP_STAIL; i++) {
    clp_textures[i].h = 40;
    clp_textures[i].w = 40;
    clp_textures[i].x = 40 * (i + 1);
    clp_textures[i].y = 600;
  }



  for (int i = 0; i <= 16; i++) {
    clp_textures[CLP_SHAL0 + i].h = 120;
    clp_textures[CLP_SHAL0 + i].w = 120;
    clp_textures[CLP_SHAL0 + i].x = 120 * i;
    clp_textures[CLP_SHAL0 + i].y = 0;

    clp_textures[CLP_STAL0 + i].h = 120;
    clp_textures[CLP_STAL0 + i].w = 120;
    clp_textures[CLP_STAL0 + i].x = 120 * i;
    clp_textures[CLP_STAL0 + i].y = 120;
  }



  for (int i = 0; i <= 7; i++) {
    clp_textures[CLP_SHAS0 + i].h = 120;
    clp_textures[CLP_SHAS0 + i].w = 120;
    clp_textures[CLP_SHAS0 + i].x = 120 * i;
    clp_textures[CLP_SHAS0 + i].y = 0;


    clp_textures[CLP_STAS0 + i].h = 120;
    clp_textures[CLP_STAS0 + i].w = 120;
    clp_textures[CLP_STAS0 + i].x = 120 * i;
    clp_textures[CLP_STAS0 + i].y = 240;


  }

  for (int i = 8; i <= 26; i++) {
    clp_textures[CLP_SHAS0 + i].h = 120;
    clp_textures[CLP_SHAS0 + i].w = 120;
    clp_textures[CLP_SHAS0 + i].x = 120 * i;
    clp_textures[CLP_SHAS0 + i].y = 240;


    clp_textures[CLP_STAS0 + i].h = 120;
    clp_textures[CLP_STAS0 + i].w = 120;
    clp_textures[CLP_STAS0 + i].x = 120 * i;
    clp_textures[CLP_STAS0 + i].y = 120;
  }

  for (int i = 0; i <= 6; i++) {
    clp_textures[CLP_STATL0 + i].h = 120;
    clp_textures[CLP_STATL0 + i].w = 120;
    clp_textures[CLP_STATL0 + i].x = i * 120;
    clp_textures[CLP_STATL0 + i].y = 360;

    clp_textures[CLP_STATS0 + i].h = 120;
    clp_textures[CLP_STATS0 + i].w = 120;
    clp_textures[CLP_STATS0 + i].x = i * 120;
    clp_textures[CLP_STATS0 + i].y = 480;

  }

  for (int i = 7; i <= 16; i++) {
    clp_textures[CLP_STATL0 + i] = clp_textures[CLP_STAL0 + i];
    clp_textures[CLP_STATS0 + i] = clp_textures[CLP_STAS0 + i];
  }


  for (int i = 0; i <= 13; i++) {
    clp_textures[CLP_SHATL0 + i] = clp_textures[CLP_SHAL0 + i];
    clp_textures[CLP_SHATS0 + i] = clp_textures[CLP_SHAS0 + i];
  }

  for (int i = 14; i <= 16; i++) {
    clp_textures[CLP_SHATL0 + i].h = 120;
    clp_textures[CLP_SHATL0 + i].w = 120;
    clp_textures[CLP_SHATL0 + i].x = 840 + 120 * (i - 14);
    clp_textures[CLP_SHATL0 + i].y = 360;

    clp_textures[CLP_SHATS0 + i].h = 120;
    clp_textures[CLP_SHATS0 + i].w = 120;
    clp_textures[CLP_SHATS0 + i].x = 840 + 120 * (i - 14);
    clp_textures[CLP_SHATS0 + i].y = 480;
  }






  /**************/
  /*+ Terrain  +*/
  /**************/

  image = IMG_Load("../Sprites/terrain.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_terrain = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);

  for (int i = CLP_ROCKP1; i <= CLP_FENCEU; i++) {
    clp_textures[i].h = 32;
    clp_textures[i].w = 32;
  }

  for (int i = 0; i < 3;i++) {
    clp_textures[CLP_ROCKP1 + i].x = 32 * i + 96;
    clp_textures[CLP_ROCKP1 + i].y = 0;
    clp_textures[CLP_ROCKP2 + i].x = 32 * i + 96;
    clp_textures[CLP_ROCKP2 + i].y = 32;
    clp_textures[CLP_ROCKUL + i].x = 32 * i + 96;
    clp_textures[CLP_ROCKUL + i].y = 64;
    clp_textures[CLP_ROCKL + i].x = 32 * i + 96;
    clp_textures[CLP_ROCKL + i].y = 96;
    clp_textures[CLP_ROCKDL + i].x = 32 * i + 96;
    clp_textures[CLP_ROCKDL + i].y = 128;
    clp_textures[CLP_ROCKT1 + i].x = 32 * i + 96;
    clp_textures[CLP_ROCKT1 + i].y = 160;
  }

  for (int i = 0; i < 18; i++) {
    clp_textures[CLP_HOLEP1 + i].x = clp_textures[CLP_ROCKP1 + i].x + 288 - 96;
    clp_textures[CLP_HOLEP1 + i].y = clp_textures[CLP_ROCKP1 + i].y;

    clp_textures[CLP_WATERP1 + i].x = clp_textures[CLP_ROCKP1 + i].x + 96 - 96;
    clp_textures[CLP_WATERP1 + i].y = clp_textures[CLP_ROCKP1 + i].y + 192;

    clp_textures[CLP_LAVAP1 + i].x = clp_textures[CLP_ROCKP1 + i].x + 192 - 96;
    clp_textures[CLP_LAVAP1 + i].y = clp_textures[CLP_ROCKP1 + i].y + 384;

    clp_textures[CLP_GRASSP1 + i].x = clp_textures[CLP_ROCKP1 + i].x + 192 - 96;
    clp_textures[CLP_GRASSP1 + i].y = clp_textures[CLP_ROCKP1 + i].y + 192;

    clp_textures[CLP_SANDP1 + i].x = clp_textures[CLP_ROCKP1 + i].x - 96;
    clp_textures[CLP_SANDP1 + i].y = clp_textures[CLP_ROCKP1 + i].y + 384;

    clp_textures[CLP_BLACKRP1 + i].x = clp_textures[CLP_ROCKP1 + i].x + +96;
    clp_textures[CLP_BLACKRP1 + i].y = clp_textures[CLP_ROCKP1 + i].y;// +384;
  }

  for (int i = 0; i < 3; i++) {
    clp_textures[CLP_FENCEL + i].x = 32 * i;
    clp_textures[CLP_FENCEL + i].y = 576;

    clp_textures[CLP_FENCED + i].x = 192 + 32 * i;
    clp_textures[CLP_FENCED + i].y = 576;
  }

  for (int i = CLP_CACTUS1T; i <= CLP_CACTUS3RT; i++) {
    clp_textures[i].h = 32;
    clp_textures[i].w = 32;
    clp_textures[i].x = 32 * (i - CLP_CACTUS1T); ;
    clp_textures[i].y = 608;
  }

  for (int i = CLP_CACTUS1B; i <= CLP_CACTUS5; i++) {
    clp_textures[i].h = 32;
    clp_textures[i].w = 32;
    clp_textures[i].x = 32 * (i - CLP_CACTUS1B);
    clp_textures[i].y = 640;
  }




  image = IMG_Load("../Sprites/food.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_food = SDL_CreateTextureFromSurface(renderer, image);

  clp_textures[CLP_APPLE].h = 32;
  clp_textures[CLP_APPLE].w = 32;

  for (int i = CLP_CHERRY; i <= CLP_MUSHROOM; i++) {
    clp_textures[i].h = 32;
    clp_textures[i].w = 32;
  }

  clp_textures[CLP_APPLE].x = 96;
  clp_textures[CLP_APPLE].y = 0;
  clp_textures[CLP_CHERRY].x = 288;
  clp_textures[CLP_CHERRY].y = 0;
  clp_textures[CLP_BANANA].x = 0;
  clp_textures[CLP_BANANA].y = 0;
  clp_textures[CLP_GRAPES].x = 64;
  clp_textures[CLP_GRAPES].y = 0;
  clp_textures[CLP_PINEAPPLE].x = 192;
  clp_textures[CLP_PINEAPPLE].y = 0;
  clp_textures[CLP_CHILI].x = 96;
  clp_textures[CLP_CHILI].y = 96;
  clp_textures[CLP_MUSHROOM].x = 192;
  clp_textures[CLP_MUSHROOM].y = 224;



  image = IMG_Load("../Sprites/icons.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_icons = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);

  clp_textures[CLP_ARRN].h = 50;
  clp_textures[CLP_ARRN].w = 50;
  clp_textures[CLP_ARRN].x = 0;
  clp_textures[CLP_ARRN].y = 400;
  clp_textures[CLP_ARRE].h = 50;
  clp_textures[CLP_ARRE].w = 50;
  clp_textures[CLP_ARRE].x = 0;
  clp_textures[CLP_ARRE].y = 450;
  clp_textures[CLP_ARRS].h = 50;
  clp_textures[CLP_ARRS].w = 50;
  clp_textures[CLP_ARRS].x = 50;
  clp_textures[CLP_ARRS].y = 50;
  clp_textures[CLP_ARRW].h = 50;
  clp_textures[CLP_ARRW].w = 50;
  clp_textures[CLP_ARRW].x = 50;
  clp_textures[CLP_ARRW].y = 0;


  clp_textures[CLP_STOP].h = 50;
  clp_textures[CLP_STOP].w = 50;
  clp_textures[CLP_STOP].x = 150;
  clp_textures[CLP_STOP].y = 0;

  clp_textures[CLP_UNDO].h = 50;
  clp_textures[CLP_UNDO].w = 50;
  clp_textures[CLP_UNDO].x = 200;
  clp_textures[CLP_UNDO].y = 50;


  clp_textures[CLP_QUES].h = 50;
  clp_textures[CLP_QUES].w = 50;
  clp_textures[CLP_QUES].x = 200;
  clp_textures[CLP_QUES].y = 100;

  clp_textures[CLP_TOON].h = 50;
  clp_textures[CLP_TOON].w = 50;
  clp_textures[CLP_TOON].x = 150;
  clp_textures[CLP_TOON].y = 50;



  image = IMG_Load("../Sprites/ui.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_frames = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);

  for (int i = CLP_TBOXNW; i <= CLP_TBOXSE; i++) {
    clp_textures[i].h = 32;
    clp_textures[i].w = 32;
  }

  clp_textures[CLP_TBOXNW].x = 16;
  clp_textures[CLP_TBOXNW].y = 40;
  clp_textures[CLP_TBOXN].x = 49;
  clp_textures[CLP_TBOXN].y = 40;
  clp_textures[CLP_TBOXNE].x = 82;
  clp_textures[CLP_TBOXNE].y = 40;

  clp_textures[CLP_TBOXW].x = 478;
  clp_textures[CLP_TBOXW].y = 24;
  clp_textures[CLP_TBOXC].x = clp_textures[CLP_TBOXW].x + 33;
  clp_textures[CLP_TBOXC].y = 24;
  clp_textures[CLP_TBOXE].x = clp_textures[CLP_TBOXC].x + 33;
  clp_textures[CLP_TBOXE].y = 24;

  clp_textures[CLP_TBOXSW].x = 478;
  clp_textures[CLP_TBOXSW].y = 80;
  clp_textures[CLP_TBOXS].x = clp_textures[CLP_TBOXSW].x + 33;
  clp_textures[CLP_TBOXS].y = 80;
  clp_textures[CLP_TBOXSE].x = clp_textures[CLP_TBOXS].x + 33;
  clp_textures[CLP_TBOXSE].y = 80;


  clp_textures[CLP_TTITW].h = 24;
  clp_textures[CLP_TTITW].w = 24;
  clp_textures[CLP_TTITW].x = 634;
  clp_textures[CLP_TTITW].y = 118;

  clp_textures[CLP_TTITC].h = 24;
  clp_textures[CLP_TTITC].w = 23;
  clp_textures[CLP_TTITC].x = clp_textures[CLP_TTITW].x + 25;
  clp_textures[CLP_TTITC].y = 118;

  clp_textures[CLP_TTITE].h = 24;
  clp_textures[CLP_TTITE].w = 25;
  clp_textures[CLP_TTITE].x = clp_textures[CLP_TTITC].x + 24;
  clp_textures[CLP_TTITE].y = 118;


  clp_textures[CLP_TTITWB].h = 24;
  clp_textures[CLP_TTITWB].w = 46;
  clp_textures[CLP_TTITWB].x = 709;
  clp_textures[CLP_TTITWB].y = 143;

  clp_textures[CLP_TTITEB].h = 24;
  clp_textures[CLP_TTITEB].w = 47;
  clp_textures[CLP_TTITEB].x = clp_textures[CLP_TTITWB].x + 47;
  clp_textures[CLP_TTITEB].y = 143;



  clp_textures[CLP_PUSHOFF].h = 14;
  clp_textures[CLP_PUSHOFF].w = 14;
  clp_textures[CLP_PUSHOFF].x = 32;
  clp_textures[CLP_PUSHOFF].y = 121;


  clp_textures[CLP_PUSHON].h = 14;
  clp_textures[CLP_PUSHON].w = 14;
  clp_textures[CLP_PUSHON].x = 32;
  clp_textures[CLP_PUSHON].y = 137;


  clp_textures[CLP_GPUSHOFF].h = 14;
  clp_textures[CLP_GPUSHOFF].w = 14;
  clp_textures[CLP_GPUSHOFF].x = 16;
  clp_textures[CLP_GPUSHOFF].y = 121;


  clp_textures[CLP_GPUSHON].h = 14;
  clp_textures[CLP_GPUSHON].w = 14;
  clp_textures[CLP_GPUSHON].x = 16;
  clp_textures[CLP_GPUSHON].y = 137;


  clp_textures[CLP_RPUSHOFF].h = 14;
  clp_textures[CLP_RPUSHOFF].w = 14;
  clp_textures[CLP_RPUSHOFF].x = 48;
  clp_textures[CLP_RPUSHOFF].y = 121;


  clp_textures[CLP_RPUSHON].h = 14;
  clp_textures[CLP_RPUSHON].w = 14;
  clp_textures[CLP_RPUSHON].x = 48;
  clp_textures[CLP_RPUSHON].y = 137;


  clp_textures[CLP_KPUSHOFF].h = 14;
  clp_textures[CLP_KPUSHOFF].w = 14;
  clp_textures[CLP_KPUSHOFF].x = 64;
  clp_textures[CLP_KPUSHOFF].y = 121;


  clp_textures[CLP_KPUSHON].h = 14;
  clp_textures[CLP_KPUSHON].w = 14;
  clp_textures[CLP_KPUSHON].x = 64;
  clp_textures[CLP_KPUSHON].y = 137;


  clp_textures[CLP_CIRCLE].h = 24;
  clp_textures[CLP_CIRCLE].w = 24;
  clp_textures[CLP_CIRCLE].x = 762;
  clp_textures[CLP_CIRCLE].y = 86;


  clp_textures[CLP_MOVEON].h = 44;
  clp_textures[CLP_MOVEON].w = 44;
  clp_textures[CLP_MOVEON].x = 802;
  clp_textures[CLP_MOVEON].y = 431;

  clp_textures[CLP_MOVEOFF].h = 44;
  clp_textures[CLP_MOVEOFF].w = 44;
  clp_textures[CLP_MOVEOFF].x = 802;
  clp_textures[CLP_MOVEOFF].y = 481;


  clp_textures[CLP_LEFTD].h = 14;
  clp_textures[CLP_LEFTD].w = 14;
  clp_textures[CLP_LEFTD].x = 113;
  clp_textures[CLP_LEFTD].y = 121;

  clp_textures[CLP_RIGHTD].h = 14;
  clp_textures[CLP_RIGHTD].w = 14;
  clp_textures[CLP_RIGHTD].x = 129;
  clp_textures[CLP_RIGHTD].y = 121;

  clp_textures[CLP_BELOWD].h = 14;
  clp_textures[CLP_BELOWD].w = 14;
  clp_textures[CLP_BELOWD].x = 129;
  clp_textures[CLP_BELOWD].y = 137;

  clp_textures[CLP_EDIT].h = 14;
  clp_textures[CLP_EDIT].w = 14;
  clp_textures[CLP_EDIT].x = 81;
  clp_textures[CLP_EDIT].y = 105;

  clp_textures[CLP_PLUS].h = 14;
  clp_textures[CLP_PLUS].w = 14;
  clp_textures[CLP_PLUS].x = 81;
  clp_textures[CLP_PLUS].y = 121;

  clp_textures[CLP_MINUS].h = 14;
  clp_textures[CLP_MINUS].w = 14;
  clp_textures[CLP_MINUS].x = 97;
  clp_textures[CLP_MINUS].y = 121;

  clp_textures[CLP_TUBEL].h = 24;
  clp_textures[CLP_TUBEL].w = 34;
  clp_textures[CLP_TUBEL].x = 259;
  clp_textures[CLP_TUBEL].y = 88;

  clp_textures[CLP_TUBEC].h = 24;
  clp_textures[CLP_TUBEC].w = 23;
  clp_textures[CLP_TUBEC].x = 284;
  clp_textures[CLP_TUBEC].y = 63;

  clp_textures[CLP_TUBER].h = 24;
  clp_textures[CLP_TUBER].w = 34;
  clp_textures[CLP_TUBER].x = 294;
  clp_textures[CLP_TUBER].y = 88;


  clp_textures[CLP_FTUBEL].h = 14;
  clp_textures[CLP_FTUBEL].w = 8;
  clp_textures[CLP_FTUBEL].x = 428;
  clp_textures[CLP_FTUBEL].y = 72;

  clp_textures[CLP_FTUBEC].h = 14;
  clp_textures[CLP_FTUBEC].w = 7;
  clp_textures[CLP_FTUBEC].x = 437;
  clp_textures[CLP_FTUBEC].y = 72;

  clp_textures[CLP_FTUBER].h = 14;
  clp_textures[CLP_FTUBER].w = 8;
  clp_textures[CLP_FTUBER].x = 445;
  clp_textures[CLP_FTUBER].y = 72;



  clp_textures[CLP_BIGL].h = 64;
  clp_textures[CLP_BIGL].w = 32;
  clp_textures[CLP_BIGL].x = 16;
  clp_textures[CLP_BIGL].y = 184;

  clp_textures[CLP_BIGC].h = 64;
  clp_textures[CLP_BIGC].w = 30;
  clp_textures[CLP_BIGC].x = 49;
  clp_textures[CLP_BIGC].y = 184;

  clp_textures[CLP_BIGR].h = 64;
  clp_textures[CLP_BIGR].w = 32;
  clp_textures[CLP_BIGR].x = 82;
  clp_textures[CLP_BIGR].y = 184;


  clp_textures[CLP_BIGBLOFF].h = 24;
  clp_textures[CLP_BIGBLOFF].w = 40;
  clp_textures[CLP_BIGBLOFF].x = 634;
  clp_textures[CLP_BIGBLOFF].y = 25;

  clp_textures[CLP_BIGBCOFF].h = 24;
  clp_textures[CLP_BIGBCOFF].w = 40;
  clp_textures[CLP_BIGBCOFF].x = 675;
  clp_textures[CLP_BIGBCOFF].y = 25;

  clp_textures[CLP_BIGBROFF].h = 24;
  clp_textures[CLP_BIGBROFF].w = 40;
  clp_textures[CLP_BIGBROFF].x = 716;
  clp_textures[CLP_BIGBROFF].y = 25;


  clp_textures[CLP_BIGBLON].h = 24;
  clp_textures[CLP_BIGBLON].w = 40;
  clp_textures[CLP_BIGBLON].x = 634;
  clp_textures[CLP_BIGBLON].y = 85;

  clp_textures[CLP_BIGBCON].h = 24;
  clp_textures[CLP_BIGBCON].w = 40;
  clp_textures[CLP_BIGBCON].x = 675;
  clp_textures[CLP_BIGBCON].y = 85;

  clp_textures[CLP_BIGBRON].h = 24;
  clp_textures[CLP_BIGBRON].w = 40;
  clp_textures[CLP_BIGBRON].x = 716;
  clp_textures[CLP_BIGBRON].y = 85;









  /*******************************/
    /*+ Student */
    /*******************************/
  image = IMG_Load("../Sprites/student.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_student = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);




  clp_textures[CLP_STUDENT].h = 64;
  clp_textures[CLP_STUDENT].w = 64;
  clp_textures[CLP_STUDENT].x = 0;
  clp_textures[CLP_STUDENT].y = 640;

  /*
  int p = 0;
  for (int i = 0; i < 9;i++) {
    clp_textures[CLP_NWALK1 + i].h = 64;
    clp_textures[CLP_NWALK1 + i].w = 64;
    clp_textures[CLP_NWALK1 + i].x = p;
    clp_textures[CLP_NWALK1 + i].y = 512;


    clp_textures[CLP_EWALK1 + i].h = 64;
    clp_textures[CLP_EWALK1 + i].w = 64;
    clp_textures[CLP_EWALK1 + i].x = p;
    clp_textures[CLP_EWALK1 + i].y = 704;

    clp_textures[CLP_SWALK1 + i].h = 64;
    clp_textures[CLP_SWALK1 + i].w = 64;
    clp_textures[CLP_SWALK1 + i].x = p;
    clp_textures[CLP_SWALK1 + i].y = 640;


    clp_textures[CLP_WWALK1 + i].h = 64;
    clp_textures[CLP_WWALK1 + i].w = 64;
    clp_textures[CLP_WWALK1 + i].x = p;
    clp_textures[CLP_WWALK1 + i].y = 576;

    p += 64;
  }

  clp_textures[CLP_WIN].h = 64;
  clp_textures[CLP_WIN].w = 64;
  clp_textures[CLP_WIN].x = 64;
  clp_textures[CLP_WIN].y = 640 + 4 * 64;

  clp_textures[CLP_DEAD].h = 64;
  clp_textures[CLP_DEAD].w = 64;
  clp_textures[CLP_DEAD].x = 5 * 64;
  clp_textures[CLP_DEAD].y = 1280;

  p = 0;

  for (int i = 0; i < 6;i++) {
    clp_textures[CLP_NSWING1 + i].h = 192;
    clp_textures[CLP_NSWING1 + i].w = 192;
    clp_textures[CLP_NSWING1 + i].x = p;
    clp_textures[CLP_NSWING1 + i].y = 2880 + 64;

    clp_textures[CLP_ESWING1 + i].h = 192;
    clp_textures[CLP_ESWING1 + i].w = 192;
    clp_textures[CLP_ESWING1 + i].x = p;
    clp_textures[CLP_ESWING1 + i].y = 3468 + 64;

    clp_textures[CLP_SSWING1 + i].h = 192;
    clp_textures[CLP_SSWING1 + i].w = 192;
    clp_textures[CLP_SSWING1 + i].x = p;
    clp_textures[CLP_SSWING1 + i].y = 3272 + 64;

    clp_textures[CLP_WSWING1 + i].h = 192;
    clp_textures[CLP_WSWING1 + i].w = 192;
    clp_textures[CLP_WSWING1 + i].x = p;
    clp_textures[CLP_WSWING1 + i].y = 3076 + 64;


    p += 192;
  }
*/


/**************/
/* Explosion */
/**************/
  image = IMG_Load("../Sprites/explosion_96.png");
  if (!image)
  {
    printf("Error when loading sprites :  %s", IMG_GetError());
    return;
  }
  txt_explosion = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);

  for (int i = CLP_EXPLO1;i <= CLP_EXPLO7; i++) {
    clp_textures[i].x = (i % 8) * 96;
    clp_textures[i].y = 0;
    clp_textures[i].h = 96;
    clp_textures[i].w = 96;
  }

}


/*****************/
/*+ Fenêtre SDL +*/
/*****************/

SDL_Window* window;
SDL_Renderer* renderer;

bool init_SDL(void) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
    FATAL("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
  }

  // Chargement des fonts
  init_fonts();

  // Initialisation des PNGs
  init_image();

  // Chargement des masques
  var_init_maskstab();


  SDL_DisplayMode DM;
  SDL_GetDesktopDisplayMode(0, &DM);
  //  printf("Screen width: %d, Screen height: %d\n", DM.w, DM.h);
  if (var_screen_width <= 0 || DM.w < var_screen_width) {
    var_screen_width = DM.w;
  }
  if (var_screen_height <= 0 || DM.h < var_screen_height) {
    var_screen_height = DM.h;
  }
  // printf("Screen width: %d, Screen height: %d\n", var_screen_width, var_screen_height);

   // Création de la fenêtre
  window = SDL_CreateWindow("The InitC Snake Game",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    var_screen_width, var_screen_height,
#ifndef SOFTWARE_MODE
    SDL_WINDOW_OPENGL | 
#endif
    SDL_WINDOW_SHOWN |
    SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    FATAL("Could not create window: %s\n", SDL_GetError());
  }

  SDL_SetWindowResizable(window, SDL_FALSE);

  // Création de l'affichage
  renderer = SDL_CreateRenderer(window, -1,
#if SOFTWARE_MODE
  SDL_RENDERER_SOFTWARE
#else    
    SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC  
#endif
    );
  if (renderer == NULL) {
    FATAL("Could not create renderer: %s\n", SDL_GetError());
  }

  // Initialisation des sprites
  init_load_sprites();

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, COLOR_TUPLE(WHITE));
  SDL_RenderClear(renderer);

  return true;
}

void shutdown_SDL(void) {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }

  if (window) {
    SDL_DestroyWindow(window);
  }
  var_free_maskstab();
  SDL_Quit();
}


