#ifndef BRESENHAM
#define BRESENHAM

#include "constants.h"


void generate_line(int (*pixel_info)[BOARD_SIZE], int (*points)[2]);

void fill_symmetric_circle(int (*pixel_info)[BOARD_SIZE], int location[2], int origin[2]);
void generate_circle(int (*pixel_info)[BOARD_SIZE], int (*points)[2]);

void generate_triangle(int (*pixel_info)[BOARD_SIZE], int (*points)[2]);

void generate_square(int (*pixel_info)[BOARD_SIZE], int (*points)[2]);


#endif