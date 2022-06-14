#include "render.h"

#include <SDL2/SDL.h>

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;

bool closed = false;

void set_color(const Color& c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void open_window() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

bool should_close_window() {
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                closed = true;
                break;
            default: break;
        }
    }

    return closed;
}

void begin_render() {
    set_color(BLACK);
    SDL_RenderClear(renderer);
}

void draw_point(int x, int y, const Color& c) {
    set_color(c);
    SDL_Rect rect = { x-POINT_RADIUS, y-POINT_RADIUS, 2*POINT_RADIUS, 2*POINT_RADIUS };
    SDL_RenderFillRect(renderer, &rect);
}

void end_render() {
    SDL_RenderPresent(renderer);
}

void close_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
