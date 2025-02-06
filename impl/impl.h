//internal functions for interfacing with each backend
//note: for users wanting to create there own backend, you will need to write implementations for each of these functions


void *allocate_memory(long size);

void draw_buffer(char* buffer, int x, int y, char* color_data);

void get_terminal_size(int *rows, int *cols);

void set_process_name(char *name);

void clear();

void hide_cursor();

void backend_init();

void scan_input();

char is_key_pressed(char key);