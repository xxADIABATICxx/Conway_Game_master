main: main.c game_logic.c
	gcc -o main main.c game_logic.c sdl_handler.c interface.c -lSDL2 -lSDL2main