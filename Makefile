CC = gcc
CFLAGS = -Wvla -Wextra -Wall -Werror -g -fsanitize=address
SDLFLAGS = -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
OBJ = src/main.c src/rom.c src/memory.c src/sdl.c src/cpu.c src/instruct.c

all: gameboy

gameboy: $(OBJ)
	$(CC) $(CFLAGS) $(SDLFLAGS) -o gameboy $(OBJ)

debug: CFLAGS += -DDEBUG
debug: clean all

clean:
	rm -rf gameboy *.o src/*.o
