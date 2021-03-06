#include "stdint.h"
#include "console.h"
#include "graphic.h"
#include "font.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

uint16_t cursor_pos_x = 0;
uint16_t cursor_pos_y = 0;
uint16_t cursor_x = 0;
uint16_t cursor_y = 0;

uint16_t cursor_x_max = 0;
uint16_t cursor_y_max = 0;

uint8_t max_height = 0x10;
uint8_t max_width = 0x10; 

const char* pattern = "0123456789ABCDEF";
void console_init(){
    cursor_pos_x = 0;
    cursor_pos_y = 0;
    cursor_x = 0;
    cursor_y = max_height;
    cursor_x_max = graphic_get_horizontal_resolution();
    cursor_y_max = graphic_get_vertical_resolution();
}
void console_puts_str(const char* str){
    int i=0;
    while(str[i]){
        console_putc(str[i]);
        i++;
    }
}


void console_puts_strn(const char* str, int len){
    for(int i=0;i<len;i++){
        console_putc(str[i]);
    }
}
void console_puts_dec(int64_t val){
    uint64_t dec = val;
    if(val < 0){
        console_putc('-');
        dec = -1*val;
    }
    uint8_t digit[32];
    int digit_num = 0;
    do{
        digit[digit_num] = dec%10;
        dec = dec/10;
        digit_num++;
    }while(dec!=0);
    for(int i=digit_num;i>0;i--){
        if(digit_num > 9){
            console_puts_str("ERROR");
        }
        console_putc(pattern[digit[i-1]]);
    }
}

void console_puts_hex(int64_t val){
    if(val < 0){
        console_putc('-');
        val -= val*2;
    }
    uint8_t digit[32];
    uint64_t hex = val;
    int digit_num = 0;
    do{
        digit[digit_num] = hex&0xF;
        hex = hex>>4;
        digit_num++;
    }while(hex!=0);
    for(int i=digit_num;i>0;i--){
        console_putc(pattern[digit[i-1]]);
    }
}
void console_putc(uint8_t c){
    if(c == '\n'){
        cursor_y += max_height;
        cursor_x = 0;
    }else{
        if(cursor_x + max_width > cursor_x_max){
            cursor_x = 0;
            cursor_y += max_height;
        }
        struct font_entry *entry;
        entry = font_draw(cursor_x,cursor_y,c);
        cursor_x += entry->dev_width;
    }
}
