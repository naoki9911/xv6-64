#include "structs.h"
#include "stdint.h"
#include "graphic.h"
#include "console.h"
#include "debug.h"

int entry(struct BootParam *boot_param)
{
  graphic_init(&(boot_param->graphic_config));
  console_init();
  debug_info_graphic(&(boot_param->graphic_config));
  debug_info_cpuid();
  while(1){
    asm("hlt");
  }
  return 0;
}
