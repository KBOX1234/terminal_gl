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