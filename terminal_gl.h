#include "impl/impl.h"

//buffer to write to
char* window_buffer;

//global variables to store the size of the terminal window
int window_size_x, window_size_y;


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


//init the window
void init_window(char* name);

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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//load an image into a text_image
struct text_image load_image_to_text(const char* file, char fill);

//loads a char buffer from disk
struct text_image load_buffer(const char* name);

//draw text image
void render_text_image(struct text_image img, int pos_x, int pos_y, char normal_pixel_ratio);

#include "include/image.c"

#endif

#include "terminal_gl.c"
#include "include/shapes.c"

