#ifndef GAME_LOGIC_GUARD_H
#define GAME_LOGIC_GUARD_H

int **init_map(int width, int height);

int **init_rand_map(int width, int height);

int save_map(int **map, int width, int height);

int **load_map(int *width, int *height);

int count_cell(int **map, int width, int height, int x, int y);

int **update_map(int **map, int width, int height);

void print_map(int **map, int width, int height);

void free_map(int **map, int height);

#endif