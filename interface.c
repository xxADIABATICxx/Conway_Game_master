#include "interface.h"
#include <stdio.h>

void print_load_or_create()
{
    printf("Do you want to create a new map or load map from .txt file: \n");
    printf("Please make your choice (1 or 2): \n");
    printf("1. Create a new map. \n");
    printf("2. Load map from file. \n");
}

void print_auto_or_manual()
{
    printf("Do you want to create automatically or create manually: \n");
    printf("Please make your choice (1 or 2): \n");
    printf("1. Create automatically. \n");
    printf("2. Create manually. \n");
}

void print_if_terminate()
{
    printf("Do you want set specific number of steps,\n");
    printf("Or let the programm keeps evoving till it terminates?\n");
    printf("input [y] for setting the number of steps,\n");
    printf("Or [n] for keeping the programme evolving:\n");
}