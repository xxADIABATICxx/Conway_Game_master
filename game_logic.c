#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_logic.h"

int **init_map(int width, int height)
{
	int **map = (int **)malloc(sizeof(int *) * (height));
	for (int i = 0; i < height; i++)
	{
		map[i] = (int *)malloc(sizeof(int) * (width));
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			map[i][j] = 0;
		}
	}
	return map;
}

int **init_rand_map(int width, int height)
{
	srand((unsigned)time(NULL));

	int **map = (int **)malloc(sizeof(int *) * (height));
	for (int i = 0; i < height; i++)
	{
		map[i] = (int *)malloc(sizeof(int) * (width));
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			map[i][j] = rand() % 2;
		}
	}
	return map;
}

void print_map(int **map, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%d", map[i][j]);
		}
		puts("");
	}
}

void free_map(int **map, int height)
{
	for (int i = 0; i < height; i++)
	{
		free(map[i]);
	}
	free(map);
}

int save_map(int **map, int width, int height)
{
	FILE *fp;

	if ((fp = fopen("map.txt", "w")) == NULL)
	{
		perror("fopen error");
		return -1;
	}
	// save width and height
	fprintf(fp, "%d\t%d\n", width, height);
	// save map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fprintf(fp, "%d", map[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("Successfully saved!\n");
	return 1;
}

int **load_map(int *width, int *height)
{
	FILE *fp;

	if ((fp = fopen("map.txt", "r")) == NULL)
	{
		perror("fopen error");
	}

	fscanf(fp, "%d\t%d", width, height);
	fgetc(fp); // remove "\n"

	int **map = init_map(*width, *height);

	for (int i = 0; i < *height; i++)
	{
		for (int j = 0; j < *width; j++)
		{
			map[i][j] = fgetc(fp) - '0';
			// printf("%d", map[i][j]);
		}
		fgetc(fp); // remove "\n"
				   // printf("\n");
	}
	fclose(fp);

	// print_map(map, width, height);
	return map;
}

int count_cell(int **map, int width, int height, int y, int x)
{
	int count = 0; // a counter for counting how much neighbor cell is full

	for (int i = -1; i <= 1; i++) //for checking neighbours (x-1 ,y) (x,y) (x+1,y)
	{
		for (int j = -1; j <= 1; j++) //for checking neighbours (x,y+1) (x,y) (x,y+1)
		{
			int neigh_H = x + i;
			int neigh_W = y + j;

			//cases when neighbours can't found
			if (neigh_W < 0 || neigh_H < 0 || neigh_W >= width || neigh_H >= height)
			{
				continue;
			}

			//case when neighbor's coordinates equals the cells itself
			else if (neigh_H == x && neigh_W == y)
			{
				continue;
			}

			//case when neighbor is full and count increments by 1
			else if (map[neigh_H][neigh_W] == 1)
			{
				count++;
			}
		}
	}

	return count;
}

int **update_map(int **map, int width, int height)
{
	int **next_map;
	next_map = (int **)malloc(sizeof(int *) * height);
	for (int i = 0; i < height; i++)
	{
		next_map[i] = (int *)malloc(sizeof(int) * width);
	}
	// calculate the neibor of each cell in previous map and store the count in next map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			next_map[i][j] = count_cell(map, width, height, j, i);

			if (next_map[i][j] == 3)
			{
				next_map[i][j] = 1;
			}
			else if (next_map[i][j] == 2)
			{
				if (map[i][j] == 1)
				{
					next_map[i][j] = 1;
				}
				else
				{
					next_map[i][j] = 0;
				}
			}
			else
			{
				next_map[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			map[i][j] = next_map[i][j];
		}
	}

	free_map(next_map, height);
	return map;
}