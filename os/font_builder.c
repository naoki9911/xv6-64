#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>


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
  for(int i=0;i<file_size-1;i++){
    printf("0x%02X, ",fgetc(fp));
    if((i+1)%10 == 0) printf("\n");
  }
  printf("0x%02X };\n",fgetc(fp));

  return 0;
}

