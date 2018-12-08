#include "font_bin.h"
#include "stdint.h"
#include "graphic.h"
#include "structs.h"
#include "font.h"

//#include <stdio.h>
#define SECTION_FILE "FILE"
#define SECTION_NAME "NAME"
#define SECTION_FAMI "FAMI"
#define SECTION_WEIG "WEIG"
#define SECTION_SLAN "SLAN"
#define SECTION_PTSZ "PTSZ"
#define SECTION_MAXW "MAXW"
#define SECTION_MAXH "MAXH"
#define SECTION_ASCE "ASCE"
#define SECTION_DESC "DESC"
#define SECTION_CHIX "CHIX"

struct __attribute__((packed)) char_index {
  uint8_t unicode_point[4];
  uint8_t str_flag;
  uint8_t offset[4];
};

struct __attribute__((packed)) font_data {
  uint16_t width;
  uint16_t height;
  uint16_t x_offset;
  uint16_t y_offset;
  uint16_t dev_width;
};

int font_addr[94] = {0};

char *buffer = font_bin;
char *buffer_base = font_bin;

int section_parser(){
  while(buffer - buffer_base < font_size){
    if(!memcmp(buffer,SECTION_FILE,4)){
    }else if(!memcmp(buffer,SECTION_NAME,4)){
    }else if(!memcmp(buffer,SECTION_FAMI,4)){
    }else if(!memcmp(buffer,SECTION_WEIG,4)){
    }else if(!memcmp(buffer,SECTION_SLAN,4)){
    }else if(!memcmp(buffer,SECTION_PTSZ,4)){
    }else if(!memcmp(buffer,SECTION_MAXW,4)){
    }else if(!memcmp(buffer,SECTION_MAXH,4)){
    }else if(!memcmp(buffer,SECTION_ASCE,4)){
    }else if(!memcmp(buffer,SECTION_DESC,4)){
    }else if(!memcmp(buffer,SECTION_CHIX,4)){
    }else{
      return -1;
    }
    buffer = element_parser(buffer);
  }
  return 0;
}

char* element_parser(char *buffer){
  int len=0;
  if(!memcmp(buffer,SECTION_CHIX,4)){
    buffer += 4;
    len = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + buffer[3];
    buffer += 4;
    char_index_parser(buffer,len);
  }else{
    buffer += 4;
    len = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + buffer[3];
    buffer += 4;
  }
  buffer += len;
  return buffer;
}

void char_index_parser(char *buffer,int len){
  struct char_index *c_index;
  for(int i=0;i<2000;){
    c_index = (struct char_index *)(buffer+i);
    int unicode_p=0;
    for(int j=0;j<4;j++){
      unicode_p = (unicode_p << 8) + c_index->unicode_point[j];
    }
    int offset=0;
    for(int j=0;j<4;j++){
      offset = (offset << 8) + c_index->offset[j];
    }
    if(unicode_p > 0x20 && unicode_p < 0x7F){
      if(font_addr[unicode_p] == 0){
        font_addr[unicode_p] = offset+buffer_base;
      }
      data_parser(offset);
    }
    i+=sizeof(struct char_index);
  }
}  

int x=0;
int y=0;
int cursor=0;
void data_parser(int offset){
  struct font_data *data = (struct font_data *)(offset+buffer_base);
  int width = be2le(data->width);
  int height = be2le(data->height);
//  int len = (be2le(data->width)*be2le(data->height)+7)/8;
  uint8_t *bmp = (uint8_t *)(buffer_base+offset+sizeof(struct font_data));
  uint8_t bmp_b = 0;
  for(int h=0;h<height;h++){
    for(int w=0;w<width;w++){
      if((w+h*width)%8 == 0){
        bmp_b = bmp[(w+h*width)/8];
      }
      if(bmp_b >> (7-(w+h*width)%8)&0x1){
        struct graphic_rgb white = {200,200,200};
        graphic_draw_pixel(w*2+x+10, h*2+y, &white);
        graphic_draw_pixel(w*2+x+11, h*2+y, &white);
        graphic_draw_pixel(w*2+x+10, h*2+y+1, &white);
        graphic_draw_pixel(w*2+x+11, h*2+y+1, &white);
 //     printf("*");
      }else{
        struct graphic_rgb black = {0,0,0};
        graphic_draw_pixel(w*2+x+10, h*2+y, &black);
        graphic_draw_pixel(w*2+x+11, h*2+y, &black);
        graphic_draw_pixel(w*2+x+10, h*2+y+1, &black);
        graphic_draw_pixel(w*2+x+11, h*2+y+1, &black);
//      printf(" ");
      }
    }
//    printf("\n");
  }
  cursor+=2;
  cursor+=width*2;
//  int x_max = graphic_get_horizontal_resolution();
  int x_max = 300;
  x = cursor%x_max;
  y = (cursor/x_max)*30;
}

uint16_t be2le(uint16_t val){
  return ((0xFF&val) << 8) + ((0xFF00&val) >> 8);
}

int memcmp(const char* val_1, const char* val_2, int n)
{
  for(int i=0;i<n;i++){
    if(val_1[i] != val_2[i]) return 1;
  }
  return 0;
}
