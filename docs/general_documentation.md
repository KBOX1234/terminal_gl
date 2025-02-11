# Documentaion of function

## Table of contents
- Structures
- Base library functions
- IMG_LOADING enabled functions

## Structures
The buffer that stores all the window data:
```c
char* window_buffer;
````

Global variables that store the size of the screen:
```c
int window_size_x, window_size_y;
```

Data structure for storing ascii images:
```c
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
```

Data structure for storing program flags:
```c
struct flag{
    //type of flag
    char command;
    //any number attributable
    int number;
};
```

## Base library functions

Function for setting a program flag:
```c
void add_flag(char flagC, int value);
```
add_flag takes 2 arguments. The first one (char flagC) is the flag and int value is any value that could be given to the flag (such as add_flag(FPS, 60)).

Function for initilising the program:
```c
void init_window(char* name);
```
This function is needed to be able to properly start termina_gl. It takes 1 argument wich is the name of the window. 

Function for plotting a char to the terminal:
```c
void draw_char(char c, int x, int y, char color);
```
This function takes 4 arguments. Char c accepts the char that you want to draw, int x and int y take the X and Y coordinates of the screen that are to be drawn on, and char color takes a [VGA color code](https://www.fountainware.com/EXPL/vga_color_palettes.htm) as its color.

Function for updating the screen:
```c
void update();
```
This function needs to be called every time the program wants to update the screen. It takes no arguments and has the responsibility to render all the data storred in the window buffer to the screen.

Function for clearing/filling the screen:
```c
void fill_screen(char chare, char color);
```
This function takes 2 arguments. The first one is char chare which takes the charecture that you want to fill the screen with. The last one is the char color and it takes a [VGA color code](https://www.fountainware.com/EXPL/vga_color_palettes.htm) as the color to fill the screen whith.

Function for drawing text:
```c
void draw_text(const char* text, int x, int y, char color);
```
This function can draw text to the screen. It takes 4 arguments. The first is const char* text which is the text that will be drawn. The second and third are int x and int y and they determin the where the string will start being drawn. Last, we have char color which takes a [VGA color code](https://www.fountainware.com/EXPL/vga_color_palettes.htm) for the color.

### Shape drawing (still in base library)
Function for drawing a rectangle:
```c
void draw_rectangle(char fill, int pos_x, int pos_y, int size_x, int size_y, char color);
```
This function draws a rectangle on screen. It takes 6 arguments. Char fill takes the charecture you want to fill the rectangle with, int pos_x and int pos_y take the X and Y coords of where it should be drawn, int size_x and int size_y gets the size of the rectangle, and char color gets the [VGA color code](https://www.fountainware.com/EXPL/vga_color_palettes.htm) to draw the rectangle with.

Function for drawing lines:
```c
void draw_line(char fill, int pos_x_1, int pos_y_1, int pos_x_2, int pos_y_2, char color);
```
This function draws lines and takes 6 arguments. Char fill is for filling the drawn space in with a selected charecture, int pos_x_1 and int pos_y_1 are the starting coordinates of the line, int pos_x_2 and int pos_y_2 are the ending coordinates of the line, and char color takes a [VGA color code](https://www.fountainware.com/EXPL/vga_color_palettes.htm) as its color.

## IMG_LOADING enabled functions
Function for loading an image from disk:
```c
struct text_image load_image_to_text(const char* file, char fill);
```
This function takes 2 arguments. Const char* file is the file name that you want to load and char fill is the charecture used to fill the image. This function returns a struct text_image containing the image data.

Function for loading text_images from disk:
```c
struct text_image load_buffer(const char* name);
```
This function is like the previus function but loads a text file as an image instead. This allows you to have control of the text charectures inside the text_image therfor, only the file name needs to be passed. This function returns a struct text_image.

Function for rendering text_images:
```c
void render_text_image(struct text_image img, int pos_x, int pos_y, char normal_pixel_ratio);
```
This function renders text_images on screen and takes 4 arguments. Struct text_image_img takes the image to render. It is not a pointer as the struct text_image already has a pointer to the data. Int pos_x and int pos_y are the coordinates that the sprite will be drawn and char normal_pixel_ratio is a bool. When normal_pixel_ratio is set to 1 (true), then it will compensate for the 1:2 text aspect ratio, otherwise it will not compensate.