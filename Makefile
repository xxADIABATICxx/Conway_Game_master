all:
	gcc -o main game_logic.c SDL_handler.c main.c -IC:\MinGW\include -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2