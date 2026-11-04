#include "main.h"
#include "project_parameters.h"
#include "project_tools.h"

int main(void) {
  atexit(shutdown_SDL);

  // Inialisation du générateur de nombres aléatoires.
  srand((unsigned int)(time(NULL)));

  // Initialisation des dimensions de l'interface.
  var_screen_height = WINDOW_SCREENHEIGHT;
  var_screen_width = WINDOW_SCREENWIDTH;


  // Initialisation de la fenêtre
  init_SDL();

  gen_nbgames = MAX(1, QUICK_NBGAMES);
  gen_players = MIN(2, QUICK_PLAYERS);
  gen_iasnakes = QUICK_IA;
  gen_hsize = MAX(2, QUICK_HSIZE);
  gen_vsize = MAX(2, QUICK_VSIZE);

  if (QUICK_SPEED > FAST) {
    gen_speed = SLOW;
  }
  else {
    gen_speed = MAX(QUICK_SPEED, SLOW);
  }

  gen_speed = QUICK_SPEED;
  gen_maxlength = MAX(1, QUICK_MAXLENGTH);



  gen_strat = QUICK_STRAT;
  MALLOC(var_strats, gen_iasnakes);
  for (int i = 0; i < gen_iasnakes; i++) {
    var_strats[i] = gen_strat;
  }
  init_all_buttons();


  var_init_maskstab();
  gen_use_mask = false;
  if (QUICK_MASK) {
    for (int i = 0; i < var_masktabsize; i++) {
      if (strcmp(var_maskstab[i]->d_name, QUICK_MASK) == 0) {
        var_maskindex = i;
        gen_use_mask = true;
        strcpy(gen_maskname, QUICK_MASK);
        break;
      }
    }
  }

  var_objgen = QUICK_OBJGEN;


  event_loop();
  var_free_maskstab();

  exit(EXIT_SUCCESS);
}
