#ifndef STRUCTS_H
#define STRUCTS_H

struct __attribute((packed)) GraphicConfig {
  unsigned long long frame_base;
  unsigned long long frame_size;
  unsigned long long horizontal_resolution;
  unsigned long long vertical_resolution;
  unsigned long long pixels_per_scan_line;
};

struct __attribute__((packed)) BootParam {
  unsigned long long kernel_entry;
  unsigned long long madt_addr;
  struct GraphicConfig graphic_config;
//  struct gdt bootstrap_gdt[3];
//  struct gdt_desc bootstrap_gdt_desc;
  unsigned long long kernel_addr;
};

#endif
