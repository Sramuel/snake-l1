#include "project_snake.h"
#include "error.h"
#include "alloc.h"
#include <limits.h>

int speed_to_value(speed s) {
    if (s==SLOWER){
        return SLOWER_VAL;
    } if (s==SLOW){
        return SLOW_VAL;
    } if (s==MEDIUM){
        return MEDIUM_VAL;
    } if (s==FAST){
        return FAST_VAL;
    } if (s==FASTER){
        return FASTER_VAL;
    } if (s==LUDICROUS){
        return LUDICROUS_VAL;
    }
    return 1;
}

snake *new_snake(board *b, speed sp, int flen) {
    if (b == NULL || b->empty_cells_count < 2) return NULL;                                     // Si le plateau est nul ou qu'il y a moins de 2 cases vides, on ne peut pas placer de serpent
    
    for (int attempt = 0; attempt < 1000; attempt++) {                                          // On essaie jusqu'à 1000 fois de placer un serpent
        int i = rand() % b->empty_cells_count;                                                  // On choisit une cellule vide au hasard pour la tête
        int head = b->empty_cells_listing[i];
        direction dir = UP;                                                                     // On teste chaque direction pour voir s'il y a une cellule voisine vide pour la queue
        while (dir < DIRECTION_SIZE) {                                                          // On récupère la cellule adjacente dans la direction opposée (car la queue est derrière la tête)
          
            int tail = get_adj_cell(b, head, opposite(dir));
            if (tail != -1) {                                                                   // Si la cellule existe (pas un bord ou en dehors du plateau)
                if (b->objects[tail] == EMPTY && b->masked[tail] == false) {                    // Et si elle est vide et non masquée
                    snake *s = malloc(sizeof(snake));                                           // On peut créer un nouveau serpent
                    if (s == NULL) return NULL;                                                 // échec d'allocation mémoire
                                                                                                // Initialisation des champs du serpent
                    s->alive = true;
                    s->head = head;
                    s->tail = tail;
                    s->length = 1;                                                              // Le serpent occupe 2 cellules mais n'a "grandi" que d'une
                    s->full_length = flen;                                                      // La longueur totale visée (si le serpent mange des objets)
                    s->progress = 0;                                                            // Il vient d'arriver dans sa cellule
                    s->move = dir;                                                              // Direction de déplacement initiale
                    s->speed = sp;                                                              // Vitesse de départ
                    s->score = 0;
                    s->distance = 0;
                    s->students = 0;

                    
                    fill_cell_board(b, head, SNAKE);                                            // On remplit les deux cellules sur le plateau avec le serpent
                    fill_cell_board(b, tail, SNAKE);                                            // On indique dans quelle direction le serpent est entré et sort de chaque cellule

                    b->indirs[head] = dir;                     
                    b->outdirs[tail] = dir;


                    return s;                                                                   // On retourne le serpent nouvellement créé
                }
            }
            dir = (direction)(dir + 1);                                                         // Tester la direction suivante (UP → RIGHT → DOWN → LEFT)
        }
    }
    return NULL;                                                                                // Si après 1000 tentatives on n’a pas trouvé deux cellules contiguës, on abandonne
}



void delete_snake(snake *s) {
    free(s);
    return;
}

void consume_object_snake(snake *s, object obj) {
    if (s == NULL || s->alive == false) 
        return;
    if (obj == APPLE) {
        s->full_length += 1;
        s->score += 10;
    } else if (obj == CHERRY) {
        s->full_length += 1;
        s->score += 20;
    } else if (obj == BANANA) {
        s->full_length += 2;
        s->score += 30;
    } else if (obj == GRAPES) {
        s->full_length += 2;
        s->score += 40;
    } else if (obj == PINEAPPLE) {
        s->full_length += 3;
        s->score += 50;
    } else if (obj == STUDENT) {
        s->full_length = s->full_length * 2;
        s->score += 100;
        s->students += 1;
    } else if (obj == MUSHROOM) {
        if (s->speed>SLOWER) {
            s->speed = (speed)(s->speed - 1);
        }
    } else if (obj == CHILI) {
        if (s->speed<LUDICROUS) {
            s->speed = (speed)(s->speed + 1);
        }
    }
    return;
}

bool implement_turn_snake(snake *s, board *b) {
    if (s == NULL || b == NULL || s->alive == false) {
        return false;
    }

    s->progress += speed_to_value(s->speed);                                                    // Avancer le progrès dans la cellule, ici progress est un int et je lui incrémente la vitesse en fonction de la vitesse grace a speed_to_value qui convertie en int
    if (s->progress < LENGTH_CELL) {                                                            // Si on n'a pas fini la cellule, on ne fait rien d'autre
        return false;
    }

    s->progress = 0;                                                                            // Sinon on termine la cellule actuelle
    int next_cell = get_adj_cell(b, s->head, s->move);                                          // Calcul de la cellule suivante selon la direction
    if (next_cell == -1 || b->masked[next_cell] || b->objects[next_cell] == SNAKE) {            // Vérification si la cellule suivante est valide
        s->alive = false;
        return true;
    }

    b->outdirs[s->head] = s->move;                                                              // Mettre à jour la direction de sortie sur la cellule actuelle
    if (s->length < s->full_length) {                                                           // Si le serpent n'est pas à pleine longueur, il s'allonge
        s->length++;
    } else {                                                                                    // Sinon la queue avance et on libère l'ancienne case
        int old_tail = s->tail;
        s->tail = get_adj_cell(b, old_tail, b->outdirs[old_tail]);
        empty_cell_board(b, old_tail);
    }
    
    object obj = b->objects[next_cell];                                                         // Manger l'objet (si c’est un fruit sinon ça va return rien (si c’est un serpent ou une case vide))
    consume_object_snake(s, obj);
    
    b->objects[next_cell] = SNAKE;                                                              // Avancer la tête dans la cellule suivante
    b->indirs[next_cell] = opposite(s->move);
    s->head = next_cell;
    s->distance++;
    return false;
}