#include <stdio.h>
#include <stdlib.h>

#include "terminal_gl.h"
#include "impl/backend_linux.c"


int main(){

    init_window("test program");

    int xi = 2;
    while(1){
        fill_screen(' ', 0);
        draw_char('&', 1, 1, 0x05);
        //hide_cursor();
        draw_text("hello world", 20, 20, 0x05);
        
        draw_rectangle('#', xi, 30, 6, 6, 0x75);
        xi++;

        update();
    }

    sys_exit(0);
}
