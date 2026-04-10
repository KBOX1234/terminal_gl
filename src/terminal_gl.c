#include "../include/terminal_gl.h"

#include <stdlib.h>
#include <string.h>

//buffer to write to
char* window_buffer = NULL;

//global variables to store the size of the terminal window
int window_size_x, window_size_y;

char* color_data = NULL;

#define SSH_MODE 1
#define DEFAULT 0

struct flag* flags = NULL;
unsigned char flag_inc = 0;

int ms_sleep = 1000 / 60;


void add_flag(char flagC, int value){
    if(flag_inc == 255) return;

    size_t modern_size = (flag_inc + 1) * sizeof(struct flag);

    struct flag* tmp = malloc(modern_size);
    memset(tmp, 0, modern_size);
    memcpy(tmp, flags, flag_inc *sizeof(struct flag));

    free(flags);

    flags = tmp;

    tmp[flag_inc].command = flagC;
    tmp[flag_inc].number = value;

    flag_inc++;
    
}

void scan_flags(){
    int inc = 0;

    while(inc < flag_inc){
        if(flags[inc].command == SSH_MODE){
            ms_sleep = 1000 / 4;
        }
        inc++;
    }
}

void init_window(const char* name){
    backend_init();
    

    get_terminal_size(&window_size_y, &window_size_x);

    scan_flags();

    window_buffer = (char*)allocate_memory(window_size_x*window_size_y);
    color_data = (char*)allocate_memory(window_size_x*window_size_y);
    
    if (!window_buffer) {
        //printtf("faled to allocate memory\n");
        //exit(1);
    }

    set_process_name(name);
}

void update(){
    draw_buffer(window_buffer, window_size_x, window_size_y, color_data);
}

void fill_screen(char chare, char color){
    int final = window_size_x*window_size_y;

    memset(window_buffer, chare, final);
    memset(color_data, color, final);
}

void draw_char(char c, int x, int y, char color){
    if(x < window_size_x && x >= 0){
        if(y < window_size_y && y >= 0){
            window_buffer[window_size_x*y+x] = c;
            color_data[window_size_x*y+x] = color;
        }
    }
}

void draw_text(const char* text, int x, int y, char color){
    int inx = x;
    int charinc = 0;
    
    while(text[charinc] != '\0'){
        draw_char(text[charinc], inx, y, color);
        inx++;
        charinc++;
    }
}
