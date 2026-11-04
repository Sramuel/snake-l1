#include "project_strats.h"
#include "alloc.h"
#include "error.h"

void (*strat_funs[STRAT_SIZE])(game *, int) = {
    empty_strategy,    
    closest_fruit_strategy, 
    score_strategy,
    students_strategy, 
    distance_strategy, 
    time_strategy
};

const char *strat_names[STRAT_SIZE] = {"Empty",
                                       "Closest fruit",
                                       "Maximize score",
                                       "Eat lots of students",
                                       "Maximize distance",
                                       "Survive"};

void empty_strategy(game *g, int i) {
    return;
}

void closest_fruit_strategy(game *g, int i) {
    return;
}

void score_strategy(game *g, int i) {
    return;
}

void students_strategy(game *g, int i) {
    return;
}


void distance_strategy(game *g, int i) {
    return;
}

void time_strategy(game *g, int i) {
    return;
}
