#include "structs.h"
#include "stdint.h"
#include "graphic.h"
#include "font.h"
int entry(struct BootParam *boot_param)
{
  graphic_init(&(boot_param->graphic_config));
  section_parser();
  while(1){
    asm("hlt");
  }
  return 0;
}
