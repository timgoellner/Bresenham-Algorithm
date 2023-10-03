#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <SDL3/SDL.h>
#include "bresenham.c"
#include "constants.h"


int running;
int last_frame;
SDL_Window *window;
SDL_Renderer *renderer;

/*
    0 -> Line
    1 -> Circle
    2 -> Triangle
    3 -> Square
*/
int mode;

SDL_FRect pixels[BOARD_SIZE][BOARD_SIZE];
int pixel_info[BOARD_SIZE][BOARD_SIZE];

int pressed;
int reset;
int mouse_pos[2];

int active_point;
int points[3][2] = { { UNDEFINED, UNDEFINED }, { UNDEFINED, UNDEFINED }, { UNDEFINED, UNDEFINED } };


int initialize_window();
void setup();
void process_input();
void update();
void render();
void destroy();
int main(int argc, char **argv);


#endif