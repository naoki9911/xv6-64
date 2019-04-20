#ifndef FONT_H
#define FONT_H

struct font_entry {
    uint8_t ascii_code;
    int16_t width;
    int16_t height;
    int16_t x_offset;
    int16_t y_offset;
    int16_t dev_width;
    uint16_t len;
    uint8_t data[10];
};

struct font_entry* font_draw(int x, int y,uint8_t c);

#endif
