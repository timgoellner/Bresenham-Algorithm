#include <math.h>
#include "bresenham.h"


void generate_line(int (*pixel_info)[BOARD_SIZE], int (*points)[2]) {
    int swap = points[0][0] > points[1][0];
    int ordered_points[2][2];

    for (int i=0; i<2; i++) { for (int j=0; j<2; j++) {
      if (!swap) ordered_points[i][j] = points[i][j];
      else ordered_points[i][j] = points[!i][j];
    } }
    
    int distance[2] = { ordered_points[1][0] - ordered_points[0][0], ordered_points[1][1] - ordered_points[0][1] };
    
    int fast_direction;
    if (distance[1] > 0) fast_direction = distance[1] > distance[0];
    else fast_direction = (-distance[1]) > distance[0];

    int special[2] = { distance[1] < 0 && fast_direction, distance[1] < 0 && !fast_direction };
    int location[2] = { ordered_points[0][0], ordered_points[0][1] };

    int error = distance[fast_direction]/2;
    if (special[0]) error = -error;

    while (location[fast_direction] != ordered_points[1][fast_direction]) {
        if (special[0]) location[fast_direction]--;
        else location[fast_direction]++;

        error -= distance[!fast_direction];

        if (error < 0 || (error > distance[fast_direction] && special[1])) {
            if (special[1]) location[!fast_direction]--;
            else location[!fast_direction]++;
            
            if (special[0] || special[1]) error -= distance[fast_direction];
            else error += distance[fast_direction];
        }

        pixel_info[location[0]][location[1]] = TRUE;
    }
    
}


void fill_symmetric_circle(int (*pixel_info)[BOARD_SIZE], int location[2], int origin[2]) {
    int tests[8] = { location[0]+origin[0], -location[0]+origin[0], location[1]+origin[0], -location[1]+origin[0], location[1]+origin[1], -location[1]+origin[1], location[0]+origin[1], -location[0]+origin[1] };

    for (int i=0; i<8; i++) {
        if (tests[i] < 0 || tests[i] >= BOARD_SIZE) tests[i] = UNDEFINED;
    }

    if (tests[0] != UNDEFINED && tests[4] != UNDEFINED) pixel_info[tests[0]][tests[4]] = TRUE;
    if (tests[0] != UNDEFINED && tests[5] != UNDEFINED) pixel_info[tests[0]][tests[5]] = TRUE;
    if (tests[1] != UNDEFINED && tests[5] != UNDEFINED) pixel_info[tests[1]][tests[5]] = TRUE;
    if (tests[1] != UNDEFINED && tests[4] != UNDEFINED) pixel_info[tests[1]][tests[4]] = TRUE;
    if (tests[2] != UNDEFINED && tests[6] != UNDEFINED) pixel_info[tests[2]][tests[6]] = TRUE;
    if (tests[2] != UNDEFINED && tests[7] != UNDEFINED) pixel_info[tests[2]][tests[7]] = TRUE;
    if (tests[3] != UNDEFINED && tests[7] != UNDEFINED) pixel_info[tests[3]][tests[7]] = TRUE;
    if (tests[3] != UNDEFINED && tests[6] != UNDEFINED) pixel_info[tests[3]][tests[6]] = TRUE;
}

void generate_circle(int (*pixel_info)[BOARD_SIZE], int (*points)[2]) {
    pixel_info[points[1][0]][points[1][1]] = FALSE;
    pixel_info[points[0][0]][points[0][1]] = FALSE;
    
    int distance[2] = { points[1][0] - points[0][0], points[1][1] - points[0][1] };
    int radius = (int) sqrt(pow(distance[0], 2) + pow(distance[1], 2));

    int location[2] = { 0, radius };
    int error = 3-(2*radius);

    int origin[2] = { points[0][0], points[0][1] };
    fill_symmetric_circle(pixel_info, location, origin);

    while (location[0] <= location[1]) {
        if (error <= 0) { error += (4*location[0])+6; }
        else {
            error += (4*location[0])-(4*location[1])+10;
            location[1]--;
        }

        location[0]++;
        fill_symmetric_circle(pixel_info, location, origin);
    }
}


void generate_triangle(int (*pixel_info)[BOARD_SIZE], int (*points)[2]) {
    generate_line(pixel_info, (int[2][2]){ { points[0][0], points[0][1] }, { points[1][0], points[1][1] } });
    generate_line(pixel_info, (int[2][2]){ { points[0][0], points[0][1] }, { points[2][0], points[2][1] } });
    generate_line(pixel_info, (int[2][2]){ { points[1][0], points[1][1] }, { points[2][0], points[2][1] } });
}


void generate_square(int (*pixel_info)[BOARD_SIZE], int (*points)[2]) {
    int distances[2][2];

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            distances[i][j] = points[2][j] - points[i][j];
        }
    }

    int distance[2] = { sqrt(pow(distances[0][0], 2) + pow(distances[0][1], 2)), sqrt(pow(distances[1][0], 2) + pow(distances[1][1], 2)) };

    int lowest_distance_point = 0;
    if (distance[1] < distance[0]) lowest_distance_point = 1;

    int next_point[2] = {
        points[!lowest_distance_point][0] + distances[lowest_distance_point][0],
        points[!lowest_distance_point][1] + distances[lowest_distance_point][1]
    };

    generate_line(pixel_info, (int[2][2]){ { points[0][0], points[0][1] }, { points[1][0], points[1][1] } });
    generate_line(pixel_info, (int[2][2]){ { points[2][0], points[2][1] }, { points[lowest_distance_point][0], points[lowest_distance_point][1] } });
    generate_line(pixel_info, (int[2][2]){ { points[!lowest_distance_point][0], points[!lowest_distance_point][1] }, { next_point[0], next_point[1] } });
    generate_line(pixel_info, (int[2][2]){ { points[2][0], points[2][1] }, { next_point[0], next_point[1] } });
}