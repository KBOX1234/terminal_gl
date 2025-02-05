#include "impl/impl.h"

// Standard Colors (0-15)
#define COLOR_0 "\033[30m"  // Black
#define COLOR_1 "\033[31m"  // Red
#define COLOR_2 "\033[32m"  // Green
#define COLOR_3 "\033[33m"  // Yellow
#define COLOR_4 "\033[34m"  // Blue
#define COLOR_5 "\033[35m"  // Magenta
#define COLOR_6 "\033[36m"  // Cyan
#define COLOR_7 "\033[37m"  // White
#define COLOR_8 "\033[90m"  // Bright Black
#define COLOR_9 "\033[91m"  // Bright Red
#define COLOR_10 "\033[92m" // Bright Green
#define COLOR_11 "\033[93m" // Bright Yellow
#define COLOR_12 "\033[94m" // Bright Blue
#define COLOR_13 "\033[95m" // Bright Magenta
#define COLOR_14 "\033[96m" // Bright Cyan
#define COLOR_15 "\033[97m" // Bright White

// Reset color
#define RESET_COLOR "\033[0m"


// Standard Colors (0-15) - Modified
#define DARK_BLACK "\033[30m"  // Black
#define DARK_RED "\033[31m"    // Red
#define DARK_GREEN "\033[32m"  // Green
#define DARK_YELLOW "\033[33m" // Yellow
#define DARK_BLUE "\033[34m"   // Blue
#define DARK_MAGENTA "\033[35m" // Magenta
#define DARK_CYAN "\033[36m"    // Cyan
#define DARK_WHITE "\033[37m"   // White
#define LIGHT_BLACK "\033[90m"  // Bright Black
#define LIGHT_RED "\033[91m"    // Bright Red
#define LIGHT_GREEN "\033[92m"  // Bright Green
#define LIGHT_YELLOW "\033[93m" // Bright Yellow
#define LIGHT_BLUE "\033[94m"   // Bright Blue
#define LIGHT_MAGENTA "\033[95m" // Bright Magenta
#define LIGHT_CYAN "\033[96m"    // Bright Cyan
#define LIGHT_WHITE "\033[97m"   // Bright White

// Reset color
#define RESET_COLOR_MODIFIED "\033[0m"



//buffer to write to
char* window_buffer;
int window_size_x, window_size_y;

//init
void init_window(char* name);

void draw_char(char c, int x, int y);

void update();

void fill_screen(char chare);

#include "terminal_gl.c"