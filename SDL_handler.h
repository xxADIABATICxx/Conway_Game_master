#ifndef SDL_HANDLER_H
#define SDL_HANDLER_H

#include <SDL2/SDL.h>

typedef struct {
	unsigned char** pixels;			// Pixels dynamic array of arrays (Ex: pixels[500][500])
	unsigned char** pixels_next;	// A copy of pixels for update() blocks
	int W, H;						// With, Height
	SDL_DisplayMode info;			// Screen info: Freq, width, height
	int delay;						// SDL Delay
	int sp;							// Block spawn probability (x / 100) 
	int point_size;					// Cell size in pixels
} screen_t;

// Use time.h and g_seed to generate random live cells on the grid board
unsigned int rand_range(const unsigned int min, const unsigned int max);

// pass arguments to initialize parameters and the grid board
screen_t* init_game(int argc, char** argv);

// to free the memory allocated and quit the game immediately without saving
void end_game(screen_t* screen);

#endif