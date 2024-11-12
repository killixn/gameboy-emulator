CC = gcc
CFLAGS = -Wvla -Wextra -Wall -Werror -g -fsanitize=address
OBJ = src/main.c src/rom.c src/memory.c

all:
	$(CC) $(CFLAGS) -o gameboy $(OBJ)

clean:
	rm -rf gameboy*
