#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>

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

int section_parser(char *buffer);
char* element_parser(char *buffer);
int char_index_parser(char *buffer,int len);
uint16_t be2le(uint16_t val);
void font_data_file_creator();

char *buffer;
char *buffer_base;
int font_size;

int main(int argc, char* argv[]){
  int file_size = 0;
  struct stat st;
  FILE *fp;


  if(argc != 2){
    fprintf(stderr,"Invalid argument. Correct argument is ./font_builder (pf2 file name)\n");
    exit(EXIT_FAILURE);
  }
  char *file_name = argv[1];

  //Get file size to allocate buffer
  if(stat(file_name,&st) != 0){
    fprintf(stderr,"Failed to get file size of %s\n",file_name);
    exit(EXIT_FAILURE);
  }
  file_size = st.st_size;
  printf("int font_size = %d;\n",file_size);

  //Open file
  if((fp = fopen(file_name,"rb")) == NULL){
    fprintf(stderr,"Failed to open %s\n",file_name);
    exit(EXIT_FAILURE);
  }
  
  printf("char font_bin[%d] = {\n",file_size);
  font_size = file_size;
  buffer = (char *)malloc(file_size);
  buffer_base = buffer;

  for(int i=0;i<file_size-1;i++){
    char c = fgetc(fp);
    buffer[i] = c;
  }
  section_parser(buffer);

  font_data_file_creator();

  return 0;
}


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



struct font_entry {
    uint8_t ascii_code;
    int16_t width;
    int16_t height;
    int16_t x_offset;
    int16_t y_offset;
    int16_t dev_width;
    uint16_t len;
    uint8_t font_bin[10];
};
int data_parser(int offset, struct font_entry *entry);

struct font_entry font_data[0x5F];


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
  int unicode_p=0;
  int i = 0;
  struct char_index *c_index;
  while(unicode_p < 0x7F){
    c_index = (struct char_index *)(buffer+i);
    for(int j=0;j<4;j++){
      unicode_p = (unicode_p << 8) + c_index->unicode_point[j];
    }
    printf("Unicode Point:%X\n",unicode_p);
    

    if( unicode_p >= 0x20 && unicode_p <= 0x7E){
        printf("Storage flags:%02X\n",c_index->str_flag);
        int offset=0;
        for(int j=0;j<4;j++){
            offset = (offset << 8) + c_index->offset[j];
        }
        printf("Offset:%d\n",offset);
        font_data[unicode_p-0x20].ascii_code = unicode_p&0xFF;
        data_parser(offset, &font_data[unicode_p-0x20]);
        printf("\n");
    }
    i+=sizeof(struct char_index);
  }
}  

int data_parser(int offset, struct font_entry *entry){
    struct font_data *data = (struct font_data *)(offset+buffer_base);
    int width = be2le(data->width);
    int height = be2le(data->height);
    printf("Width:%d\n",width);
    printf("Height:%d\n",height);
    printf("X offset:%d\n",be2le(data->x_offset));
    printf("Y offset:%d\n",(int16_t)be2le(data->y_offset));
    printf("Device Width:%d\n",be2le(data->dev_width));
    int len = (be2le(data->width)*be2le(data->height)+7)/8;
    uint8_t *bmp = (uint8_t *)(buffer_base+offset+sizeof(struct font_data));
    memset(entry->font_bin, 0, 10);
    memcpy(entry->font_bin, bmp, len);
    printf("Bitmap Length:%d\n",len);
    if(len > 10) {
        printf("Bitmap Length is larger than 10\n");
        exit(1);
    }
    uint8_t bmp_b = 0;
    for (int i=0;i<len;i++){
        printf(" 0x%02X", bmp[i]);
    }
    printf("\n");
    for (int i=0;i<len;i++){
        printf(" 0x%02X", entry->font_bin[i]);
    }
    printf("\n");
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
    entry->width = width;
    entry->height = height;
    entry->x_offset = be2le(data->x_offset);
    entry->y_offset = be2le(data->y_offset);
    entry->dev_width = be2le(data->dev_width);
    entry->len = len;
}

void font_data_file_creator(){
    printf("struct font_entry font_data[0x5F] = {\n");
    for(int i=0;i<0x5F;i++){
        struct font_entry *entry = &font_data[i];
        printf("{ 0x%X, %d, %d, %d, %d, %d, %d",
                entry->ascii_code, entry->width, entry->height, entry->x_offset, entry->y_offset, entry->dev_width, entry->len);
        printf(", { 0x%02X", entry->font_bin[0]);
        for(int j=1;j<10;j++){
            printf(", 0x%02X", entry->font_bin[j]);
        }
        printf(" }}");
        if(i != 0x5E){
            printf(",\n");
        }else{
            printf("};\n");
        }
    }
}
uint16_t be2le(uint16_t val){
    return ((0xFF&val) << 8) + ((0xFF00&val) >> 8);
}
