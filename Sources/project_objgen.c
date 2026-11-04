#include "project_objgen.h"
#include "alloc.h"
#include "error.h"

void (*generator_funs[OGEN_SIZE])(game *) = {
    gen_empty, 
    gen_basic,                                         
    gen_single_apple, 
    gen_ten_percent,
    gen_student_invasion
};

const char* generator_names[OGEN_SIZE] = { 
    "Empty", 
    "Basic", 
    "Single Apple", 
    "Ten Percent", 
    "Student Invasion" 
};


void gen_empty(game *g) {
    return;
}


void gen_basic(game *g) {
    return;
}

void gen_single_apple(game *g) {
    return;
}


void gen_ten_percent(game *g) {
    return;
}

void gen_student_invasion(game *g) {
    return;
}
