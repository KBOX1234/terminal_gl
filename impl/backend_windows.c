#include <windows.h>

void *allocate_memory(long size){
    return malloc(size);
}

char swap_nibbles(char value) {
    // Shift the lower nibble to the upper nibble and vice versa
    return (value >> 4) | (value << 4);
}

void draw_buffer(char* buffer, int x, int y, char* color_data) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {x, y};  // Console buffer size
    COORD zeroCoord = {0, 0};   // Top-left start
    SMALL_RECT writeRegion = {0, 0, x - 1, y - 1};  // Where to write
    
    CHAR_INFO* charInfo = (CHAR_INFO*)malloc(x * y * sizeof(CHAR_INFO));
    if (!charInfo) return;

    // Fill the CHAR_INFO buffer
    for (int i = 0; i < x * y; i++) {
        charInfo[i].Char.AsciiChar = buffer[i];     // Character
        charInfo[i].Attributes = (WORD)swap_nibbles(color_data[i]); // Foreground + Background
    }

    // Write the full buffer at once
    WriteConsoleOutput(hConsole, charInfo, bufferSize, zeroCoord, &writeRegion);
    
    free(charInfo);  // Cleanup
    Sleep(ms_sleep);
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
    //system("clear");
}

void hide_cursor(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo); // Get current cursor info
    cursorInfo.bVisible = FALSE; // Hide the cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void backend_init(){
    return;
}

char key_bord[256] = {0};  // Key state array

void release_all_keys() {
    for (int i = 0; i < 256; i++) {
        key_bord[i] = 0;  // Reset all keys
    }
}

void scan_input() {
    for (int i = 0; i < 256; i++) {
        SHORT keyState = GetAsyncKeyState(toupper(i));
        if (keyState & 0x8000) {  // If high-order bit is set, key is currently down
            key_bord[i] = 1;
        } else {
            key_bord[i] = 0;
        }
    }
}

char is_key_pressed(char key) {
    return (key >= 0 && key < 256) ? key_bord[(unsigned char)key] : 0;
}
