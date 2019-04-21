#include "stdint.h"
#include "console.h"
#include "font.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

uint16_t cursor_pos_x = 0;
uint16_t cursor_pos_y = 0;
uint16_t cursor_x = 0;
uint16_t cursor_y = 0;

uint16_t max_height = 0x10;

const char* pattern = "0123456789ABCDEF";
void console_init(){
    cursor_pos_x = 0;
    cursor_pos_y = 0;
    cursor_x = 0;
    cursor_y = max_height;
}
void console_puts_str(char *str){
    int i=0;
    while(str[i]){
        console_putc(str[i]);
        i++;
    }
}

void console_puts_dec(int val){
    if(val < 0){
        console_putc('-');
        val -= val*2;
    }
    uint8_t digit[32];
    int dec = val;
    int digit_num = 0;
    do{
        digit[digit_num] = dec%10;
        dec = dec/10;
        digit_num++;
    }while(dec!=0);
    for(int i=digit_num;i>=0;i--){
        console_putc(pattern[digit[i]]);
    }
}
void console_putc(uint8_t c){
    if(c == '\n'){
        cursor_y += max_height;
        cursor_x = 0;
    }else{
        struct font_entry *entry;
        entry = font_draw(cursor_x,cursor_y,c);
        cursor_x += entry->dev_width;
    }
}
