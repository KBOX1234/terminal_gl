#include "impl/impl.h"

//buffer to write to
char* window_buffer;
int window_size_x, window_size_y;

//init

void init_window(char* name);

void draw_char(char c, int x, int y, char color);

void update();

void fill_screen(char chare, char color);

void draw_text(const char* text, int x, int y, char color);

void draw_rectangle(char fill, int pos_x, int pos_y, int size_x, int size_y, char color);

#include "terminal_gl.c"
