#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game_logic.h"
#include "sdl_handler.h"
#include "interface.h"

#undef main

int main(int argc, char **argv)
{
    int choice = 0;
    char select;
    int map_width = 10;  // default map width
    int map_height = 10; // defatult map height
    int num_gen = 0; // default evoving generation
    int **g_map;

    print_if_terminate();
    if ((select = getchar()) == 'y')
    {
        printf("Please input the number of generations:\n");
        scanf("%d", &num_gen);
    }
    else
    {
        num_gen = 10000;
        printf("The programme will keep evolving.\n");
    }

// --------------------------------------------------------

    print_load_or_create();
    scanf("%d", &choice);

    if (choice == 1)    // create map
    {
        print_auto_or_manual();
        scanf("%d", &choice);

        if (choice == 1)    // create automatically
        {
            printf("Please input the width of the map: \n");
            scanf("%d", &map_width);
            printf("Please input the height of the map: \n");
            scanf("%d", &map_height);
            g_map = init_rand_map(map_width, map_height);
            print_SDL(g_map, map_width, map_height, num_gen);
        }
        else if (choice == 2)   // create manually
        {
            printf("Please input the width of the map: \n");
            scanf("%d", &map_width);
            printf("Please input the height of the map: \n");
            scanf("%d", &map_height);
            g_map = init_map(map_width, map_height);
            print_SDL(g_map, map_width, map_height, num_gen);
        }
        else
        {
            printf("Invalid input, programme terminate.\n");
        }
    }
    else if (choice == 2)   // load map
    {
        g_map = load_map(&map_width, &map_height);
        print_SDL(g_map, map_width, map_height, num_gen);
    }
    else
    {
        printf("Invalid input, programme terminate.\n");
        return 0;
    }

    return 0;
}