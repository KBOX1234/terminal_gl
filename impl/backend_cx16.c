#include <cx16.h>


#define HEAP_START ((volatile unsigned char*)0x0810)
#define HEAP_END ((volatile unsigned char*)0x9EFF)
#define HEAP_SIZE 0x96EF

#define TEXT_AREA 0x1B000
#define vera ((volatile unsigned char*)0x9F20)


short heap_inc;
char video_mode = 0;

void *allocate_memory(long size){
    if(heap_inc+size+(short)HEAP_START > (short)HEAP_END){
        return 0;
    }
    heap_inc = heap_inc + size;
    return (void*)&HEAP_START[heap_inc-size];
}

void draw_buffer(char* buffer, int x, int y, char* color_data){
    vera[0] = 0xB0;
    vera[1] = 0x00;
    vera[2] = 0b01000001;

    short inc2 = 0;
    short end2 = 80*60;

    while(inc < end){
        VERA[4] = buffer[inc];
        inc++;
    }
}

void get_terminal_size(int *rows, int *cols){
    *rows = 80;
    *cols = 60;
}

void set_process_name(char *name){

}

void clear(){

}

void hide_cursor(){

}

void backend_init(){
    videomode(video_mode);
}

void scan_input(){

}

char is_key_pressed(char key){

}