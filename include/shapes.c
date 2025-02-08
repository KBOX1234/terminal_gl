void draw_rectangle(char fill, int pos_x, int pos_y, int size_x, int size_y, char color){
    int pointer_x = pos_x;
    int pointer_y = pos_y;

    while(pointer_x < pos_x + size_x){
        while(pointer_y < pos_y + size_y){
            draw_char(fill, pointer_x, pointer_y, color);
            pointer_y++;
        }
        pointer_y = pos_y;
        pointer_x++;
    }
}

void draw_line(char fill, int pos_x_1, int pos_y_1, int pos_x_2, int pos_y_2, char color){
    int dx = abs(pos_x_2 - pos_x_1);
    int dy = abs(pos_y_2 - pos_y_1);
    int sx = (pos_x_1 < pos_x_2) ? 1 : -1;
    int sy = (pos_y_1 < pos_y_2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_char(fill, pos_x_1, pos_y_1, color); // Draw pixel at (pos_x_1, pos_y_1)

        if (pos_x_1 == pos_x_2 && pos_y_1 == pos_y_2) break; // Stop when reaching end point

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; pos_x_1 += sx; }
        if (e2 < dx) { err += dx; pos_y_1 += sy; }
    }
}