#include "structs.h"
#include "stdint.h"
#include "graphic.h"
#include "console.h"
int entry(struct BootParam *boot_param)
{
  graphic_init(&(boot_param->graphic_config));
  console_init();
  console_putc('l');
  console_putc('o');
  console_puts("Hello World!");
  while(1){
    asm("hlt");
  }
  return 0;
}
