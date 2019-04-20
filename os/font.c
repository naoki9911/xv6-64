#include "stdint.h"
#include "graphic.h"
#include "structs.h"
#include "font.h"
#include "font.bin"

struct font_entry* font_draw(int base_x, int base_y,uint8_t c){
    struct font_entry *entry = &font_data[c-0x20];
    uint8_t bmp_b = 0;
    uint16_t width = entry->width;
    uint16_t height = entry->height;
    int x = base_x+entry->x_offset;
    int y = base_y-height-entry->y_offset;
    for(int h=0;h<height;h++){
        for(int w=0;w<width;w++){
            int bit_pos = (w+h*width)%8;
            if(bit_pos == 0){
                bmp_b = entry->data[(w+h*width)/8];
            }
            if(bmp_b >> (7-bit_pos)&0x1){
                struct graphic_rgb white = {200,200,200};
                graphic_draw_pixel(w+x, h+y, &white);
            }else{
                struct graphic_rgb black = {0,0,0};
                graphic_draw_pixel(w+x, h+y, &black);
            }
        }
    }
    return entry;
}
