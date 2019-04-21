#include "structs.h"
#include "stdint.h"
#include "graphic.h"
#include "console.h"
#include "debug.h"
#include "asm.h"

int entry(struct BootParam *boot_param)
{
  graphic_init(&(boot_param->graphic_config));
  console_init();
  debug_info_graphic(&(boot_param->graphic_config));
  struct cpuid_reg cpuid;
  cpuid_read(&cpuid, 0);
  uint8_t cpuid_str[14];
  cpuid_str[0] = cpuid.ebx >> 0;
  cpuid_str[1] = cpuid.ebx >> 8;
  cpuid_str[2] = cpuid.ebx >> 16;
  cpuid_str[3] = cpuid.ebx >> 24;
  cpuid_str[4] = cpuid.edx >> 0;
  cpuid_str[5] = cpuid.edx >> 8;
  cpuid_str[6] = cpuid.edx >> 16;
  cpuid_str[7] = cpuid.edx >> 24;
  cpuid_str[8] = cpuid.ecx >> 0;
  cpuid_str[9] = cpuid.ecx >> 8;
  cpuid_str[10] = cpuid.ecx >> 16;
  cpuid_str[11] = cpuid.ecx >> 24;
  cpuid_str[12] = '\n';
  cpuid_str[13] = 0;
  console_puts_str("\n[CPUID] CPU Vendor:");
  console_puts_str((char *)cpuid_str);
  while(1){
    asm("hlt");
  }
  return 0;
}
