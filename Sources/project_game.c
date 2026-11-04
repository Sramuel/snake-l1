#include "project_game.h"
#include "alloc.h"


game *new_game(int hsize, int vsize, mask *m, int nh, int ns, int vs, int ls) {
    if (nh < 0 || nh > 2 || ns < 0 || vs <= 0 || ls <= 0 || hsize <= 0 || vsize <= 0) {             // Vérification des paramètres (valeurs interdites ou incohérentes)
        return NULL;
    }

    game *g = malloc(sizeof(game));                           // Allocation de la structure game
    if (g == NULL) return NULL;

    if (m == NULL) {                 // Création du plateau avec ou sans masque
        g->b = new_board_nomask(hsize, vsize);    // Plateau simple
    } else {
        resize_mask(m, hsize, vsize);          // Redimensionne le masque à hsize × vsize
        g->b = new_board_mask(m);              // Plateau basé sur le masque ajusté
    }

    if (g->b == NULL) {            // Si l'allocation du plateau échoue, on libère la mémoire du jeu
        free(g);
        return NULL;
    }
    g->nb_ais = ns;                // Nombre de serpents IA
    g->nb_players = nh;           // Nombre de joueurs humains
    g->nb_alive = ns + nh;        // Total de serpents en vie
    g->nb_turns = 0;              // Aucun tour joué au départ

    g->snakes_array = malloc((ns + nh) * sizeof(snake *));                 // Allocation du tableau de pointeurs vers les serpents
    if (g->snakes_array == NULL) {
        delete_board(g->b);
        free(g);
        return NULL;
    }

    // Création de chaque serpent (IA puis joueurs)
    for (int i = 0; i < ns + nh; i++) {
        g->snakes_array[i] = new_snake(g->b, vs, ls); // Crée un serpent à la vitesse vs et longueur ls
        if (g->snakes_array[i] == NULL) {       // Si l’un des serpents ne peut pas être créé, on annule tout
            for (int j = 0; j < i; j++) {
                delete_snake(g->snakes_array[j]); // Libération des serpents précédemment créés
            }
            free(g->snakes_array);
            delete_board(g->b);
            free(g);
            return NULL;
        }
    }
    return g;
}

void delete_game(game *g){
    free(g->snakes_array);
    free(g->b);
    free(g);
    g = NULL;
    return;
}

void set_direction_player1(game *g, direction dir) {
    if (g->nb_players < 1 || g->nb_players > 2) {
       return;
    } 
    if (g->nb_players == 1) {
       long unsigned int player1_index = g->nb_ais + g->nb_players-1;
       if (g->snakes_array[player1_index]->alive && dir != opposite(g->snakes_array[player1_index]->move)) {
           g->snakes_array[player1_index]->move = dir;
           return;
       }
    }
    if (g->nb_players == 2) {
       long unsigned int player1_index = g->nb_ais + g->nb_players-2;
       if (g->snakes_array[player1_index]->alive && dir != opposite(g->snakes_array[player1_index]->move)) {
           g->snakes_array[player1_index]->move = dir;
           return;
       }
    }
    return;
}

void set_direction_player2(game *g, direction dir) {
    if (g->nb_players < 1 || g->nb_players > 2) {
        return;
     } 
    if (g->nb_players == 1) {
            return;
        }
    if (g->nb_players == 2) {
       long unsigned int player1_index = g->nb_ais + g->nb_players-1;
       if (g->snakes_array[player1_index]->alive && dir != opposite(g->snakes_array[player1_index]->move)) {
           g->snakes_array[player1_index]->move = dir;
           return;
       }
    }
    return;
}

void implement_turn_all_snakes(game *g, score_table *st) {
    if (g == NULL || g->b == NULL) {
        return;
    }

    for (int i = 0; i < g->nb_ais + g->nb_players; i++) {
        snake *s = g->snakes_array[i];
        if (s != NULL && s->alive) {                                                            // Effectue un tour pour ce serpent
       
            bool died = implement_turn_snake(s, g->b);

            if (died) {
                s->alive = false;
                g->nb_alive--;

                if (st != NULL) {
                    int time = get_time_counter() / 1000;
                    update_single_score(st, i, s, time);
                }
            }
        }
    }

    if (st != NULL) {                                                                           // Mise à jour des scores de tous les serpents (morts ou vivants)
        for (int i = 0; i < g->nb_ais + g->nb_players; i++) {
            snake *s = g->snakes_array[i];

            if (s != NULL) {
                int gi = st->game_to_score[i];
                single_score *sc = st->scores[gi][st->cu_game];

                if (sc->filled == false) {
                    int time = get_time_counter() / 1000;
                    update_single_score(st, i, s, time);
                }
            }
        }
    }

    g->nb_turns++;
}