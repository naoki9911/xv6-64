#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "font_bin.h"

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

int section_parser(char *buffer);
char* element_parser(char *buffer);
int char_index_parser(char *buffer,int len);
uint16_t be2le(uint16_t val);
int data_parser(int offset);


char *buffer = font_bin;
char *buffer_base = font_bin;

int main(int argc, char* argv[]){
  section_parser(buffer);
}

int section_parser(char *buffer){
  while(buffer - buffer_base < font_size){
    if(!memcmp(buffer,SECTION_FILE,4)){
      printf("-----FILE SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_NAME,4)){
      printf("-----NAME SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_FAMI,4)){
      printf("-----FAMI SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_WEIG,4)){
      printf("-----WEIG SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_SLAN,4)){
      printf("-----SLAN SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_PTSZ,4)){
      printf("-----PTSZ SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_MAXW,4)){
      printf("-----MAXW SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_MAXH,4)){
      printf("-----MAXH SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_ASCE,4)){
      printf("-----ASCE SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_DESC,4)){
      printf("-----DESC SECTION-----\n");
    }else if(!memcmp(buffer,SECTION_CHIX,4)){
      printf("-----CHIX SECTION-----\n");
    }else{
      return -1;
    }
    buffer = element_parser(buffer);
  }
}

char* element_parser(char *buffer){
  int len=0;
  if(!memcmp(buffer,SECTION_CHIX,4)){
    buffer += 4;
    len = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + buffer[3];
    printf("Length:%d\n",len);
    buffer += 4;
    char_index_parser(buffer,len);
  }else{
    buffer += 4;
    len = (buffer[0] << 24) + (buffer[1] << 16) + (buffer[2] << 8) + buffer[3];
    buffer += 4;
    printf("Length:%d\n",len);
    printf("Value :");
    for(int i=0;i<len;i++){
      printf("%02X ",buffer[i]);
    }
    printf("(");
    for(int i=0;i<len;i++){
      printf("%c",buffer[i]);
    }
    printf(")\n");
  }
  buffer += len;
  return buffer;
}

int char_index_parser(char *buffer,int len){
  printf("struct size:%d\n",sizeof(struct char_index));
  struct char_index *c_index;
  for(int i=0;i<800;){
    c_index = (struct char_index *)(buffer+i);
    int unicode_p=0;
    for(int j=0;j<4;j++){
      unicode_p = (unicode_p << 8) + c_index->unicode_point[j];
    }
    printf("Unicode Point:%X\n",unicode_p);
    
    printf("Storage flags:%02X\n",c_index->str_flag);

    int offset=0;
    for(int j=0;j<4;j++){
      offset = (offset << 8) + c_index->offset[j];
    }
    printf("Offset:%d\n",offset);
    data_parser(offset);
    printf("\n");
    i+=sizeof(struct char_index);
  }
}  

int data_parser(int offset){
  struct font_data *data = (struct font_data *)(offset+buffer_base);
  int width = be2le(data->width);
  int height = be2le(data->height);
  printf("Width:%d\n",width);
  printf("Height:%d\n",height);
  printf("X offset:%d\n",be2le(data->x_offset));
  printf("Y offset:%d\n",be2le(data->y_offset));
  printf("Device Width:%d\n",be2le(data->dev_width));
  int len = (be2le(data->width)*be2le(data->height)+7)/8;
  uint8_t *bmp = (uint8_t *)(buffer_base+offset+sizeof(struct font_data));
  printf("Bitmap Length:%d\n",len);
  uint8_t bmp_b = 0;
  for(int h=0;h<height;h++){
    for(int w=0;w<width;w++){
      if((w+h*width)%8 == 0){
        bmp_b = bmp[(w+h*width)/8];
      }
      if(bmp_b >> (7-(w+h*width)%8)&0x1){
        printf("*");
      }else{
        printf(" ");
      }
    }
    printf("\n");
  }
}

uint16_t be2le(uint16_t val){
  return ((0xFF&val) << 8) + ((0xFF00&val) >> 8);
}
