char* color_data;

void init_window(char* name){
    backend_init();
    get_terminal_size(&window_size_y, &window_size_x);

    window_buffer = allocate_memory(window_size_x*window_size_y);
    color_data = allocate_memory(window_size_x*window_size_y);
    
    if (!window_buffer) {
        //printtf("faled to allocate memory\n");
        //exit(1);
    }

    set_process_name(name);
}

void update(){
    clear();
    draw_buffer(window_buffer, window_size_x, window_size_y, color_data);
}

void fill_screen(char chare, char color){
    int i = 0;
    int final = window_size_x*window_size_y;

    while(i < final){
        window_buffer[i] = chare;
        color_data[i] = color;
        i++;
    }
}

void draw_char(char c, int x, int y, char color){
    if(x < window_size_x && x > 0){
        if(y < window_size_y && y > 0){
            window_buffer[window_size_x*y+x] = c;
            color_data[window_size_x*y+x] = color;
        }
    }
}

void draw_text(const char* text, int x, int y, char color){
    int inx = x;
    int charinc = 0;
    int max = x + (x - window_size_x);
    
    while(text[charinc] != '\0'){
        draw_char(text[charinc], inx, y, color);
        inx++;
        charinc++;
    }
}