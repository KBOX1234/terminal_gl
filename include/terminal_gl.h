#ifndef TERMINAL_GL_H
#define TERMINAL_GL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

//buffer to write to
extern char* window_buffer;

//global variables to store the size of the terminal window
extern int window_size_x, window_size_y;

extern int ms_sleep;

//struct for text images (text sprites)
struct text_image{
    //color data
    char* color_data;
    //text data
    char* buffer_data;
    //width 
    int x;
    //height
    int y;
};

struct flag{
    char command;
    int number;
};

void add_flag(char flagC, int value);
//init the window
void init_window(const char* name);

//draw a char to the screen
void draw_char(char c, int x, int y, char color);

//updates the screen buffer from the window buffer
void update();

//fills the screen with a char and a color
void fill_screen(char chare, char color);

//draws text to the screen
void draw_text(const char* text, int x, int y, char color);

//draws a rectangle to the screen
void draw_rectangle(char fill, int pos_x, int pos_y, int size_x, int size_y, char color);

//draws a line to the screen
void draw_line(char fill, int pos_x_1, int pos_y_1, int pos_x_2, int pos_y_2, char color);

//if IMG_LOADING is defined then you can load images
//NOTE: you will need a file system for loading images from.
#ifdef IMG_LOADING

//load an image into a text_image
struct text_image load_image_to_text(const char* file, char fill);

//loads a char buffer from disk
struct text_image load_buffer(const char* name);

//draw text image
void render_text_image(struct text_image img, int pos_x, int pos_y, char normal_pixel_ratio);

#endif

//internal functions for interfacing with each backend
//note: for users wanting to create there own backend, you will need to write implementations for each of these functions


void *allocate_memory(size_t size);

void draw_buffer(char* buffer, int x, int y, char* color_data);

void get_terminal_size(int *rows, int *cols);

void set_process_name(const char *name);

void clear();

void hide_cursor();

void backend_init();

void scan_input();

char is_key_pressed(char key);

#ifdef __cplusplus
}
#endif

#endif
