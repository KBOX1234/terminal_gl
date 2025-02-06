void init_window(char* name){
    get_terminal_size(&window_size_y, &window_size_x);

    window_buffer = allocate_memory(window_size_x*window_size_y);

    if (!window_buffer) {
        printf("faled to allocate memory\n");
        exit(1);
    }

    set_process_name(name);
}

void update(){
    clear();
    draw_buffer(window_buffer, window_size_x, window_size_y);
}

void fill_screen(char chare){
    int i = 0;
    int final = window_size_x*window_size_y;

    while(i < final){
        window_buffer[i] = chare;
        i++;
    }
}

void draw_char(char c, int x, int y){
    window_buffer[window_size_x*y+x] = c;
}

void draw_text(const char* text, int x, int y){
    int inx = x;
    int charinc = 0;
    int max = x + (x - window_size_x);
    
    while(text[charinc] != '\0'){
        draw_char(text[charinc], inx, y);
        inx++;
        charinc++;
    }
}

void draw_rectangle(char fill, int pos_x, int pos_y, int size_x, int size_y){
    int pointer_x = pos_x;
    int pointer_y = pos_y;

    while(pointer_x < pos_x + size_x){
        while(pointer_y < pos_y + size_y){
            draw_char(fill, pointer_x, pointer_y);
            pointer_y++;
        }
        pointer_y = pos_y;
        pointer_x++;
    }
}
