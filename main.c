#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "SDL_handler.h"
#include "game_logic.h"

#define TITLE "Conway's game of life"

int main(int argc, char** argv)		// Inizialize all values
{
	SDL_Init(SDL_INIT_VIDEO);

	screen_t* screen = init_game(argc, argv);

	SDL_Window* win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										screen->W * screen->point_size, screen->H * screen->point_size, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event event;

	if (argc < 3 || (argv[1][0] == '.' && argv[2][0] == '.'))
		SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);

	unsigned char quit = 0, pause = 0, mouseDownLeft = 0, mouseDownRight = 0, gen_count = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							quit = 1;
							break;
						case SDLK_p:
							pause = !pause;
							break;
						case SDLK_DOWN:
							screen->delay <<= 1;
							if (screen->delay > 500) screen->delay = 500;
							break;
						case SDLK_UP:
							screen->delay >>= 1;
							if (screen->delay < 1) screen->delay = 1;
							break;
					}
					break;						
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) mouseDownLeft = 1;
					if (event.button.button == SDL_BUTTON_RIGHT) mouseDownRight = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) mouseDownLeft = 0;
					if (event.button.button == SDL_BUTTON_RIGHT) mouseDownRight = 0;
					break;
				case SDL_MOUSEMOTION: {
					int x_ = event.button.x / screen->point_size;
					int y_ = event.button.y / screen->point_size;
					if (x_ < screen->W && y_ < screen->H) {
						if (mouseDownLeft) {
							screen->pixels[x_][y_] = 1;
						}
						else if (mouseDownRight) {
							screen->pixels[x_][y_] = 0;
						}
					}
					break;
				}
			}
		}
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);		// Set color = white
		if (!pause && gen_count <= screen->gen_max) {
			update(screen);
			gen_count++;
		}
		else {
			SDL_Delay(1);
		}
		draw(screen, renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);			// Reset color to black
		SDL_RenderPresent(renderer);
		if(screen->sp == 0){
			pause;
		}
		if (pause) {
			SDL_Delay(1);
		}
		else {
			SDL_Delay(screen->delay);
		}
	}

	end_game(screen);			// Free all screen allocations
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}