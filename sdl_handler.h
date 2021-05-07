#ifndef SDL_HANDLER_GUARD_H
#define SDL_HANDLER_GUARD_H

#include <SDL2/SDL.h>
#include "game_logic.h"

#define WIN_TITLE "Game of Life"
#define WIN_WIDTH 40
#define WIN_HEIGHT 40


#define BORDER 1
#define CELL 25
#define SIZE (2 * BORDER + CELL)
#define FPS 60

SDL_Window *init_window();

SDL_Renderer *init_renderer(SDL_Window *win);

void draw(SDL_Renderer *renderer, int **map, int map_w, int map_h);

void print_SDL(int **map, int map_w, int map_h, int num_gen);

#endif