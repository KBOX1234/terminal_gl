#include <stdio.h>
#include <stdlib.h>

#include "terminal_gl.h"
#include "impl/backend_linux.c"


int main(){

    init_window("test program");
    fill_screen('*');
    draw_char('&', 20, 20);
    //hide_cursor();

    while(1){
        update();
    }

    sys_exit(0);
}