#include "constants.h"
#include "stdio.h"

void generate_line(int (*pixel_info)[BOARD_SIZE], int (*points)[2]) {
    int ordered_points[2][2];
    int swap = FALSE;

    swap = points[0][0] > points[1][0];

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