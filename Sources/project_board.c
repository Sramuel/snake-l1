#include "project_board.h"
#include "alloc.h"
#include "error.h"

direction opposite(direction dir){  
    direction opposite_dir = dir; 
    if (dir==UP) opposite_dir = DOWN;
    if (dir==DOWN) opposite_dir = UP;
    if (dir==RIGHT) opposite_dir = LEFT;
    if (dir==LEFT) opposite_dir = RIGHT;
    return opposite_dir;
}

int get_adj_cell(board *b, int cell, direction dir) {
    int new_cell = cell; 
    if (dir==UP){  
        new_cell -= b->hsize;
        if (new_cell <0) return -1;
        return new_cell;
    } if (dir==DOWN){
        new_cell += b->hsize;
        if (new_cell >= b->hsize*b->vsize) return -1;
        return new_cell;
    } if (dir==RIGHT){
        new_cell += 1;
        if (new_cell % b->hsize == 0) return -1;
        return new_cell;
    } if (dir==LEFT){
        new_cell -= 1;
        if (new_cell % b->hsize == b->hsize - 1) return -1;
        return new_cell;
    } return -1;
}

board *new_board_nomask(int hsize, int vsize) {
    if (hsize <= 0 || vsize <= 0) return NULL;

    board *b = malloc(sizeof(board));                                                           //Allocation de la structure board
    if (b==NULL) return NULL;

    int size = hsize * vsize;
    b->hsize = hsize;
    b->vsize = vsize;
    b->size = size;
    b->nb_food = 0;
    b->masked = calloc(size, sizeof(bool));                                                     // Allocation et initialisation du tableau masked à false 
    b->objects = calloc(size, sizeof(object));                                                  // Allocation et initialisation du tableau objects à EMPTY 
    b->indirs = malloc(size * sizeof(direction));
    b->outdirs = malloc(size * sizeof(direction));
    b->empty_cells_listing = malloc(size * sizeof(int));
    b->empty_cells_indices = malloc(size * sizeof(int));

    if (b->masked==NULL || b->objects==NULL || b->indirs==NULL || b->outdirs==NULL || b->empty_cells_listing==NULL || b->empty_cells_indices==NULL) {
        delete_board(b);                                                                        // Libération de la mémoire si une allocation échoue
        return NULL;
    }
    for (int i = 0; i < size; i++) {                                                            // Initialisation des tableaux
        b->empty_cells_listing[i] = i;
        b->empty_cells_indices[i] = i;
    }
    b->empty_cells_count = size;
    return b;
}

board *new_board_mask(mask *m) {
    if (m==NULL || m->hsize <= 0 || m->vsize <= 0){
        return NULL;
    }

    int hsize = m->hsize;
    int vsize = m->vsize;
  
    board *b = malloc(sizeof(board));
    if (b==NULL) return NULL;

    int size = hsize * vsize;
    b->hsize = hsize;
    b->vsize = vsize;
    b->size = size;
    b->nb_food = 0;
    b->masked = malloc(size * sizeof(bool)); 
    b->objects = calloc(size, sizeof(object));
    b->indirs = malloc(size * sizeof(direction));
    b->outdirs = malloc(size * sizeof(direction));
    b->empty_cells_listing = malloc(size * sizeof(int));
    b->empty_cells_indices = malloc(size * sizeof(int));

    if (b->masked==NULL || b->objects==NULL || b->indirs==NULL || b->outdirs==NULL || b->empty_cells_listing==NULL || b->empty_cells_indices==NULL) {
        delete_board(b);                                                                        // Libération de la mémoire si une allocation échoue
        return NULL;
    }

    b->empty_cells_count = 0;
    for (int i = 0; i < size; i++) {
        b->masked[i] = m->grid[i];                                                              // On regarde si la cellule doit être masquée ou non
        if (b->masked[i] == false) {                                                            // Cellule non masquée donc on l'initialise
            b->objects[i] = EMPTY;
            b->empty_cells_listing[b->empty_cells_count] = i;
            b->empty_cells_indices[i] = b->empty_cells_count;
            b->empty_cells_count++;
        } else {
            b->objects[i] = -1;                                                                 // Par convention, -1 pour une cellule non utilisable, on ne pourra pas y mettre d'objet
            b->empty_cells_indices[i] = -1;                                                     // Par convention, -1 pour une cellule non utilisable, on ne l'aura pas dans la liste des cellules vides
        }
    }
    return b;
}

void delete_board(board *b) {
    free(b->empty_cells_indices);
    free(b->empty_cells_listing);
    free(b->outdirs);
    free(b->indirs);
    free(b->objects);
    free(b->masked);
    free(b);
    b = NULL;
    return;
}

void swap_empty_cells(board *b, int i1, int i2) {     

    int tmp = b->empty_cells_listing[i1];                                                       // Échange des valeurs dans empty_cells_listing
    b->empty_cells_listing[i1] = b->empty_cells_listing[i2];
    b->empty_cells_listing[i2] = tmp;

    b->empty_cells_indices[b->empty_cells_listing[i1]] = i1;                                    // Mise à jour des indices dans empty_cells_indices
    b->empty_cells_indices[b->empty_cells_listing[i2]] = i2;
}


void fill_cell_board(board *b, int i, object obj) {
  if (obj == EMPTY || b->masked[i] || b->objects[i] != EMPTY){                                  // Si la cellule est masquée ou déjà pleine
    return;
  }

  b->objects[i] = obj;
  int i1 = b->empty_cells_indices[i];
  if (i1 != -1) {
    int i2 = b->empty_cells_count - 1;
    swap_empty_cells(b, i1, i2);
    b->empty_cells_indices[b->empty_cells_listing[i2]] = -1;
    b->empty_cells_count--;
  } 

  if (obj >= APPLE && obj <= MUSHROOM) {
    b->nb_food++;
  }
  return;
}

void empty_cell_board(board *b, int i) {
  if (b->masked[i] || b->objects[i] == EMPTY) return;

  if (b->objects[i] >= APPLE && b->objects[i] <= MUSHROOM) {
    b->nb_food--;
  }
  b->objects[i] = EMPTY;
  b->empty_cells_indices[i] = b->empty_cells_count;
  b->empty_cells_listing[b->empty_cells_count] = i;
  b->empty_cells_count++;
  return;  
}

