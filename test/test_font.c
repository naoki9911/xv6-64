#include <stdint.h>
#include <stdio.h>
#include "../os/font.bin"

void my_putc(int x, int y, uint8_t c);
int main(void){
    my_putc(0,0,'H');
    my_putc(0,0,'e');
    my_putc(0,0,'l');
    my_putc(0,0,'l');
    my_putc(0,0,'o');
    my_putc(0,0,'W');
    my_putc(0,0,'o');
    my_putc(0,0,'r');
    my_putc(0,0,'l');
    my_putc(0,0,'d');
}

void my_putc(int x, int y, uint8_t c){
    struct font_entry *entry = &font_data[c-0x20];

    uint16_t width = entry->width;
    uint16_t height = entry->height;
    printf("ASCII CODE:%02X\n" ,entry->ascii_code);
    printf("Len:%d\n", entry->len);
    printf("Width:%d\n", width);
    printf("Height:%d\n", height);
    printf("Dev Width:%d\n", entry->dev_width);
    printf("X Offset:%d\n", entry->x_offset);
    printf("Y Offset:%d\n", entry->y_offset);
    printf("BIN:");
    for(int i=0;i<entry->len;i++){
        printf("0x%02X ", entry->data[i]);
    }
    printf("\n");
    uint8_t bmp_b;
    for(int h=0;h<height;h++){
        for(int w=0;w<width;w++){
            int bit_pos = (w+h*width)%8;
            if(bit_pos == 0){
                bmp_b = entry->data[(w+h*width)/8];
            }
            if(bmp_b >> (7-bit_pos)&1){
                printf("*");
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
