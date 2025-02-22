#include <stdio.h>
#include <stdlib.h>

#define IMG_LOADING

#include "terminal_gl.h"
#include "impl/backend_linux.c"


int main(){

    //add_flag(SSH_MODE, 1);

    init_window("test program");

    int xi = 2;
    int yi = 2;
    

    struct text_image smile = load_image_to_text("test.png", '#');
    struct text_image text_buff2 = load_buffer("test.txt");
    while(1){
        fill_screen(' ', 0);
        draw_char('&', 1, 1, 0x05);

        render_text_image(smile, xi, yi, 1);
        render_text_image(text_buff2, 10, 10, 0);
        //hide_cursor();
        draw_text("hello world", 20, 20, 0x05);
        
        //draw_rectangle('#', xi, yi, 6, 6, 0x75);

        draw_line('%', 1, 1, 1, 30, 0x10);
        scan_input();

        if(is_key_pressed('a') == 1){
            xi = xi - 2;
        }
        if(is_key_pressed('d') == 1){
            xi = xi + 2;
        }
        if(is_key_pressed('w') == 1){
            yi--;
        }
        if(is_key_pressed('s') == 1){
            yi++;
        }

        update();
    }

    return 0;
}
