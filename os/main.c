#include "structs.h"
#include "stdint.h"
int entry(struct BootParam *boot_param)
{
  uint8_t *vram = (unsigned char*)boot_param->graphic_config.frame_base;
  uint64_t vram_size = boot_param->graphic_config.frame_size;
  for(int i=0;i<vram_size;i++){
    vram[i] = 0xFF;
  }
  while(1){
    asm("hlt");
  }
  return 0;
}
