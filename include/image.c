// Function to find the closest VGA color index

const uint8_t VGA_PALETTE[16][3] = {
    {0, 0, 0},       // Black
    {0, 0, 170},     // Blue
    {0, 170, 0},     // Green
    {0, 170, 170},   // Cyan
    {170, 0, 0},     // Red
    {170, 0, 170},   // Magenta
    {170, 85, 0},    // Brown
    {170, 170, 170}, // Light Gray
    {85, 85, 85},    // Dark Gray
    {85, 85, 255},   // Light Blue
    {85, 255, 85},   // Light Green
    {85, 255, 255},  // Light Cyan
    {255, 85, 85},   // Light Red
    {255, 85, 255},  // Light Magenta
    {255, 255, 85},  // Yellow
    {255, 255, 255}  // White
};

uint8_t find_closest_vga_color(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t closest_index = 0;
    int min_distance = 1000000;

    for (uint8_t i = 0; i < 16; i++) {
        int dr = r - VGA_PALETTE[i][0];
        int dg = g - VGA_PALETTE[i][1];
        int db = b - VGA_PALETTE[i][2];
        int distance = dr * dr + dg * dg + db * db;

        if (distance < min_distance) {
            min_distance = distance;
            closest_index = i;
        }
    }
    return closest_index;
}

// Function to convert STB image to 16-color VGA format
char* convert_stbi_to_vga(const uint8_t* img_data, int width, int height, int channels) {
    char* vga_bitmap = (char*)malloc(width * height);
    if (!vga_bitmap) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;
            uint8_t r = img_data[index];
            uint8_t g = img_data[index + 1];
            uint8_t b = img_data[index + 2];
            vga_bitmap[y * width + x] = find_closest_vga_color(r, g, b);
        }
    }
    return vga_bitmap;
}

struct text_image load_image_to_text(const char* file, char fill){
    struct text_image text_img;
    
    int channels;
    unsigned char *img = stbi_load(file, &text_img.x, &text_img.y, &channels, 0);
    text_img.color_data = convert_stbi_to_vga(img, text_img.x, text_img.y, channels);

    text_img.buffer_data = malloc(text_img.x*text_img.y);

    int inc = 0;

    while(inc < text_img.x*text_img.y){
        text_img.buffer_data[inc] = fill;
        inc++;
    }

    return text_img;

}

struct text_image load_buffer(const char *name) {
    FILE *fptr = fopen(name, "r");
    if (!fptr) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(fptr, 0, SEEK_END);
    size_t length = ftell(fptr);
    rewind(fptr); // Reset file pointer

    struct text_image char_img;
    char_img.buffer_data = malloc(length + 1);
    char_img.color_data = malloc(length + 1);
    if (!char_img.buffer_data || !char_img.color_data) {
        perror("Memory allocation failed");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    memset(char_img.color_data, 0x0f, length);
    fread(char_img.buffer_data, 1, length, fptr);
    char_img.buffer_data[length] = '\0'; // Null-terminate buffer

    fclose(fptr);

    // Determine width (x) and height (y)
    char_img.x = 0;
    char_img.y = 1;
    size_t i = 0;
    while (i < length) {
        if (char_img.buffer_data[i] == '\n') {
            if (char_img.x == 0) {
                char_img.x = i; // Set width (x) from the first line
            }
            char_img.y++; // Count lines
        }
        i++;
    }

    // Remove newlines by shifting characters left
    size_t write_pos = 0;
    i = 0;
    while (i < length) {
        if (char_img.buffer_data[i] != '\n') {
            char_img.buffer_data[write_pos++] = char_img.buffer_data[i];
        }
        i++;
    }
    char_img.buffer_data[write_pos] = '\0'; // Null-terminate after removal

    return char_img;
}

void render_text_image(struct text_image img, int pos_x, int pos_y, char normal_pixel_ratio){
    if(normal_pixel_ratio == 0){    
        int inc = 0;
        int pointer_x = pos_x;
        int pointer_y = pos_y;

        while(pointer_y < pos_y+img.y){
            while(pointer_x < pos_x+img.x){
                draw_char(img.buffer_data[inc], pointer_x, pointer_y, img.color_data[inc]);
                inc++;

                pointer_x++;
            }
            pointer_x = pos_x;
            pointer_y++;
        }
    }

    else if(normal_pixel_ratio == 1){
        int inc = 0;
        int pointer_x = pos_x;
        int pointer_y = pos_y;

        while(pointer_y < pos_y+img.y){
            while(pointer_x < pos_x+img.x*2){
                draw_char(img.buffer_data[inc], pointer_x, pointer_y, img.color_data[inc]);
                inc++;

                pointer_x = pointer_x + 2;
            }
            pointer_x = pos_x;
            pointer_y++;
        }
        inc = 0;
        pointer_x = pos_x;
        pointer_y = pos_y;

        while(pointer_y < pos_y+img.y){
            while(pointer_x < pos_x+img.x*2){
                draw_char(img.buffer_data[inc], pointer_x+1, pointer_y, img.color_data[inc]);
                inc++;
                pointer_x = pointer_x + 2;
            }
            pointer_x = pos_x;
            pointer_y++;
        }
    }
}