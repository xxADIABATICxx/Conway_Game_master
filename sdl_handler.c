#include <SDL2/SDL.h>
#include <stdio.h>
#include "sdl_handler.h"
#include "game_logic.h"

SDL_Window *init_window(int map_w, int map_h)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "ERROR: failed SDL_Init : %s \n", SDL_GetError());
        exit(errno);
    }

    SDL_Window *win = SDL_CreateWindow(
        WIN_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        map_w * SIZE,
        map_h * SIZE,
        SDL_WINDOW_SHOWN);

    if (win == NULL)
    {
        fprintf(stderr, "ERROR: failed Create Window : %s \n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
    }

    return win;
}

SDL_Renderer *init_renderer(SDL_Window *win)
{
    Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, renderFlags);

    if (renderer == NULL)
    {
        fprintf(stderr, "ERROR: failed SDL_Init : %s \n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    return renderer;
}

void draw(SDL_Renderer *renderer, int **map, int map_w, int map_h)
{
    for (int i = 0; i < map_h; i++)
    {
        for (int j = 0; j < map_w; j++)
        {
            if (map[i][j])
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            else
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_Rect rect = {j * SIZE + BORDER, i * SIZE + BORDER, CELL, CELL};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void print_SDL(int **map, int map_w, int map_h, int num_gen)
{
    SDL_Window *window = init_window(map_w, map_h);
    SDL_Renderer *renderer = init_renderer(window);

    SDL_Event event;
    int quit = 0;
    int pause = 1;
    int mouseDownLeft = 0;
    int mouseDownRight = 0;
    int generation = 0;
    unsigned long int frame_start, frame_time;

    while (!quit)
    {
        frame_start = SDL_GetTicks();
        frame_time = SDL_GetTicks() - frame_start;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                case SDLK_q:
                    quit = 1;
                    break;
                case SDLK_p:
                    pause = !pause;
                    break;
                case SDLK_SPACE:
                    pause = !pause;
                    break;
                case SDLK_DOWN:
                    frame_time <<= 1;
                    if (frame_time > 500)
                        frame_time = 500;
                    break;
                case SDLK_UP:
                    frame_time >>= 1;
                    if (frame_time < 1)
                        frame_time = 1;
                    break;
                case SDLK_s:
                    save_map(map, map_w, map_h);
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouseDownLeft = 1;
                if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseDownRight = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouseDownLeft = 0;
                if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseDownRight = 0;
                break;
            case SDL_MOUSEMOTION:
            {
                int x_ = event.button.x / SIZE;
                int y_ = event.button.y / SIZE;
                if (x_ < map_h && y_ < map_w)
                {
                    if (mouseDownLeft)
                    {
                        map[y_][x_] = 1;
                    }
                    else if (mouseDownRight)
                    {
                        map[y_][x_] = 0;
                    }
                }
                break;
            }
            }
        }

        if (!pause && generation <= num_gen)
        {
            update_map(map, map_w, map_h);
            generation++;
        }
        else
        {
            SDL_Delay(1);
        }

        SDL_SetRenderDrawColor(renderer, 0x40, 0x40, 0x40, 0xFF);
        SDL_RenderClear(renderer);
        draw(renderer, map, map_w, map_h);
        SDL_RenderCopy(renderer, NULL, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(2500 / FPS - frame_time);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    free_map(map, map_h);
    SDL_Quit();
}