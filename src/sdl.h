#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>

int sdl_init(SDL_Window **window, SDL_Renderer **renderer);
void sdl_cleanup(SDL_Window *window, SDL_Renderer *renderer);

#endif /* !SDL_H */
