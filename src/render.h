#ifndef RENDER_H
#define RENDER_H 

#include <cstdint>

const int WIDTH = 1000;
const int HEIGHT = 800;
const int POINT_RADIUS = 8;

struct Color {
    uint8_t r, g, b, a;
};

const Color WHITE = { 255, 255, 255, 0 };
const Color BLACK = { 0, 0, 0, 0 };
const Color RED = { 255, 0, 0, 0 };
const Color GREEN = { 0, 255, 0, 0 };
const Color BLUE = { 0, 0, 255, 0 };

void open_window();

bool should_close_window();

void begin_render();

void draw_point(int x, int y, const Color& c);

void end_render();

void close_window();

#endif /* RENDER_H */
