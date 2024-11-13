// Main entry point of the emulator, manages the emulation loop.

#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
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

    while (1)
    {
        // Execute a CPU cycle
        // Handle any pending interrupts
        // Update internal timers
        // Render the display (LCD)
        // Process user input events

        break; // To removed when required
    }

    // Free allocated memory
    free_memory();
    free_rom();
    return EXIT_SUCCESS;
}
