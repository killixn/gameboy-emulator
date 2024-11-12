// Main entry point of the emulator, manages the emulation loop.

#include <stdio.h>
#include <stdlib.h>

#include "rom.h"

int main(int argc, char *argv[])
{
    int error_occur = 0;

    // Check args
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s [-D] <path_to_rom>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize components: CPU, memory, display (LCD), ROM, etc
    error_occur = rom_load(argv[1]);
    if (error_occur)
    {
        fprintf(stderr, "error: %s: unable to load ROM\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("\nROM successfully loaded\n");

    while (1)
    {
        // CPU cycle
        // Handle interrupts
        // Update timers
        // Render display
        // Process user input
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
