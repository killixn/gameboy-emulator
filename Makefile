CC = gcc
CFLAGS = -Wvla -Wextra -Wall -Werror -g -fsanitize=address
OBJ = src/main.c

all:
	$(CC) $(CFLAGS) -o GameBoy $(OBJ)

clean:
	rm -rf GameBoy*
