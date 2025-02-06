#include <stdio.h>
#include <stdlib.h>

#include "terminal_gl.h"
#include "impl/backend_linux.c"


int main(){

    init_window("test program");
    fill_screen(' ', 0);
    draw_char('&', 1, 1, 0x05);
    //hide_cursor();
    draw_text("hello world", 20, 20, 0x05);
    
    draw_rectangle('#', 30, 30, 6, 6, 0x75);
    while(1){
        update();
        //printf("%d\n", window_size_y);
    }

    sys_exit(0);
}
