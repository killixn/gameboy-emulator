// Handles display, sound, and user input via the SDL library.

#include "sdl.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define SCALE_FACTOR 4

int sdl_init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "error: SDL could not initialize (%s)\n",
                SDL_GetError());
        return EXIT_FAILURE;
    }

    *window = SDL_CreateWindow("GameBoy Emulator by @killixn @twip4",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH * SCALE_FACTOR,
                               SCREEN_HEIGHT * SCALE_FACTOR, SDL_WINDOW_SHOWN);
    if (!*window)
    {
        fprintf(stderr, "error: window could not be created (%s)\n",
                SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer)
    {
        fprintf(stderr, "error: renderer could not be created (%s)\n",
                SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 0);

    return EXIT_SUCCESS;
}

void sdl_cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
