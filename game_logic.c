#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "SDL_handler.h"
#include "game_logic.h"


void update(screen_t* screen)
{
	#pragma omp parallel for
	for (int x = 0; x < screen->W; x++) {
		for (int y = 0; y < screen->H; y++) {
			int n = 0;	// Number of neighbours
			int to_iterate[8][2] = {
				{ x-1 , y+1 },
				{ x   , y+1 },
				{ x+1 , y+1 },
				{ x-1 , y   },
				{ x+1 , y   },
				{ x-1 , y-1 },
				{ x   , y-1 },
				{ x+1 , y-1 }
			};
			for (int i = 0; i < 8; i++) {
				if (to_iterate[i][0] >= 0 && to_iterate[i][0] < screen->W
					&& to_iterate[i][1] >= 0 && to_iterate[i][1] < screen->H
					&& screen->pixels[to_iterate[i][0]][to_iterate[i][1]] == 1)
				{
					n++;
				}
			}
			if (screen->pixels[x][y]) {
				screen->pixels_next[x][y] = (n == 2) || (n == 3);
			}
			else {
				screen->pixels_next[x][y] = (n == 3);
			}
		}
	}
	#pragma omp parallel for
	for (int x = 0; x < screen->W; x++)	{	// Copy temp data to real pointer (used on draw())
		memcpy(screen->pixels[x], screen->pixels_next[x], screen->H * sizeof(unsigned char));
	}
}


void draw(screen_t* screen, SDL_Renderer* renderer)
{
	for (int x = 0; x < screen->W; x++) {
		for (int y = 0; y < screen->H; y++) {
			if (screen->pixels[x][y]) {
				SDL_Rect rect;
				rect.x = x * screen->point_size;
				rect.y = y * screen->point_size;
				rect.w = screen->point_size;
				rect.h = screen->point_size;
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}