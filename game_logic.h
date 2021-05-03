#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include <SDL2/SDL.h>
#include "SDL_handler.h"

// Update the graphic grid board
void update(screen_t* screen);

// Draw the SDL window and redenr the screen
void draw(screen_t* screen, SDL_Renderer* renderer);

#endif