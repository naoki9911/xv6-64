#ifndef STRUCTS_H
#define STRUCTS_H

#define STA_X     0x8       // Executable segment
#define STA_E     0x4       // Expand down (non-executable segments)
#define STA_C     0x4       // Conforming code segment (executable only)
#define STA_W     0x2       // Writeable (non-executable segments)
#define STA_R     0x2       // Readable (executable segments)
#define STA_A     0x1       // Accessed

struct __attribute__((packed)) gdt {
  UINT16 limit;
  UINT16 base1;
  UINT8 base2;
  UINT8 access_byte;
  UINT8 flags;
  UINT8 base3;
};

struct __attribute__((packed)) gdt_desc {
  UINT16 size;
  UINT64 gdt_addr;
};

struct rsdp {
  CHAR8 sig[8];
  UINT8 Checksum;
  CHAR8 OEMID[6];
  UINT8 Revision;
  UINT32 RsdtAddress;
  UINT32 Len;
  UINT64 XsdtAddress;
  UINT8 ExtChecksum;
  UINT8 reserved[3];
};

struct sdt_header {
  CHAR8 sig[4];
  UINT32 len;
  UINT8 rev;
  UINT8 chksum;
  CHAR8 OEMID[6];
  CHAR8 tableid[8];
  UINT32 OEMrev;
  UINT32 creatorID;
  UINT32 creatorRev;
};

struct __attribute__((packed)) xsdt {
  struct sdt_header h;
  UINT64 pointer_others[];
};

struct __attribute__((packed)) madt {
  struct sdt_header h;
  UINT32 lapic_addr;
  UINT32 flags;
};

struct __attribute__((packed)) madt_entry {
  UINT8 entry_type;
  UINT8 record_len;
};

struct __attribute__((packed)) lapic {
  struct madt_entry entry;
  UINT8 processor_id;
  UINT8 lapic_id;
  UINT32 flags;
};

struct __attribute__((packed)) ioapic {
  struct madt_entry entry;
  UINT8 ioapic_id;
  UINT8 reserved;
  UINT32 ioapic_addr;
  UINT32 global_sys_intr_base;
};

struct __attribute__((packed)) iso {
  struct madt_entry entry;
  UINT8 bus_src;
  UINT8 irq_src;
  UINT32 gsi;
  UINT16 flags;
};

struct __attribute__((packed)) non_maskable_intr {
  struct madt_entry entry;
  UINT8 acpi_processor_id;
  UINT16 flags;
  UINT8 lint;
};

struct __attribute((packed)) GraphicConfig {
  UINT64 frame_base;
  UINT64 frame_size;
  UINT64 horizontal_resolution;
  UINT64 vertical_resolution;
  UINT64 pixels_per_scan_line;
};

struct __attribute__((packed)) BootParam {
  UINT64 kernel_entry;
  UINT64 madt_addr;
  struct GraphicConfig graphic_config;
//  struct gdt bootstrap_gdt[3];
//  struct gdt_desc bootstrap_gdt_desc;
  UINT64 kernel_addr;
};

#endif
