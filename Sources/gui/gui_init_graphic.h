/**
 * @file gui_init_graphic.h
 * @brief
 * Pre-computation of the displayed grid. DO NOT MODIFY.
 *
 * @attention
 * This part is already implemented. It should not be modified.
 */

#ifndef _GUI_INIT_GRAPHIC_H_
#define _GUI_INIT_GRAPHIC_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "gui_textbuf.h"
#include "gui_gamevars.h"

 /*  ___       _ _   _       _ _          _   _                      __   ____  ____  _      */
 /* |_ _|_ __ (_) |_(_) __ _| (_)______ _| |_(_) ___  _ __     ___  / _| / ___||  _ \| |     */
 /*  | || '_ \| | __| |/ _` | | |_  / _` | __| |/ _ \| '_ \   / _ \| |_  \___ \| | | | |     */
 /*  | || | | | | |_| | (_| | | |/ / (_| | |_| | (_) | | | | | (_) |  _|  ___) | |_| | |___  */
 /* |___|_| |_|_|\__|_|\__,_|_|_/___\__,_|\__|_|\___/|_| |_|  \___/|_|   |____/|____/|_____| */


 /************/
 /*+ Colors +*/
 /************/

/**
 * @brief Black.
 */
static const SDL_Color BLACK = { 0, 0, 0, 255 };

/**
 * @brief White.
 */
static const SDL_Color WHITE = { 255, 255, 255, 255 };

/**
 * @brief Blue
 */
static const SDL_Color BLUET = { 25, 25, 252, 200 };

/**
 * @brief Orange
 */
static const SDL_Color ORANGE = { 239, 216, 7, 200 };

/**
 * @brief Pale.
 */
static const SDL_Color PALE = { 250,235,215, 200 };

#define COLOR_TUPLE(color) ((color).r), ((color).g), ((color).b), ((color).a)

/***********/
/*+ Fonts +*/
/***********/

extern TTF_Font* Sans18, * Sans16, * Paci20, * SnakeFont, * Jungle18, * Jungle20, * Jungle24, * Jungle28, * Jungle36;

/**
 * @brief Chargement des fonts.
 */
void init_fonts(void);

/*************/
/*+ Sprites +*/
/*************/

/**
 * @brief Initializes the module that loads the PNG images.
 */
void init_image(void);

extern SDL_Texture* txt_icons;
extern SDL_Texture* txt_frames;
extern SDL_Texture* txt_student;
extern SDL_Texture* txt_explosion;
extern SDL_Texture* txt_terrain;

extern SDL_Texture* txt_snakegreen;
extern SDL_Texture* txt_snakeblue;
extern SDL_Texture* txt_snakered;
extern SDL_Texture* txt_snakeblack;
extern SDL_Texture* txt_food;
/**
 * @brief Internal names for the texture coordinates
 */
typedef enum {

    // Basic snake blocks

    CLP_STUBE,
    CLP_STURN,
    CLP_SHEAD,
    CLP_STAIL,

    // Head animation for large body (left to right)
    CLP_SHAL0,
    CLP_SHAL1,
    CLP_SHAL2,
    CLP_SHAL3,
    CLP_SHAL4,
    CLP_SHAL5,
    CLP_SHAL6,
    CLP_SHAL7,
    CLP_SHAL8,
    CLP_SHAL9,
    CLP_SHAL10,
    CLP_SHAL11,
    CLP_SHAL12,
    CLP_SHAL13,
    CLP_SHAL14,
    CLP_SHAL15,
    CLP_SHAL16,

    // Head animation for small body (left to right)
    CLP_SHAS0,
    CLP_SHAS1,
    CLP_SHAS2,
    CLP_SHAS3,
    CLP_SHAS4,
    CLP_SHAS5,
    CLP_SHAS6,
    CLP_SHAS7,
    CLP_SHAS8,
    CLP_SHAS9,
    CLP_SHAS10,
    CLP_SHAS11,
    CLP_SHAS12,
    CLP_SHAS13,
    CLP_SHAS14,
    CLP_SHAS15,
    CLP_SHAS16,

    // Head animation for large body (up to right)
    CLP_SHATL0,
    CLP_SHATL1,
    CLP_SHATL2,
    CLP_SHATL3,
    CLP_SHATL4,
    CLP_SHATL5,
    CLP_SHATL6,
    CLP_SHATL7,
    CLP_SHATL8,
    CLP_SHATL9,
    CLP_SHATL10,
    CLP_SHATL11,
    CLP_SHATL12,
    CLP_SHATL13,
    CLP_SHATL14,
    CLP_SHATL15,
    CLP_SHATL16,

    // Head animation for small body (up to right)
    CLP_SHATS0,
    CLP_SHATS1,
    CLP_SHATS2,
    CLP_SHATS3,
    CLP_SHATS4,
    CLP_SHATS5,
    CLP_SHATS6,
    CLP_SHATS7,
    CLP_SHATS8,
    CLP_SHATS9,
    CLP_SHATS10,
    CLP_SHATS11,
    CLP_SHATS12,
    CLP_SHATS13,
    CLP_SHATS14,
    CLP_SHATS15,
    CLP_SHATS16,

    // Tail animation for large body (left to right)
    CLP_STAL0,
    CLP_STAL1,
    CLP_STAL2,
    CLP_STAL3,
    CLP_STAL4,
    CLP_STAL5,
    CLP_STAL6,
    CLP_STAL7,
    CLP_STAL8,
    CLP_STAL9,
    CLP_STAL10,
    CLP_STAL11,
    CLP_STAL12,
    CLP_STAL13,
    CLP_STAL14,
    CLP_STAL15,
    CLP_STAL16,

    // Tail animation for small body (left to right)
    CLP_STAS0,
    CLP_STAS1,
    CLP_STAS2,
    CLP_STAS3,
    CLP_STAS4,
    CLP_STAS5,
    CLP_STAS6,
    CLP_STAS7,
    CLP_STAS8,
    CLP_STAS9,
    CLP_STAS10,
    CLP_STAS11,
    CLP_STAS12,
    CLP_STAS13,
    CLP_STAS14,
    CLP_STAS15,
    CLP_STAS16,

    // Tail animation for large body (up to right)
    CLP_STATL0,
    CLP_STATL1,
    CLP_STATL2,
    CLP_STATL3,
    CLP_STATL4,
    CLP_STATL5,
    CLP_STATL6,
    CLP_STATL7,
    CLP_STATL8,
    CLP_STATL9,
    CLP_STATL10,
    CLP_STATL11,
    CLP_STATL12,
    CLP_STATL13,
    CLP_STATL14,
    CLP_STATL15,
    CLP_STATL16,

    // Tail animation for small body (up to right)
    CLP_STATS0,
    CLP_STATS1,
    CLP_STATS2,
    CLP_STATS3,
    CLP_STATS4,
    CLP_STATS5,
    CLP_STATS6,
    CLP_STATS7,
    CLP_STATS8,
    CLP_STATS9,
    CLP_STATS10,
    CLP_STATS11,
    CLP_STATS12,
    CLP_STATS13,
    CLP_STATS14,
    CLP_STATS15,
    CLP_STATS16,

    // Terrain
    CLP_ROCKP1,
    CLP_ROCKFLU,
    CLP_ROCKFRU,
    CLP_ROCKP2,
    CLP_ROCKFLD,
    CLP_ROCKFRD,
    CLP_ROCKUL,
    CLP_ROCKU,
    CLP_ROCKUR,
    CLP_ROCKL,
    CLP_ROCKC,
    CLP_ROCKR,
    CLP_ROCKDL,
    CLP_ROCKD,
    CLP_ROCKDR,
    CLP_ROCKT1,
    CLP_ROCKT2,
    CLP_ROCKT3,


    CLP_HOLEP1,
    CLP_HOLEFLU,
    CLP_HOLEFRU,
    CLP_HOLEP2,
    CLP_HOLEFLD,
    CLP_HOLEFRD,
    CLP_HOLEUL,
    CLP_HOLEU,
    CLP_HOLEUR,
    CLP_HOLEL,
    CLP_HOLEC,
    CLP_HOLER,
    CLP_HOLEDL,
    CLP_HOLED,
    CLP_HOLEDR,
    CLP_HOLET1,
    CLP_HOLET2,
    CLP_HOLET3,


    CLP_WATERP1,
    CLP_WATERFLU,
    CLP_WATERFRU,
    CLP_WATERP2,
    CLP_WATERFLD,
    CLP_WATERFRD,
    CLP_WATERUL,
    CLP_WATERU,
    CLP_WATERUR,
    CLP_WATERL,
    CLP_WATERC,
    CLP_WATERR,
    CLP_WATERDL,
    CLP_WATERD,
    CLP_WATERDR,
    CLP_WATERT1,
    CLP_WATERT2,
    CLP_WATERT3,


    CLP_LAVAP1,
    CLP_LAVAFLU,
    CLP_LAVAFRU,
    CLP_LAVAP2,
    CLP_LAVAFLD,
    CLP_LAVAFRD,
    CLP_LAVAUL,
    CLP_LAVAU,
    CLP_LAVAUR,
    CLP_LAVAL,
    CLP_LAVAC,
    CLP_LAVAR,
    CLP_LAVADL,
    CLP_LAVAD,
    CLP_LAVADR,
    CLP_LAVAT1,
    CLP_LAVAT2,
    CLP_LAVAT3,



    CLP_GRASSP1,
    CLP_GRASSFLU,
    CLP_GRASSFRU,
    CLP_GRASSP2,
    CLP_GRASSFLD,
    CLP_GRASSFRD,
    CLP_GRASSUL,
    CLP_GRASSU,
    CLP_GRASSUR,
    CLP_GRASSL,
    CLP_GRASSC,
    CLP_GRASSR,
    CLP_GRASSDL,
    CLP_GRASSD,
    CLP_GRASSDR,
    CLP_GRASST1,
    CLP_GRASST2,
    CLP_GRASST3,

    CLP_SANDP1,
    CLP_SANDFLU,
    CLP_SANDFRU,
    CLP_SANDP2,
    CLP_SANDFLD,
    CLP_SANDFRD,
    CLP_SANDUL,
    CLP_SANDU,
    CLP_SANDUR,
    CLP_SANDL,
    CLP_SANDC,
    CLP_SANDR,
    CLP_SANDDL,
    CLP_SANDD,
    CLP_SANDDR,
    CLP_SANDT1,
    CLP_SANDT2,
    CLP_SANDT3,

    CLP_BLACKRP1,
    CLP_BLACKRFLU,
    CLP_BLACKRFRU,
    CLP_BLACKRP2,
    CLP_BLACKRFLD,
    CLP_BLACKRFRD,
    CLP_BLACKRUL,
    CLP_BLACKRU,
    CLP_BLACKRUR,
    CLP_BLACKRL,
    CLP_BLACKRC,
    CLP_BLACKRR,
    CLP_BLACKRDL,
    CLP_BLACKRD,
    CLP_BLACKRDR,
    CLP_BLACKRT1,
    CLP_BLACKRT2,
    CLP_BLACKRT3,

    CLP_FENCEL,
    CLP_FENCEC,
    CLP_FENCER,

    CLP_FENCED,
    CLP_FENCEW,
    CLP_FENCEU,

    // Cactus
    CLP_CACTUS1T,
    CLP_CACTUS2T,
    CLP_CACTUS3LT,
    CLP_CACTUS3RT,
    CLP_CACTUS1B,
    CLP_CACTUS2B,
    CLP_CACTUS3LB,
    CLP_CACTUS3RB,
    CLP_CACTUS4,
    CLP_CACTUS5,



    // Food 

    CLP_APPLE,
    CLP_CHERRY,
    CLP_BANANA,
    CLP_GRAPES,
    CLP_PINEAPPLE,
    CLP_CHILI,
    CLP_MUSHROOM,








    // Icons
    CLP_ARRN,
    CLP_ARRE,
    CLP_ARRS,
    CLP_ARRW,
    CLP_STOP,
    CLP_UNDO,
    CLP_QUES,
    CLP_TOON,

    // UI
    CLP_TBOXNW,
    CLP_TBOXN,
    CLP_TBOXNE,
    CLP_TBOXW,
    CLP_TBOXC,
    CLP_TBOXE,
    CLP_TBOXSW,
    CLP_TBOXS,
    CLP_TBOXSE,

    CLP_TTITW,
    CLP_TTITC,
    CLP_TTITE,
    CLP_TTITWB,
    CLP_TTITEB,


    CLP_PUSHOFF,
    CLP_PUSHON,
    CLP_GPUSHOFF,
    CLP_GPUSHON,
    CLP_RPUSHOFF,
    CLP_RPUSHON,
    CLP_KPUSHOFF,
    CLP_KPUSHON,

    CLP_CIRCLE,


    CLP_MOVEON,
    CLP_MOVEOFF,

    CLP_LEFTD,
    CLP_RIGHTD,
    CLP_BELOWD,

    CLP_EDIT,



    CLP_PLUS,
    CLP_MINUS,

    CLP_TUBEL,
    CLP_TUBEC,
    CLP_TUBER,

    CLP_FTUBEL,
    CLP_FTUBEC,
    CLP_FTUBER,


    CLP_BIGL,
    CLP_BIGC,
    CLP_BIGR,

    CLP_BIGBLON,
    CLP_BIGBCON,
    CLP_BIGBRON,
    CLP_BIGBLOFF,
    CLP_BIGBCOFF,
    CLP_BIGBROFF,



    // Student

    CLP_STUDENT,


    // Explosion

    CLP_EXPLO1,
    CLP_EXPLO2,
    CLP_EXPLO3,
    CLP_EXPLO4,
    CLP_EXPLO5,
    CLP_EXPLO6,
    CLP_EXPLO7,




    // Number of clips
    CLP_SIZE,
} textureclips;
extern SDL_Rect clp_textures[CLP_SIZE];


/**
 * @brief Initialization of the sprites.
 */
void init_load_sprites(void);

/*****************/
/*+ Fenêtre SDL +*/
/*****************/

extern SDL_Window* window;
extern SDL_Renderer* renderer;

/**
 * @brief Initialization of SDL.
 */
bool init_SDL(void);

/**
 * @brief Shutdown of SDL.
 */
void shutdown_SDL(void);






#endif // _GUI_INIT_GRAPHIC_H_
