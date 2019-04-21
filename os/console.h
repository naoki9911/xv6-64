#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdint.h"
void console_init();
void console_puts_str(const char *str);
void console_puts_dec(int64_t val);
void console_puts_hex(int64_t val);
void console_putc(uint8_t c);

#endif
