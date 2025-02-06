#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/prctl.h>  // Include the prctl header
#include <string.h>


#define STD_OUT 1
#define CLEAR_AND_CURSOR_RESET "\033[2J\033[H"
#define HIDE_CURSOR "\033[?25l"

#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

// Reset
#define ANSI_RESET       "\x1b[0m"

// Foreground (text) colors
#define ANSI_BLACK       "\x1b[30m"
#define ANSI_RED         "\x1b[31m"
#define ANSI_GREEN       "\x1b[32m"
#define ANSI_YELLOW      "\x1b[33m"
#define ANSI_BLUE        "\x1b[34m"
#define ANSI_MAGENTA     "\x1b[35m"
#define ANSI_CYAN        "\x1b[36m"
#define ANSI_WHITE       "\x1b[37m"

// Bright Foreground Colors
#define ANSI_BRIGHT_BLACK   "\x1b[90m"
#define ANSI_BRIGHT_RED     "\x1b[91m"
#define ANSI_BRIGHT_GREEN   "\x1b[92m"
#define ANSI_BRIGHT_YELLOW  "\x1b[93m"
#define ANSI_BRIGHT_BLUE    "\x1b[94m"
#define ANSI_BRIGHT_MAGENTA "\x1b[95m"
#define ANSI_BRIGHT_CYAN    "\x1b[96m"
#define ANSI_BRIGHT_WHITE   "\x1b[97m"

// Background colors
#define ANSI_BG_BLACK       "\x1b[40m"
#define ANSI_BG_RED         "\x1b[41m"
#define ANSI_BG_GREEN       "\x1b[42m"
#define ANSI_BG_YELLOW      "\x1b[43m"
#define ANSI_BG_BLUE        "\x1b[44m"
#define ANSI_BG_MAGENTA     "\x1b[45m"
#define ANSI_BG_CYAN        "\x1b[46m"
#define ANSI_BG_WHITE       "\x1b[47m"

// Bright Background Colors
#define ANSI_BG_BRIGHT_BLACK   "\x1b[100m"
#define ANSI_BG_BRIGHT_RED     "\x1b[101m"
#define ANSI_BG_BRIGHT_GREEN   "\x1b[102m"
#define ANSI_BG_BRIGHT_YELLOW  "\x1b[103m"
#define ANSI_BG_BRIGHT_BLUE    "\x1b[104m"
#define ANSI_BG_BRIGHT_MAGENTA "\x1b[105m"
#define ANSI_BG_BRIGHT_CYAN    "\x1b[106m"
#define ANSI_BG_BRIGHT_WHITE   "\x1b[107m"

// Text Styles
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_DIM          "\x1b[2m"
#define ANSI_UNDERLINE    "\x1b[4m"
#define ANSI_BLINK        "\x1b[5m"
#define ANSI_REVERSE      "\x1b[7m"
#define ANSI_HIDDEN       "\x1b[8m"


char* color_table[256] = {
    // Foreground: 30-37 (standard) and 90-97 (bright), Background: 40-47 (standard) and 100-107 (bright)
    // Table for 16 foreground × 16 background combinations
    [0x00] = "\x1b[30m\x1b[40m", [0x01] = "\x1b[30m\x1b[41m", [0x02] = "\x1b[30m\x1b[42m", [0x03] = "\x1b[30m\x1b[43m",
    [0x04] = "\x1b[30m\x1b[44m", [0x05] = "\x1b[30m\x1b[45m", [0x06] = "\x1b[30m\x1b[46m", [0x07] = "\x1b[30m\x1b[47m",
    [0x08] = "\x1b[30m\x1b[100m", [0x09] = "\x1b[30m\x1b[101m", [0x0A] = "\x1b[30m\x1b[102m", [0x0B] = "\x1b[30m\x1b[103m",
    [0x0C] = "\x1b[30m\x1b[104m", [0x0D] = "\x1b[30m\x1b[105m", [0x0E] = "\x1b[30m\x1b[106m", [0x0F] = "\x1b[30m\x1b[107m",
    
    [0x10] = "\x1b[31m\x1b[40m", [0x11] = "\x1b[31m\x1b[41m", [0x12] = "\x1b[31m\x1b[42m", [0x13] = "\x1b[31m\x1b[43m",
    [0x14] = "\x1b[31m\x1b[44m", [0x15] = "\x1b[31m\x1b[45m", [0x16] = "\x1b[31m\x1b[46m", [0x17] = "\x1b[31m\x1b[47m",
    [0x18] = "\x1b[31m\x1b[100m", [0x19] = "\x1b[31m\x1b[101m", [0x1A] = "\x1b[31m\x1b[102m", [0x1B] = "\x1b[31m\x1b[103m",
    [0x1C] = "\x1b[31m\x1b[104m", [0x1D] = "\x1b[31m\x1b[105m", [0x1E] = "\x1b[31m\x1b[106m", [0x1F] = "\x1b[31m\x1b[107m",
    
    [0x20] = "\x1b[32m\x1b[40m", [0x21] = "\x1b[32m\x1b[41m", [0x22] = "\x1b[32m\x1b[42m", [0x23] = "\x1b[32m\x1b[43m",
    [0x24] = "\x1b[32m\x1b[44m", [0x25] = "\x1b[32m\x1b[45m", [0x26] = "\x1b[32m\x1b[46m", [0x27] = "\x1b[32m\x1b[47m",
    [0x28] = "\x1b[32m\x1b[100m", [0x29] = "\x1b[32m\x1b[101m", [0x2A] = "\x1b[32m\x1b[102m", [0x2B] = "\x1b[32m\x1b[103m",
    [0x2C] = "\x1b[32m\x1b[104m", [0x2D] = "\x1b[32m\x1b[105m", [0x2E] = "\x1b[32m\x1b[106m", [0x2F] = "\x1b[32m\x1b[107m",
    
    [0x30] = "\x1b[33m\x1b[40m", [0x31] = "\x1b[33m\x1b[41m", [0x32] = "\x1b[33m\x1b[42m", [0x33] = "\x1b[33m\x1b[43m",
    [0x34] = "\x1b[33m\x1b[44m", [0x35] = "\x1b[33m\x1b[45m", [0x36] = "\x1b[33m\x1b[46m", [0x37] = "\x1b[33m\x1b[47m",
    [0x38] = "\x1b[33m\x1b[100m", [0x39] = "\x1b[33m\x1b[101m", [0x3A] = "\x1b[33m\x1b[102m", [0x3B] = "\x1b[33m\x1b[103m",
    [0x3C] = "\x1b[33m\x1b[104m", [0x3D] = "\x1b[33m\x1b[105m", [0x3E] = "\x1b[33m\x1b[106m", [0x3F] = "\x1b[33m\x1b[107m",

    [0x40] = "\x1b[34m\x1b[40m", [0x41] = "\x1b[34m\x1b[41m", [0x42] = "\x1b[34m\x1b[42m", [0x43] = "\x1b[34m\x1b[43m",
    [0x44] = "\x1b[34m\x1b[44m", [0x45] = "\x1b[34m\x1b[45m", [0x46] = "\x1b[34m\x1b[46m", [0x47] = "\x1b[34m\x1b[47m",
    [0x48] = "\x1b[34m\x1b[100m", [0x49] = "\x1b[34m\x1b[101m", [0x4A] = "\x1b[34m\x1b[102m", [0x4B] = "\x1b[34m\x1b[103m",
    [0x4C] = "\x1b[34m\x1b[104m", [0x4D] = "\x1b[34m\x1b[105m", [0x4E] = "\x1b[34m\x1b[106m", [0x4F] = "\x1b[34m\x1b[107m",
    
    [0x50] = "\x1b[34m\x1b[40m", [0x51] = "\x1b[34m\x1b[41m", [0x52] = "\x1b[34m\x1b[42m", [0x53] = "\x1b[34m\x1b[43m",
    [0x54] = "\x1b[34m\x1b[44m", [0x55] = "\x1b[34m\x1b[45m", [0x56] = "\x1b[34m\x1b[46m", [0x57] = "\x1b[34m\x1b[47m",
    [0x58] = "\x1b[34m\x1b[100m", [0x59] = "\x1b[34m\x1b[101m", [0x5A] = "\x1b[34m\x1b[102m", [0x5B] = "\x1b[34m\x1b[103m",
    [0x5C] = "\x1b[34m\x1b[104m", [0x5D] = "\x1b[34m\x1b[105m", [0x5E] = "\x1b[34m\x1b[106m", [0x5F] = "\x1b[34m\x1b[107m",

    [0x60] = "\x1b[34m\x1b[40m", [0x61] = "\x1b[34m\x1b[41m", [0x62] = "\x1b[34m\x1b[42m", [0x63] = "\x1b[34m\x1b[43m",
    [0x64] = "\x1b[34m\x1b[44m", [0x65] = "\x1b[34m\x1b[45m", [0x66] = "\x1b[34m\x1b[46m", [0x67] = "\x1b[34m\x1b[47m",
    [0x68] = "\x1b[34m\x1b[100m", [0x69] = "\x1b[34m\x1b[101m", [0x6A] = "\x1b[34m\x1b[102m", [0x6B] = "\x1b[34m\x1b[103m",
    [0x6C] = "\x1b[34m\x1b[104m", [0x6D] = "\x1b[34m\x1b[105m", [0x6E] = "\x1b[34m\x1b[106m", [0x6F] = "\x1b[34m\x1b[107m",

    [0x70] = "\x1b[34m\x1b[40m", [0x71] = "\x1b[34m\x1b[41m", [0x72] = "\x1b[34m\x1b[42m", [0x73] = "\x1b[34m\x1b[43m",
    [0x74] = "\x1b[34m\x1b[44m", [0x75] = "\x1b[34m\x1b[45m", [0x76] = "\x1b[34m\x1b[46m", [0x77] = "\x1b[34m\x1b[47m",
    [0x78] = "\x1b[34m\x1b[100m", [0x79] = "\x1b[34m\x1b[101m", [0x7A] = "\x1b[34m\x1b[102m", [0x7B] = "\x1b[34m\x1b[103m",
    [0x7C] = "\x1b[34m\x1b[104m", [0x7D] = "\x1b[34m\x1b[105m", [0x7E] = "\x1b[34m\x1b[106m", [0x7F] = "\x1b[34m\x1b[107m",

    [0x80] = "\x1b[34m\x1b[40m", [0x81] = "\x1b[34m\x1b[41m", [0x82] = "\x1b[34m\x1b[42m", [0x83] = "\x1b[34m\x1b[43m",
    [0x84] = "\x1b[34m\x1b[44m", [0x85] = "\x1b[34m\x1b[45m", [0x86] = "\x1b[34m\x1b[46m", [0x87] = "\x1b[34m\x1b[47m",
    [0x88] = "\x1b[34m\x1b[100m", [0x89] = "\x1b[34m\x1b[101m", [0x8A] = "\x1b[34m\x1b[102m", [0x8B] = "\x1b[34m\x1b[103m",
    [0x8C] = "\x1b[34m\x1b[104m", [0x8D] = "\x1b[34m\x1b[105m", [0x8E] = "\x1b[34m\x1b[106m", [0x8F] = "\x1b[34m\x1b[107m",

    [0x90] = "\x1b[34m\x1b[40m", [0x91] = "\x1b[34m\x1b[41m", [0x92] = "\x1b[34m\x1b[42m", [0x93] = "\x1b[34m\x1b[43m",
    [0x94] = "\x1b[34m\x1b[44m", [0x95] = "\x1b[34m\x1b[45m", [0x96] = "\x1b[34m\x1b[46m", [0x97] = "\x1b[34m\x1b[47m",
    [0x98] = "\x1b[34m\x1b[100m", [0x99] = "\x1b[34m\x1b[101m", [0x9A] = "\x1b[34m\x1b[102m", [0x9B] = "\x1b[34m\x1b[103m",
    [0x9C] = "\x1b[34m\x1b[104m", [0x9D] = "\x1b[34m\x1b[105m", [0x9E] = "\x1b[34m\x1b[106m", [0x9F] = "\x1b[34m\x1b[107m",

    [0xa0] = "\x1b[34m\x1b[40m", [0xa1] = "\x1b[34m\x1b[41m", [0xa2] = "\x1b[34m\x1b[42m", [0xa3] = "\x1b[34m\x1b[43m",
    [0xa4] = "\x1b[34m\x1b[44m", [0xa5] = "\x1b[34m\x1b[45m", [0xa6] = "\x1b[34m\x1b[46m", [0xa7] = "\x1b[34m\x1b[47m",
    [0xa8] = "\x1b[34m\x1b[100m", [0xa9] = "\x1b[34m\x1b[101m", [0xaA] = "\x1b[34m\x1b[102m", [0xaB] = "\x1b[34m\x1b[103m",
    [0xaC] = "\x1b[34m\x1b[104m", [0xaD] = "\x1b[34m\x1b[105m", [0xaE] = "\x1b[34m\x1b[106m", [0xaF] = "\x1b[34m\x1b[107m",

    [0xb0] = "\x1b[34m\x1b[40m", [0xb1] = "\x1b[34m\x1b[41m", [0xb2] = "\x1b[34m\x1b[42m", [0xb3] = "\x1b[34m\x1b[43m",
    [0xb4] = "\x1b[34m\x1b[44m", [0xb5] = "\x1b[34m\x1b[45m", [0xb6] = "\x1b[34m\x1b[46m", [0xb7] = "\x1b[34m\x1b[47m",
    [0xb8] = "\x1b[34m\x1b[100m", [0xb9] = "\x1b[34m\x1b[101m", [0xbA] = "\x1b[34m\x1b[102m", [0xbB] = "\x1b[34m\x1b[103m",
    [0xbC] = "\x1b[34m\x1b[104m", [0xbD] = "\x1b[34m\x1b[105m", [0xbE] = "\x1b[34m\x1b[106m", [0xbF] = "\x1b[34m\x1b[107m",

    [0xc0] = "\x1b[34m\x1b[40m", [0xc1] = "\x1b[34m\x1b[41m", [0xc2] = "\x1b[34m\x1b[42m", [0xc3] = "\x1b[34m\x1b[43m",
    [0xc4] = "\x1b[34m\x1b[44m", [0xc5] = "\x1b[34m\x1b[45m", [0xc6] = "\x1b[34m\x1b[46m", [0xc7] = "\x1b[34m\x1b[47m",
    [0xc8] = "\x1b[34m\x1b[100m", [0xc9] = "\x1b[34m\x1b[101m", [0xcA] = "\x1b[34m\x1b[102m", [0xcB] = "\x1b[34m\x1b[103m",
    [0xcC] = "\x1b[34m\x1b[104m", [0xcD] = "\x1b[34m\x1b[105m", [0xcE] = "\x1b[34m\x1b[106m", [0xcF] = "\x1b[34m\x1b[107m",

    [0xd0] = "\x1b[34m\x1b[40m", [0xd1] = "\x1b[34m\x1b[41m", [0xd2] = "\x1b[34m\x1b[42m", [0xd3] = "\x1b[34m\x1b[43m",
    [0xd4] = "\x1b[34m\x1b[44m", [0xd5] = "\x1b[34m\x1b[45m", [0xd6] = "\x1b[34m\x1b[46m", [0xd7] = "\x1b[34m\x1b[47m",
    [0xd8] = "\x1b[34m\x1b[100m", [0xd9] = "\x1b[34m\x1b[101m", [0xdA] = "\x1b[34m\x1b[102m", [0xdB] = "\x1b[34m\x1b[103m",
    [0xdC] = "\x1b[34m\x1b[104m", [0xdD] = "\x1b[34m\x1b[105m", [0xdE] = "\x1b[34m\x1b[106m", [0xdF] = "\x1b[34m\x1b[107m",

    [0xe0] = "\x1b[34m\x1b[40m", [0xe1] = "\x1b[34m\x1b[41m", [0xe2] = "\x1b[34m\x1b[42m", [0xe3] = "\x1b[34m\x1b[43m",
    [0xe4] = "\x1b[34m\x1b[44m", [0xe5] = "\x1b[34m\x1b[45m", [0xe6] = "\x1b[34m\x1b[46m", [0xe7] = "\x1b[34m\x1b[47m",
    [0xe8] = "\x1b[34m\x1b[100m", [0xe9] = "\x1b[34m\x1b[101m", [0xeA] = "\x1b[34m\x1b[102m", [0xeB] = "\x1b[34m\x1b[103m",
    [0xeC] = "\x1b[34m\x1b[104m", [0xeD] = "\x1b[34m\x1b[105m", [0xeE] = "\x1b[34m\x1b[106m", [0xeF] = "\x1b[34m\x1b[107m",

    [0xf0] = "\x1b[34m\x1b[40m", [0xf1] = "\x1b[34m\x1b[41m", [0xf2] = "\x1b[34m\x1b[42m", [0xf3] = "\x1b[34m\x1b[43m",
    [0xf4] = "\x1b[34m\x1b[44m", [0xf5] = "\x1b[34m\x1b[45m", [0xf6] = "\x1b[34m\x1b[46m", [0xf7] = "\x1b[34m\x1b[47m",
    [0xf8] = "\x1b[34m\x1b[100m", [0xf9] = "\x1b[34m\x1b[101m", [0xfA] = "\x1b[34m\x1b[102m", [0xfB] = "\x1b[34m\x1b[103m",
    [0xfC] = "\x1b[34m\x1b[104m", [0xfD] = "\x1b[34m\x1b[105m", [0xfE] = "\x1b[34m\x1b[106m", [0xfF] = "\x1b[34m\x1b[107m",
    
    // Other colors would continue similarly...
};

char key_bord[256];

#endif // ANSI_COLORS_H

char* buffer_expanded;

size_t buffer_expanded_size;

// Function to allocate memory
void *allocate_memory(long size) {
    return malloc(size);
}

void sys_exit(int status) {
    exit(status);  // Use glibc exit function
}

void get_terminal_size(int *rows, int *cols) {
    struct winsize ws;
    ioctl(STD_OUT, TIOCGWINSZ, &ws);  // Use STDOUT as file descriptor
    *rows = ws.ws_row;
    *cols = ws.ws_col;
}

void set_non_canonical_mode() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);  // Get current terminal settings
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    newt.c_cc[VMIN] = 1;  // Read at least 1 character
    newt.c_cc[VTIME] = 0;  // No timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply new settings
}


void backend_init(){
    int window_x;
    int window_y;
    get_terminal_size(&window_y, &window_x);
    buffer_expanded_size = window_y*window_x;
    buffer_expanded_size = buffer_expanded_size*10;
    buffer_expanded = malloc(buffer_expanded_size);

    set_non_canonical_mode();


    //init ascii table;

    int inc = 0;

    while(inc < 256){
        key_bord[inc] = 0;
        inc++;
    }
}

int kbhit(void) {
    struct timeval tv = { 0, 0 };  // Timeout is 0 to make it non-blocking
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    // Check if data is available on stdin without blocking
    int result = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    if (result == -1) {
        // Handle error (optional)
        perror("select");
        return 0;
    }
    return result > 0;  // Returns 1 if data is available, otherwise 0
}


char* refrence_color(int i){
    return color_table[i];
}

void draw_buffer(char* buffer, int x, int y, char* color_data) {
    //memset(buffer_expanded, ' ', strlen(buffer_expanded));
    int x_inc = 0;
    int y_inc = 0;

    int color_and_buffer_inc = 0;
    int buffer_expanded_inc = 0;

    while(y_inc < y){
        while(x_inc < x){
            char* tmp_color = refrence_color(color_data[color_and_buffer_inc]);
            memcpy(&buffer_expanded[buffer_expanded_inc], tmp_color, strlen(tmp_color));
            buffer_expanded_inc = buffer_expanded_inc + strlen(tmp_color);
            buffer_expanded[buffer_expanded_inc] = buffer[color_and_buffer_inc];

            buffer_expanded_inc++;
            color_and_buffer_inc++;
            x_inc++;
        }
        buffer_expanded[buffer_expanded_inc] = '\n';
        buffer_expanded_inc++;

        x_inc = 0;
        y_inc++;
    }
    write(STD_OUT, buffer_expanded, buffer_expanded_inc);
    usleep(16667);

}


void set_process_name(char *name) {
    prctl(PR_SET_NAME, (unsigned long)name);  // Use the direct syscall for setting process name
}

void clear() {
    write(STD_OUT, CLEAR_AND_CURSOR_RESET, 7);
}

void hide_cursor() {
    write(STD_OUT, HIDE_CURSOR, 6);  // Send escape sequence to hide the cursor
}

void release_all_keys() {
    for (int i = 0; i < 256; i++) {
        key_bord[i] = 0;  // Reset all keys
    }
}

void scan_input() {
    release_all_keys();
    while (kbhit()) {
        char ch = getchar();  // Read the pressed key
        if (ch >= 0 && ch < 256) {
            key_bord[(unsigned char)ch] = 1;  // Mark key as pressed
        }
    }
}

char is_key_pressed(char key) {
    if (key >= 0 && key < 256) {
        return key_bord[(unsigned char)key];  // Return the state of the requested key
    }
    return 0;  // If the key is out of range, return 0 (not pressed)
}
