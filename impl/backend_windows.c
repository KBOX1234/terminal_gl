#include <windows.h>

void *allocate_memory(long size){
    return malloc(size);
}
void draw_buffer(char* buffer, int x, int y, char* color_data){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char inc = 0;
    char x_inc = 0;
    char y_inc = 0;

    while(y_inc < y){
        while(x_inc < x){
            SetConsoleTextAttribute(hConsole, color_data[inc]);
            DWORD written;
            WriteConsole(hConsole, &buffer[inc], lstrlenA(text), &written, NULL);
            x_inc++;
            inc++;
        }
        WriteConsole(hConsole, '\n', lstrlenA(text), &written, NULL);
        x_inc = 0;
        y_inc++;
        
    }
}

void get_terminal_size(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        *cols = 0; // Error case
        *rows = 0;
    }
}

void set_process_name(char *name){
    SetConsoleTitle(name);
}

void clear(){
    system("cls");
}

void hide_cursor(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo); // Get current cursor info
    cursorInfo.bVisible = FALSE; // Hide the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void backend_init();