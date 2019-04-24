#include "structs.h"
#include "stdint.h"
#include "graphic.h"
#include "console.h"
#include "acpi.h"
#include "debug.h"

int entry(struct BootParam *boot_param)
{
  graphic_init(&(boot_param->graphic_config));
  console_init();
  debug_info_bootparam(boot_param);
  debug_info_graphic(&(boot_param->graphic_config));
  debug_info_cpuid();
  struct rsdp_desc *rsdp = (struct rsdp_desc *)boot_param->rsdp_addr;
  debug_info_rsdp(rsdp);
  while(1){
    asm("hlt");
  }
  return 0;
}
