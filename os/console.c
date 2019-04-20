#include "stdint.h"
#include "console.h"
#include "font.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

uint16_t cursor_pos_x = 0;
uint16_t cursor_pos_y = 0;
uint16_t cursor_x = 0;
uint16_t cursor_y = 0;

void console_init(){
    cursor_pos_x = 0;
    cursor_pos_y = 0;
    cursor_x = 0;
    cursor_y = 0;
}
void console_puts(char *str){
    int i=0;
    while(str[i]){
        console_putc(str[i]);
        i++;
    }
}
void console_putc(uint8_t c){
    struct font_entry *entry;
    entry = font_draw(cursor_x,cursor_y,c);
    cursor_x += entry->dev_width;
}
