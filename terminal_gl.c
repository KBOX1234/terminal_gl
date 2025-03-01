char* color_data;

#define SSH_MODE 1
#define DEFAULT 0

struct flag* flags;
char flag_inc = 0;

int ms_sleep = 1000 / 60;


void add_flag(char flagC, int value){
    flag_inc++;
    struct flag* new_flag = (struct flag*)malloc((flag_inc+1)*sizeof(struct flag));
    memcpy(new_flag, flags, (flag_inc - 1) * sizeof(struct flag));
    free(flags);
    flags = new_flag;
    flags[flag_inc - 1].command = flagC;
    flags[flag_inc - 1].number = value;
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