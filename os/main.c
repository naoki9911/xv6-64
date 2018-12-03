#include "structs.h"

int entry(struct BootParam *boot_param)
{
  unsigned char *vram = (unsigned char*)boot_param->graphic_config.frame_base;
  unsigned long long vram_size = boot_param->graphic_config.frame_size;
  for(int i=0;i<vram_size;i++){
    vram[i] = 0xFF;
  }
  while(1){
    asm("hlt");
  }
  return 0;
}
