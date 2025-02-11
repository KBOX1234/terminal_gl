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
    buffer_expanded_size = buffer_expanded_size*16;
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

const int vga_to_ansi_fg[16] = {30, 34, 32, 36, 31, 35, 33, 37, 90, 94, 92, 96, 91, 95, 93, 97};
const int vga_to_ansi_bg[16] = {40, 44, 42, 46, 41, 45, 43, 47, 100, 104, 102, 106, 101, 105, 103, 107};

char* refrence_color(char color_byte) {
    int fg = (color_byte >> 4) & 0x0F; // Foreground (upper 4 bits)
    int bg = color_byte & 0x0F;        // Background (lower 4 bits)

    // Look up correct ANSI color codes
    int fg_ansi = vga_to_ansi_fg[fg];
    int bg_ansi = vga_to_ansi_bg[bg];

    // Allocate memory for the ANSI escape string
    char *ansi_code = (char*)malloc(16);
    if (!ansi_code) return NULL;

    // Format ANSI escape sequence (FG first)
    sprintf(ansi_code, "\x1b[%d;%dm", fg_ansi, bg_ansi);

    return ansi_code;
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
    usleep(ms_sleep*1000);

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
