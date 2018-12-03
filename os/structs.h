#ifndef STRUCTS_H
#define STRUCTS_H

#include "stdint.h"

struct __attribute((packed)) GraphicConfig {
  uint64_t frame_base;
  uint64_t frame_size;
  uint64_t horizontal_resolution;
  uint64_t vertical_resolution;
  uint64_t pixels_per_scan_line;
};

struct __attribute__((packed)) BootParam {
  uint64_t kernel_entry;
  uint64_t madt_addr;
  struct GraphicConfig graphic_config;
//  struct gdt bootstrap_gdt[3];
//  struct gdt_desc bootstrap_gdt_desc;
  uint64_t kernel_addr;
};

#endif
