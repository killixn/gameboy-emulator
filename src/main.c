// Main entry point of the emulator, manages the emulation loop.

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "rom.h"
#include "sdl.h"

int main(int argc, char *argv[])
{
    int error_occur = 0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Check args
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s [-D] <path_to_rom>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Load the ROM file into memory
    error_occur = rom_load(argv[1]);
    if (error_occur)
    {
        fprintf(stderr, "error: %s: unable to load ROM\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("\nROM successfully loaded\n");

    // Initialize memory components (VRAM, RAM, etc)
    error_occur = memory_init();
    if (error_occur)
    {
        fprintf(stderr, "error: %s: unable to initialize memory\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("\nMemory successfully initialized\n");

    error_occur = sdl_init(&window, &renderer);
    if (error_occur)
    {
        fprintf(stderr, "error: %s: unable to initialize SDL\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("\nSDL successfully initialized\n");

    // Main loop
    int quit = 0;
    SDL_Event event;
    while (!quit)
    {
        // Execute a CPU cycle
        // Handle any pending interrupts
        // Update internal timers
        // Render the display (LCD)
        // Process user input events

        // Handle events
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = 1;
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
            }
        }

        SDL_RenderClear(renderer); // Clear the screen
        SDL_RenderPresent(renderer); // Update the screen

        SDL_Delay(16); // Frame delay (~60 FPS)
    }

    // Clean up resources
    free_memory();
    free_rom();
    sdl_cleanup(window, renderer);
    return EXIT_SUCCESS;
}
