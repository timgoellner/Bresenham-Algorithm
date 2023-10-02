#include <stdio.h>
#include <SDL3/SDL.h>
#include "constants.h"
#include "bresenham.c"

int running;
int last_frame;
SDL_Window *window;
SDL_Renderer *renderer;

int mode;

SDL_FRect pixels[BOARD_SIZE][BOARD_SIZE];
int pixel_info[BOARD_SIZE][BOARD_SIZE];

int pressed;
int reset;
int mouse_pos[2];

int active_point;
int points[2][2] = { { UNDEFINED, UNDEFINED }, { UNDEFINED, UNDEFINED } };


int initialize_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return FALSE;
    }

    window = SDL_CreateWindow("Line Algorythm", WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_BORDERLESS);
    if (!window) {
        fprintf(stderr, "Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, NULL, 0);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return FALSE;
    }

    return TRUE;
}

void setup() {
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            SDL_FRect newRect = { i*PIXEL_SIZE, j*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
            pixels[i][j] = newRect;

            pixel_info[i][j] = FALSE;
        }
    }
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_EVENT_QUIT:
            running = FALSE;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q) running = FALSE;
            if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_KP_ENTER) {
                mode = !mode;
                reset = TRUE;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                pressed = TRUE;
                mouse_pos[0] = (int)(event.button.x/PIXEL_SIZE);
                mouse_pos[1] = (int)(event.button.y/PIXEL_SIZE);
            } else if (event.button.button == SDL_BUTTON_RIGHT) reset = TRUE;
            break;
        default:
            break;
    }
}

void update() {
    int sleep_time = FRAME_TARGET - (SDL_GetTicks() - last_frame);
    if (sleep_time > 0 && sleep_time <= FRAME_TARGET) SDL_Delay(sleep_time);

    float delta_time = (SDL_GetTicks() - last_frame) / 1000.0f;
    last_frame = SDL_GetTicks();

    if (reset) {
        for (int i=0; i<2; i++) { for (int j=0; j<2; j++) { points[i][j] = UNDEFINED; } }
        for (int i=0; i<BOARD_SIZE; i++) { for (int j=0; j<BOARD_SIZE; j++) { pixel_info[i][j] = FALSE; }}

        mouse_pos[0] = UNDEFINED;
        mouse_pos[1] = UNDEFINED;

        active_point = FALSE;

        reset = FALSE;
    }

    if (!pressed || pixel_info[mouse_pos[0]][mouse_pos[1]] == TRUE) return;

    pressed = FALSE;

    points[active_point][0] = mouse_pos[0];
    points[active_point][1] = mouse_pos[1];

    active_point = !active_point;

    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if ((points[0][0] == i && points[0][1] == j) || (points[1][0] == i && points[1][1] == j)) pixel_info[i][j] = TRUE;
            else pixel_info[i][j] = FALSE;
        }
    }

    if (points[0][0] != UNDEFINED && points[1][0] != UNDEFINED) {
        if (mode) generate_line(pixel_info, points);
        else generate_circle(pixel_info, points);
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (pixel_info[i][j] == TRUE) SDL_RenderFillRect(renderer, &pixels[i][j]);
        }
    }

    SDL_RenderPresent(renderer);
}

void destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main(int argc, char **argv) {
    running = initialize_window();
    
    setup();

    while (running) {
        process_input();
        update();
        render();
    }

    destroy();

    return 0;
}