#ifndef ACPI_H
#define ACPI_H
#include "stdint.h"

struct rsdp_desc {
    char signature[8];
    uint8_t chksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdt_addr;
} __attribute__((packed));
#endif
