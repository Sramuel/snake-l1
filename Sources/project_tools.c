#include "project_tools.h"

int time_start;
int time_counter;

void init_time_counter(void) {
    time_counter = 0;
    time_start = SDL_GetTicks();
}
void pause_time_counter(void) {
    time_counter += SDL_GetTicks() - time_start;
}
void resume_time_counter(void) {
    time_start = SDL_GetTicks();
}
int get_time_counter(void) {
    return time_counter + SDL_GetTicks() - time_start;
}


