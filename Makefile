CC = gcc
CFLAGS = -Wvla -Wextra -Wall -Werror -g -fsanitize=address
SDLFLAGS = -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2
OBJ = src/main.c src/rom.c src/memory.c src/sdl.c src/cpu.c

all:
	$(CC) $(CFLAGS) $(SDLFLAGS) -o gameboy $(OBJ)

clean:
	rm -rf gameboy*
